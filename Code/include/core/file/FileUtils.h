

#ifndef VsboardMobile_FileUtils_h
#define VsboardMobile_FileUtils_h

#include <string>
#include <vector>

namespace VSTestSDK {
    class FileUtils
    {
    public:
        // cross-platform
        static bool ClearFile(const std::string & path);
        static bool CopyFile(const std::string & fromPath, const std::string & toPath);
        static bool MoveFile(const std::string& fromPath, const std::string& toPath);
        static bool readFile(const std::string &path, std::string &content);
        static bool writeFile(const std::string &path, const std::string & content);
        static std::string GetFileFolderPath(const std::string & fullpath);
        static std::string GetFileExtension(const std::string &fileName);
        static std::string GetFileName(const std::string &fullpath);
        static std::string GetFileNameWithoutExtension(const std::string &fileName);
        static std::string GetFilePath(const std::string &folderPath, const std::string &fileName);
        static const char* GetFileName(const char* fullpath);

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
        static bool CreateFolderAtPath(std::string path, const std::vector<std::string> & folderList);
        static bool CreateRecursiveFolderByPath(const std::string &path);
        static bool RenameFolder(const std::string& fromPath, const std::string& toPath);
    };
}

#endif  //VsboardMobile_FileUtils_h
