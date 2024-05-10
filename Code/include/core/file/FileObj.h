

#ifndef VsboardMobile_FileObj_h
#define VsboardMobile_FileObj_h

#include <memory>
#include <string>
#include <vector>
#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"
#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK
{
    class FileObj;
    GLB_SMART_PTR_DEF(FileObj)
    GLB_SMART_VEC_PTR_DEF(FileObj)
    
    class FileMetadata;
    GLB_SMART_PTR_DEF(FileMetadata)
    GLB_SMART_VEC_PTR_DEF(FileMetadata)
    
    class FileObj
    {
    public:
        FileObj();
        FileObj(const std::string &fileName, const std::string &docUrl, const std::string &documentType, long long fileSize, long long modifiedDate, const std::string &thumbnailUrl, const FileMetadataPtr &fileMetadata, const std::string &localPath);
        virtual ~FileObj();
        FileObj(const FileObj &rhs);
        FileObj& operator = (const FileObj &rhs);
        
        static FileObjPtr CreateFileObjWithLocalPath(const std::string &localPath);
        
        void SetFileName(const std::string &fileName);
        std::string GetFileName(void);
        
        void SetDocUrl(const std::string &docUrl);
        std::string GetDocUrl(void);
        
        void SetDocumentType(const std::string &documentType);
        std::string GetDocumentType(void);
        
        void SetFileSize(long long fileSize);
        long long GetFileSize(void);
        
        void SetModifiedDate(long long modifiedDate);
        long long GetModifiedDate(void);
        
        void SetThumbnailUrl(const std::string &thumbnailUrl);
        std::string GetThumbnailUrl(void);
        
        void SetFileMetadata(const FileMetadataPtr &fileMetadata);
        FileMetadataPtr GetFileMetadata(void);
        
        void SetLocalPath(const std::string &localPath);
        std::string GetLocalPath(void);
        
        
        virtual void FromJson(rapidjson::Value &json);
        virtual void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer);
        
        std::string ToJsonString();
        
        
    private: // public:
        std::string m_FileName;
        std::string m_DocUrl;
        std::string m_DocumentType;
        long long m_FileSize;
        long long m_ModifiedDate;
        std::string m_ThumbnailUrl;
        FileMetadataPtr m_FileMetadata; 
        std::string m_LocalPath;
    };
    
    
}

#endif
