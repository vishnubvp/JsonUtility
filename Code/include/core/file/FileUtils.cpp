

#include "core/file/FileUtils.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "core/config/SharedMobileConfig.h"
#include "core/log/Logger.h"
#include "core/util/StringUtils.h"
#include "core/util/TimeUtils.h"
#include "shared/const/SharedInternalConst.h"

#ifdef _WIN32
    #include "core/win32/WinFileUtils.h"
    using FileUtilsImpl = BBMobileSDK::WinFileUtils;
#else
    #include "core/file/PosixFileUtils.h"
    using FileUtilsImpl = BBMobileSDK::PosixFileUtils;
#endif  // _WIN32

namespace BBMobileSDK {

    bool FileUtils::ClearFile(const std::string & path)
    {
        std::ofstream file;
        file.open(path, std::ios::out | std::ios::trunc);
        if (file.is_open())
        {
            file.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    bool FileUtils::CopyFile(const std::string & fromPath, const std::string & toPath)
    {
        if (fromPath.length() == 0 || toPath.length() == 0)
        {
            return false;
        }
        
        std::ifstream source(fromPath, std::ios::binary);
        std::ofstream dest(toPath, std::ios::binary);
        
        std::istreambuf_iterator<char> begin_source(source);
        std::istreambuf_iterator<char> end_source;
        std::ostreambuf_iterator<char> begin_dest(dest);
        copy(begin_source, end_source, begin_dest);
        
        source.close();
        dest.close();
        
        return true;
    }

    bool FileUtils::readFile(const std::string &path, std::string &content)
    {
        std::string line;
        std::ifstream myfile(path);
        content = "";
        std::stringstream contentStream;
        
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                contentStream << line;
            }
            myfile.close();
            
            content = contentStream.str();
            
            return true;
        }
        else
        {
            Logger::debug("cannot open file");
        }
        
        return false;
    }

