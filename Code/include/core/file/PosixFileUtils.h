

#ifndef VsboardMobile_PosixFileUtils_h
#define VsboardMobile_PosixFileUtils_h

#include <regex>
#include <string>
#include <vector>

namespace VSTestSDK {
    class PosixFileUtils
    {
    public:
        // file operation
        static bool IsFileExistsInPath(const std::string &path);
        static bool Remove(const std::string & filePath);
        static bool Rename(const std::string & oldPath, const std::string & newPath);
        static bool OpenTextFile(const std::string & path);
        static FILE* OpenFileForAppendingAtPath(const std::string & path);
        static FILE* OpenFileForWritingAtPath(const std::string & path);
        static long long LastModifiedTimeForFileAtPath(const std::string & path);
        static long long SizeOfFileAtPath(const std::string & path);
        static std::string TrimFileName(const char * sourcefile);
        static std::vector<std::string> SearchFilesAtPath(const std::string &path, const std::string &regexString);
        
        // folder operation
        static bool CleanFolder(const std::string & path);
        static bool CreateFolderAtPath(const std::string & path);
        static bool RemoveFolder(const std::string & path);
        static bool SplitFileFolder(const std::string & fullpath, std::string & folderPath, std::string & fileName);
        static long long SizeOfFolderAtPath(const std::string & path);
        static bool CreateRecursiveFolderByPath(const std::string &path);
        static bool RenameFolder(const std::string& oldPath, const std::string& newPath);
    };
}

#endif  //VsboardMobile_PosixFileUtils_h
