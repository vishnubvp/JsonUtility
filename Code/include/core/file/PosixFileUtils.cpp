

#include "core/file/PosixFileUtils.h"

#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "core/config/SharedMobileConfig.h"
#include "core/log/Logger.h"
#include "core/util/StringUtils.h"
#include "core/util/TimeUtils.h"
#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK {
    
    static const char* FILE_OPEN_MODE_READ_BINARY = "rb";
    static const char* FILE_OPEN_MODE_WRITE_BINARY = "wb";
    static const char* FILE_OPEN_MODE_APPEND_BINARY = "ab";
    static const char* FILE_OPEN_MODE_APPEND = "a";
    
    static const int s_InvalidSize = -1;
    
    bool PosixFileUtils::IsFileExistsInPath(const std::string &path)
    {
        struct stat st;
        return stat(path.c_str(), &st) == 0;
    }
    
    bool PosixFileUtils::Remove(const std::string & filePath)
    {
        if (filePath.empty())
            return false;
        if (!IsFileExistsInPath(filePath))
            return true;
        int error = remove(filePath.c_str());
        return error == 0;
    }
    
    bool PosixFileUtils::Rename(const std::string & oldPath, const std::string & newPath)
    {
        if (oldPath.empty() || newPath.empty())
            return false;
        
        int error = rename(oldPath.c_str(), newPath.c_str());
        return error == 0;
    }
    
    bool PosixFileUtils::OpenTextFile(const std::string & path)
    {
        std::fstream fs;
        fs.open(path.c_str());
        
        if (fs.is_open())
        {
            return true;
        }
        
        return fopen(path.c_str(), FILE_OPEN_MODE_APPEND) != NULL;
    }
    
    FILE* PosixFileUtils::OpenFileForAppendingAtPath(const std::string & path)
    {
        return fopen(path.c_str(), FILE_OPEN_MODE_APPEND_BINARY);
    }
    
    FILE* PosixFileUtils::OpenFileForWritingAtPath(const std::string &path)
    {
        return fopen(path.c_str(), FILE_OPEN_MODE_WRITE_BINARY);
    }
    
    long long PosixFileUtils::LastModifiedTimeForFileAtPath(const std::string & path)
    {
        long long ts = -1;
        struct stat status = { 0 };
        // if not exists
        if (stat(path.c_str(), &status) != -1) {
            ts = status.st_mtime;
        }
        
        return ts;
    }
    
    long long PosixFileUtils::SizeOfFileAtPath(const std::string & path)
    {
        long long size = 0;
        FILE *file = fopen(path.c_str(), FILE_OPEN_MODE_READ_BINARY);
        if (file)
        {
            fseek(file, 0, SEEK_END);
            size = ftell(file);
            rewind(file);
            fclose(file);
        }
        
        return size;
    }
    
    std::string PosixFileUtils::TrimFileName(const char * sourcefile)
    {
        std::string absPath = sourcefile;
        
        if (absPath.empty())
            return absPath;
        
        if (absPath.find_last_of("/") != std::string::npos)
        {
            return absPath.substr(absPath.find_last_of("/")+1, std::string::npos);
        }
        else
        {
            return absPath;
        }
    }
    
    std::vector<std::string> PosixFileUtils::SearchFilesAtPath(const std::string &path, const std::string &regexString)
    {
        DIR *dp;
        struct dirent *entry;
        struct stat statbuf;
        std::vector<std::string> filesVec;
        
        if ((dp = opendir(path.c_str())) == NULL)
        {
            Logger::debug("folder is not exist: " + StringUtils::strfval(path));
            return filesVec;
        }
        
        while ((entry = readdir(dp)) != NULL)
        {
            char subdir[PATH_MAX];
            snprintf(subdir, sizeof(subdir), "%s/%s", path.c_str(), entry->d_name);
            lstat(subdir, &statbuf);
            
            if (!S_ISDIR(statbuf.st_mode))
            {
                std::string fileName = StringUtils::strfval(entry->d_name);
                
                // Fix it later: std::regex will cause crash issue on android.
                if (std::regex_match(fileName, std::regex(regexString)))
                {
                    filesVec.push_back(fileName);
                }
            }
        }
        
        closedir(dp);
        return filesVec;
    }
    
    bool PosixFileUtils::CleanFolder(const std::string & path)
    {
        DIR* dir = opendir(path.c_str());
        if (!dir)
            return false;
        
        struct dirent *next_file;
        char filepath[PATH_MAX];
        bool hasError = false;
        while ( (next_file = readdir(dir)) != NULL )
        {
            // build the path for each file in the folder
            snprintf(filepath, sizeof(filepath), "%s/%s", path.c_str(), next_file->d_name);
            if (remove(filepath))
                hasError = true;
        }
        closedir(dir);
        return true;
    }
    
    bool PosixFileUtils::CreateFolderAtPath(const std::string & path)
    {
        struct stat st = { 0 };
        
        // if not exists
        if (stat(path.c_str(), &st) == -1) {
            // TODO: support multi-layer directories creation
            // make path, mkdir -p
            int result = mkdir(path.c_str(), 0700);
            
            // return true if there is no error
            return result == 0;
        }
        
        // already exists
        return true;
    }
    
    bool PosixFileUtils::RemoveFolder(const std::string & path)
    {
        try
        {
            DIR *dp;
            struct dirent *entry;
            struct stat statbuf;
            
            if ((dp = opendir(path.c_str())) == NULL)
            {
                Logger::debug("folder is not exist: " + path);
                
                return true;
            }
            
            while ((entry = readdir(dp)) != NULL)
            {
                char subdir[PATH_MAX];
                snprintf(subdir, sizeof(subdir), "%s/%s", path.c_str(), entry->d_name);
                lstat(subdir, &statbuf);
                
                if (S_ISDIR(statbuf.st_mode))
                {
                    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                    {
                        continue;
                    }
                    
                    if(!RemoveFolder(subdir))
                    {
                        return false;
                    }
                }
                else
                {
                    remove(subdir);
                }
            }
            
            if (NULL != dp)
            {
                closedir(dp);
            }
            
            if(remove(path.c_str()) != 0)
            {
                return false;
            }
        }
        catch (...)
        {
            Logger::debug("Meet exception when remove folder: " + path);
            
            return false;
        }
        
        return true;
    }
    
    bool PosixFileUtils::SplitFileFolder(const std::string & fullpath, std::string & folderPath, std::string & fileName)
    {
        if (fullpath.empty())
            return false;
        
        std::string relativePath = fullpath;
        size_t pos = relativePath.find_last_of(CachingConst::DIRECTORY_SEPARATOR);
        
        if (pos == std::string::npos)
            return false;
        
        folderPath = relativePath.substr(0, pos);
        fileName = relativePath.substr(pos + 1);
        
        return true;
    }
    
    long long PosixFileUtils::SizeOfFolderAtPath(const std::string & path)
    {
        DIR *dp;
        struct dirent *entry;
        struct stat statbuf;
        
        long long totalSize = 0;
        
        if ((dp = opendir(path.c_str())) == NULL)
        {
            Logger::debug("folder is not exist: " + StringUtils::strfval(path));
            
            return s_InvalidSize;
        }
        
        while ((entry = readdir(dp)) != NULL)
        {
            char subdir[PATH_MAX];
            snprintf(subdir, sizeof(subdir), "%s/%s", path.c_str(), entry->d_name);
            lstat(subdir, &statbuf);
            
            if (S_ISDIR(statbuf.st_mode))
            {
                // folder
                if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                {
                    continue;
                }
                
                long long subDirSize = SizeOfFolderAtPath(subdir);
                
                if (subDirSize == s_InvalidSize)
                {
                    closedir(dp);
                    return s_InvalidSize;
                }
                else
                {
                    totalSize += subDirSize;
                }
            }
            else
            {
                // files
                totalSize += statbuf.st_size;
            }
        }
        
        closedir(dp);
        return totalSize;
    }
    
    bool PosixFileUtils::CreateRecursiveFolderByPath(const std::string &path)
    {
        std::string subStr = "";
        bool status = true;
        std::vector<std::string> subPaths = StringUtils::Split(path, CachingConst::DIRECTORY_SEPARATOR);
        std::vector<std::string>::const_iterator iter = subPaths.begin();
        while (status &&
               iter != subPaths.end())
        {
            subStr += (*iter) + CachingConst::DIRECTORY_SEPARATOR;
            status = CreateFolderAtPath(subStr);
            
            iter++;
        }
        
        return status;
    }
    
    bool PosixFileUtils::RenameFolder(const std::string& oldPath, const std::string& newPath)
    {
        if (oldPath.empty() || newPath.empty())
        {
            return false;
        }
        
        return Rename(oldPath, newPath);
    }
    
}