    bool FileUtils::writeFile(const std::string &path, const std::string & content)
    {
        if (path.length() == 0)
        {
            return false;
        }
        
        std::ofstream file(path, std::ios::out | std::ios::app);
        
        if (file.is_open())
        {
            file << content << "\n";
            file.close();
            
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string FileUtils::GetFileFolderPath(const std::string & fullpath)
    {
        std::string path = fullpath;
        
        if (path.empty())
            return path;
        
        size_t pos = path.find_last_of(CachingConst::DIRECTORY_SEPARATOR);
        
        if (pos == std::string::npos)
            return path;
        
        path = path.substr(0, pos);
        return path;
    }

    std::string FileUtils::GetFileName(const std::string &fullpath)
    {
        if (fullpath.empty())
            return "";
        
        size_t pos = fullpath.find_last_of(CachingConst::DIRECTORY_SEPARATOR);
        if (pos == std::string::npos)
            return "";
        
        // remove "/" from result
        return fullpath.substr(pos+1, fullpath.length()-pos);
    }
    
    const char* FileUtils::GetFileName(const char* fullpath)
    {
        if (NULL == fullpath) return "";
        
        const char* pos = std::strrchr(fullpath, CachingConst::DIRECTORY_SEPARATOR_CHAR);

        if (NULL == pos || '\0' == *(pos + 1))
        {
            return fullpath;
        }
        else
        {
            return pos + 1;
        }
    }
    
    std::string FileUtils::GetFileExtension(const std::string &fileName)
    {
        std::string extension = "";
        if (!fileName.empty())
        {
            size_t pos = fileName.find_last_of(".");
            if (pos != std::string::npos)
            {
                extension = fileName.substr(pos+1, fileName.length() - pos);
            }
        }
        
        return extension;
    }
    
    std::string FileUtils::GetFileNameWithoutExtension(const std::string &fileName)
    {
        std::string fileNameWithoutExtentsion = "";
        if (!fileName.empty())
        {
            size_t pos = fileName.find_last_of(".");
            if (pos == std::string::npos)
            {
                fileNameWithoutExtentsion = fileName;
            }
            else
            {
                fileNameWithoutExtentsion = fileName.substr(0, pos);
            }
        }
        
        return fileNameWithoutExtentsion;
    }

    std::string FileUtils::GetFilePath(const std::string &folderPath, const std::string &fileName)
    {
        return folderPath + CachingConst::DIRECTORY_SEPARATOR + fileName;
    }

    bool FileUtils::CreateFolderAtPath(std::string path, const std::vector<std::string> & folderList)
    {
        for (std::vector<std::string>::const_iterator iter = folderList.begin(); iter != folderList.end(); ++iter)
        {
            path += StringUtils::strfval(CachingConst::DIRECTORY_SEPARATOR) + iter->c_str();
            if (!FileUtils::CreateFolderAtPath(path))
            {
                return false;
            }
        }
        return true;
    }

    bool FileUtils::IsFileExistsInPath(const std::string &path)
    {
        return FileUtilsImpl::IsFileExistsInPath(path);
    }

    bool FileUtils::Remove(const std::string & filePath)
    {
        return FileUtilsImpl::Remove(filePath);
    }

    bool FileUtils::Rename(const std::string & oldPath, const std::string & newPath)
    {
        return FileUtilsImpl::Rename(oldPath, newPath);
    }

    bool FileUtils::OpenTextFile(const std::string & path)
    {
        return FileUtilsImpl::OpenTextFile(path);
    }

    FILE* FileUtils::OpenFileForAppendingAtPath(const std::string & path)
    {
        return FileUtilsImpl::OpenFileForAppendingAtPath(path);
    }

    FILE* FileUtils::OpenFileForWritingAtPath(const std::string &path)
    {
        return FileUtilsImpl::OpenFileForWritingAtPath(path);
    }

    long long FileUtils::LastModifiedTimeForFileAtPath(const std::string & path)
    {
        return FileUtilsImpl::LastModifiedTimeForFileAtPath(path);
    }

    long long FileUtils::SizeOfFileAtPath(const std::string & path)
    {
        return FileUtilsImpl::SizeOfFileAtPath(path);
    }

    std::string FileUtils::TrimFileName(const char * sourcefile)
    {
        return FileUtilsImpl::TrimFileName(sourcefile);
    }
    
    std::vector<std::string> FileUtils::SearchFilesAtPath(const std::string &path, const std::string &regexString)
    {
        return FileUtilsImpl::SearchFilesAtPath(path, regexString);
    }

    bool FileUtils::CleanFolder(const std::string & path)
    {
        return FileUtilsImpl::CleanFolder(path);
    }

    bool FileUtils::CreateFolderAtPath(const std::string & path)
    {
        return FileUtilsImpl::CreateFolderAtPath(path);
    }

    bool FileUtils::RemoveFolder(const std::string & path)
    {
        return FileUtilsImpl::RemoveFolder(path);
    }
    
    bool FileUtils::MoveFile(const std::string& fromPath, const std::string& toPath)
    {
        if (fromPath.empty() || toPath.empty())
        {
            return false;
        }
        
        if (Rename(fromPath, toPath))
        {
           return FileUtils::Remove(fromPath);
        }
        
        return false;
    }

    bool FileUtils::SplitFileFolder(const std::string & fullpath, std::string & folderPath, std::string & fileName)
    {
        return FileUtilsImpl::SplitFileFolder(fullpath, folderPath, fileName);
    }

    long long FileUtils::SizeOfFolderAtPath(const std::string & path)
    {
        return FileUtilsImpl::SizeOfFolderAtPath(path);
    }
    
    bool FileUtils::CreateRecursiveFolderByPath(const std::string &path)
    {
        return FileUtilsImpl::CreateRecursiveFolderByPath(path);
    }
    
    bool FileUtils::RenameFolder(const std::string& fromPath, const std::string& toPath)
    {
        return FileUtilsImpl::RenameFolder(fromPath, toPath);
    }
}
