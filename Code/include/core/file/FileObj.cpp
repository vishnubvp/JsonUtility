

#include "core/util/Helpers.h"
#include "limits.h"

#include "core/file/FileObj.h"
#include "core/file/FileUtils.h"
#include "shared/model/utility/FileMetadata.h"


namespace VSTestSDK
{
    
    FileObj::FileObj()
    : m_FileName()
    , m_DocUrl()
    , m_DocumentType()
    , m_FileSize(LLONG_MAX)
    , m_ModifiedDate(LLONG_MAX)
    , m_ThumbnailUrl()
    , m_FileMetadata()
    , m_LocalPath()
    {
        
    }
    
    
    FileObj::FileObj(const std::string &fileName, const std::string &docUrl, const std::string &documentType, long long fileSize, long long modifiedDate, const std::string &thumbnailUrl, const FileMetadataPtr &fileMetadata, const std::string &localPath)
    : m_FileName(fileName)
    , m_DocUrl(docUrl)
    , m_DocumentType(documentType)
    , m_FileSize(fileSize)
    , m_ModifiedDate(modifiedDate)
    , m_ThumbnailUrl(thumbnailUrl)
    , m_FileMetadata(fileMetadata)
    , m_LocalPath(localPath)
    {
        
    }
    
    
    FileObj::~FileObj()
    {
    }
    
    FileObj::FileObj(const FileObj &rhs)
    {
        *this = rhs;
    }
    
    FileObj& FileObj::operator = (const FileObj &rhs)
    {
        if (&rhs != this)
        {
            m_FileName = rhs.m_FileName;
            m_DocUrl = rhs.m_DocUrl;
            m_DocumentType = rhs.m_DocumentType;
            m_FileSize = rhs.m_FileSize;
            m_ModifiedDate = rhs.m_ModifiedDate;
            m_ThumbnailUrl = rhs.m_ThumbnailUrl;
            m_FileMetadata = rhs.m_FileMetadata;
            m_LocalPath = rhs.m_LocalPath;
        }
        
        return *this;
    }
    
    FileObjPtr FileObj::CreateFileObjWithLocalPath(const std::string &localPath)
    {
        if (!FileUtils::IsFileExistsInPath(localPath)) {
            return nullptr;
        }
        FileObjPtr fileObj = std::make_shared<FileObj>();
        fileObj->SetLocalPath(localPath);
        fileObj->SetFileName(FileUtils::TrimFileName(localPath.c_str()));
        return fileObj;
    }
    
    
    void FileObj::SetFileName(const std::string &fileName)
    {
        m_FileName = fileName;
    }
    
    std::string FileObj::GetFileName(void)
    {
        return m_FileName;
    }
    
    void FileObj::SetDocUrl(const std::string &docUrl)
    {
        m_DocUrl = docUrl;
    }
    
    std::string FileObj::GetDocUrl(void)
    {
        return m_DocUrl;
    }
    
    void FileObj::SetDocumentType(const std::string &documentType)
    {
        m_DocumentType = documentType;
    }
    
    std::string FileObj::GetDocumentType(void)
    {
        return m_DocumentType;
    }
    
    void FileObj::SetFileSize(long long fileSize)
    {
        m_FileSize = fileSize;
    }
    
    long long FileObj::GetFileSize(void)
    {
        return m_FileSize;
    }
    
    void FileObj::SetModifiedDate(long long modifiedDate)
    {
        m_ModifiedDate = modifiedDate;
    }
    
    long long FileObj::GetModifiedDate(void)
    {
        return m_ModifiedDate;
    }
    
    void FileObj::SetThumbnailUrl(const std::string &thumbnailUrl)
    {
        m_ThumbnailUrl = thumbnailUrl;
    }
    
    std::string FileObj::GetThumbnailUrl(void)
    {
        return m_ThumbnailUrl;
    }
    
    void FileObj::SetFileMetadata(const FileMetadataPtr &fileMetadata)
    {
        m_FileMetadata = fileMetadata;
    }
    
    FileMetadataPtr FileObj::GetFileMetadata(void)
    {
        return m_FileMetadata;
    }
    
    void FileObj::SetLocalPath(const std::string &localPath)
    {
        m_LocalPath = localPath;
    }
    
    std::string FileObj::GetLocalPath(void)
    {
        return m_LocalPath;
    }
    
    
    
    void FileObj::FromJson(rapidjson::Value &jsonItems)
    {
        if (!jsonItems.IsNull())
        {
            
            m_FileName = Helpers::CheckStringValue(jsonItems, "fileName");
            m_DocUrl = Helpers::CheckStringValue(jsonItems, "docUrl");
            m_DocumentType = Helpers::CheckStringValue(jsonItems, "documentType");
            m_FileSize = Helpers::CheckInt64Value(jsonItems, "fileSize");
            m_ModifiedDate = Helpers::CheckInt64Value(jsonItems, "modifiedDate");
            m_ThumbnailUrl = Helpers::CheckStringValue(jsonItems, "thumbnailUrl");
            if (!Helpers::IsInvalidItem(jsonItems, "fileMetadata"))
            {
                FileMetadataPtr fileMetadata(new FileMetadata);
                fileMetadata->FromJson(jsonItems["fileMetadata"]);
                m_FileMetadata = fileMetadata;
            }
            
            
            m_LocalPath = Helpers::CheckStringValue(jsonItems, "localPath");
        }
        return;
        
    }
    
    void FileObj::ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer)
    {
        writer.StartObject();
        
        
        if (!m_FileName.empty())
        {
            writer.String("fileName");
            writer.String(m_FileName.c_str());
        }
        
        if (!m_DocUrl.empty())
        {
            writer.String("docUrl");
            writer.String(m_DocUrl.c_str());
        }
        
        if (!m_DocumentType.empty())
        {
            writer.String("documentType");
            writer.String(m_DocumentType.c_str());
        }
        
        if (LLONG_MAX != m_FileSize)
        {
            writer.String("fileSize");
            writer.Int64(m_FileSize);
        }
        
        if (LLONG_MAX != m_ModifiedDate)
        {
            writer.String("modifiedDate");
            writer.Int64(m_ModifiedDate);
        }
        
        if (!m_ThumbnailUrl.empty())
        {
            writer.String("thumbnailUrl");
            writer.String(m_ThumbnailUrl.c_str());
        }
        
        if (nullptr != m_FileMetadata)
        {
            writer.String("fileMetadata");
            m_FileMetadata->ToJson(writer);
        }
        
        if (!m_LocalPath.empty())
        {
            writer.String("localPath");
            writer.String(m_LocalPath.c_str());
        }
        
        
        writer.EndObject();
        
        return;
    }
    
    std::string FileObj::ToJsonString()
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        
        ToJson(writer);
        
        return buffer.GetString();
    }
    
    
}

