

#include "core/util/MobileCurlNetwork.h"

#include <math.h>

#include "core/config/SharedMobileConfig.h"
#include "core/file/FileUtils.h"
#include "core/notification/NotificationCenter.h"
#include "core/http/CurlSharedObject.h"
#include "core/util/Helpers.h"
#include "core/util/InternalConstData.h"
#include "shared/const/NotificationNames.h"


#ifdef _WIN32
#pragma comment ( lib, "ws2_32.lib" )   
#pragma comment ( lib, "winmm.lib" )  
#endif

#define VECTOR_DEFAULT_SIZE 20

#define SECONDS_DEFAULT_TRANSFER_TIMEOUT 60
#define SECONDS_DEFAULT_CONNECT_TIMEOUT  20

const int CURL_CONTINUE_TRANSFER = 0;
const int CURL_ABORT_TRANSFER = 1;


namespace BBMobileSDK
{
    std::atomic<int> MobileCurlNetwork::s_abortAllTransfer{CURL_CONTINUE_TRANSFER};
    
    MobileCurlNetwork::MobileCurlNetwork(int connectionTimeout, int readTimeout)
    : url()
    , httpCode(0)
    , content()
    , m_responseHeaders()
    , m_pDownloadFile(NULL)
    , m_LengthOfResumeFile(0)
    , m_transferCallbackFunction(nullptr)
    , m_connectTimeout(connectionTimeout)
    , m_readTimeout(readTimeout) 
    , m_lastModifiedTimeStamp(LLONG_MAX)
    , m_abortTransfer(CURL_CONTINUE_TRANSFER)
    , m_previousUploadPercentage(0.00)
    {
        m_responseHeaders.reserve(VECTOR_DEFAULT_SIZE);
    }

	MobileCurlNetwork::~MobileCurlNetwork()
	{
		if (nullptr != m_pDownloadFile)
		{
            fclose(m_pDownloadFile);
            m_pDownloadFile = NULL;
		}
	}
    
// #- callbacks
    
    
    void MobileCurlNetwork::RegisterTransferCallback(sf_callback_progress_meter transferCallback)
    {
        m_transferCallbackFunction = transferCallback;
    }
    
    size_t MobileCurlNetwork::handle(char * data, size_t size, size_t nmemb, void * p)
    {
        return static_cast<MobileCurlNetwork*>(p)->handle_impl(data, size, nmemb);
    }
    
    size_t MobileCurlNetwork::handle_impl(char* data, size_t size, size_t nmemb)
    {
        
        content.append(data, size * nmemb);
        return size * nmemb;
    }
    
    size_t MobileCurlNetwork::cb_parse_headers_handle(char * data, size_t size, size_t nmemb, void *p)
    {
        return static_cast<MobileCurlNetwork*>(p)->cb_parse_headers_impl(data, size, nmemb);
    }
    
    size_t MobileCurlNetwork::cb_parse_headers_impl(char * data, size_t size, size_t nmemb)
    {
        char *buffer = (char*)data;
        
        std::string headStr = "";
        headStr.append(buffer, size * nmemb);
        
        Logger::debug("head: " + headStr);
        
        RestHeaderField header = RestHeaderField::InstanceFromHeaderString(headStr);
        if (!header.GetName().empty())
            m_responseHeaders.push_back(header);
        
        return size * nmemb;
    }
    
    size_t MobileCurlNetwork::cb_write_file_handle(void *data, size_t size, size_t nmemb, void *p)
    {
        return static_cast<MobileCurlNetwork*>(p)->cb_write_file_impl(data, size, nmemb);
    }
    
    size_t MobileCurlNetwork::cb_write_file_impl(void *data, size_t size, size_t nmemb)
    {
        return fwrite(data, size, nmemb, m_pDownloadFile);
    }
    
    // check http status code
    void MobileCurlNetwork::checkStatusCode()
    {
        if (httpCode == 0) {
            content = ResponseErrorMessage::CONNECTION_ERROR;
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", connection error.");
        } else if (httpCode >= 200 && httpCode < 400) {
            Logger::debug("http status code : " + StringUtils::strfval(httpCode) + ", request successful.");
        } else if (httpCode == 401) {
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", authentication failed.");
        } else if (httpCode == 403) {
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", request forbidden.");
        } else if (httpCode == 413) {
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", request entity too large.");
        } else if (httpCode >= 400 && httpCode < 500) {
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", request error.");
        } else if (httpCode >= 500) {
            Logger::error("http status code : " + StringUtils::strfval(httpCode) + ", server error.");
        } else {
            Logger::error("http status code: " + StringUtils::strfval(httpCode) + ", unknown error");
        }
    }
    
    void MobileCurlNetwork::BuildHttpHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers, bool usingGzip, bool contentTypeJson)
    {
        RestHeaderFieldVPtr requestHeaders = headers;
        
        if (usingGzip) {
            auto gzipHeader = std::make_shared<RestHeaderField>("Content-Encoding", "gzip");
            requestHeaders.push_back(gzipHeader);
        }
        
        if (contentTypeJson) {
            auto jsonHeader = std::make_shared<RestHeaderField>("Content-Type", "application/json;charset=UTF-8");
            requestHeaders.push_back(jsonHeader);
        }
        
        for (auto header : requestHeaders) {
            if (!header)
                continue;
            
            std::string headerString = header->toString();
            Logger::debug("curl headers: " + headerString);
            http_headers = curl_slist_append(http_headers, headerString.c_str());
        }
    }
    
    void MobileCurlNetwork::BuildFormHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers, bool usingGzip)
    {
        RestHeaderFieldVPtr requestHeaders = headers;
        
        if (usingGzip) {
            auto gzipHeader = std::make_shared<RestHeaderField>("Content-Encoding", "gzip");
            requestHeaders.push_back(gzipHeader);
        }
        
        auto formHeader = std::make_shared<RestHeaderField>("Content-Type", "application/x-www-form-urlencoded");
        requestHeaders.push_back(formHeader);
        
        for (auto header : requestHeaders) {
            if (!header)
                continue;
            std::string headerString = header->toString();
            Logger::debug("curl headers: " + headerString);
            http_headers = curl_slist_append(http_headers, headerString.c_str());
        }
        
    }
    
    void MobileCurlNetwork::BuildCurlHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers)
    {
		for (auto header : headers) {
            if (!header)
                continue;
            std::string headerString = header->toString();
			Logger::debug("curl headers: " + headerString);
			http_headers = curl_slist_append(http_headers, headerString.c_str()); 
		}
    }

    bool MobileCurlNetwork::InitCurlCommonOps(CURL *&curl, CurlSharedObjectPtr &sharedObj, struct curl_slist *& httpHeaders, const std::string &urlString, const RestHeaderFieldVPtr &headers, bool isUsingGzip, ContentType contentType)
    {
        url = urlString;
        Logger::info("Executing URL: " + url);
        
        sharedObj = CurlSharedObject::GetInstance();
        if (sharedObj == nullptr)
            return false;
        
        curl = curl_easy_init();

        if (curl == NULL && url.empty())
            return false;

        // set url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // no initial cookie file
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

        // To unzip, decode http request
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");

        // timeout settings
        SetConnectOption(curl);
        
        // response writer
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handle);
        
        // register progress meter
        SetProgressOption(curl);
        
        if (LLONG_MAX != m_lastModifiedTimeStamp)
        {
            curl_easy_setopt(curl, CURLOPT_TIMEVALUE, m_lastModifiedTimeStamp);
            curl_easy_setopt(curl, CURLOPT_TIMECONDITION, CURL_TIMECOND_IFMODSINCE);
        }
        
        //Set ssl options
        SetSSLOption(curl);
        
        // Because in multi-threaded environment, DNS lookup is not thread-safe
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, true);
        
        // cert files for SSL
        std::string certpathStr = SharedMobileConfig::m_certStoragePath;
        Logger::debug("cert file location : " + SharedMobileConfig::m_certStoragePath);
        curl_easy_setopt(curl, CURLOPT_CAINFO, SharedMobileConfig::m_certStoragePath.c_str());
        
        // Set proxy options
        SetProxyOption(curl);
        
        // Config TCP Keep-alive to make sure request return quickly when network is broken
        // Detail about those fields could see here: http://www.tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE,  RestConst::TCP_KEEPALIVE_IDLE_SEC);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, RestConst::TCP_KEEPALIVE_INTVL_SEC);
        
        CURLSH* curlShared = sharedObj->GetCurlSharedObject();
        curl_easy_setopt(curl, CURLOPT_SHARE, curlShared);
        
        // headers
        switch (contentType) {
            case ContentTypeRaw:
                BuildHttpHeaders(httpHeaders, headers, isUsingGzip, false);
                break;
            case ContentTypeJSON:
                BuildHttpHeaders(httpHeaders, headers, isUsingGzip, true);
                break;
            case ContentTypeForm:
                BuildFormHeaders(httpHeaders, headers, isUsingGzip);
                break;
            default:
                break;
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpHeaders);
        
        return true;
    }
    
    void MobileCurlNetwork::CleanUpCurl(CURL *curl, CurlSharedObjectPtr &sharedObj)
    {
        if (nullptr != curl)
        {
            curl_easy_cleanup(curl);
        }
    }

    void MobileCurlNetwork::PerformAndCheckCurlResult(CURL *&curl, CurlSharedObjectPtr &sharedObj, RestResponsePtr & restResponse, bool hasCookie)
    {
        if(curl == NULL)
        {
            return;
        }
        CURLcode curl_code = curl_easy_perform (curl);

        // if curl code is not ok, means failed to call curl_easy_perform
        if (curl_code != CURLE_OK)
        {
            // For curl error code detail description: https://curl.haxx.se/libcurl/c/libcurl-errors.html
            restResponse->curlErrorCode = curl_code;
            if (curl_code == CURLE_ABORTED_BY_CALLBACK)
            {
                restResponse->httpResponseCode = HttpStatusCodeHTTPRequestAborted;
            }
            else
            {
                restResponse->httpResponseCode = 0;
            }
            
            const char* err = curl_easy_strerror(curl_code);
            if (nullptr != err &&
                strlen(err) > 0)
            {
                std::string curlCodeDescription(err);
                Logger::error("curl_easy_perform failed, curl code is: " + StringUtils::strfval(curl_code) + " " + curlCodeDescription);
            }
            
            NotificationCenter::PostNotification(NotificationNames::MOBILYTICS_MARKER_CURL, (void*)&restResponse);
            
            CleanUpCurl(curl, sharedObj);
            return;
        }
        
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpCode);
        Logger::debug("Http code is: " + StringUtils::strfval(httpCode));
        
        // handling based on returned http code
        if (httpCode >= 300 && httpCode < 400)
        {
            // redirected
            char *redirectUrl = NULL;
            curl_easy_getinfo(curl,CURLINFO_REDIRECT_URL, &redirectUrl);
            if (nullptr != redirectUrl)
            {
                restResponse->redirectUrl = std::string(redirectUrl);
            
                Logger::debug("redirect url:  " + restResponse->redirectUrl);
            }
        }
        else
        {
            checkStatusCode();
        }
        
        restResponse->httpResponseCode = static_cast<int>(httpCode);
        restResponse->strContent = content;
        restResponse->m_Headers = m_responseHeaders;
        
        Logger::debug("The content is : " + content);
        
        if (hasCookie) {
            struct curl_slist *cookiesList;
            struct curl_slist *nc;
            
            curl_code = curl_easy_getinfo (curl, CURLINFO_COOKIELIST, &cookiesList);
            
            Logger::debug("curl easy getinfo cookie return code is : " + StringUtils::strfval(curl_code));
            
            nc = cookiesList;
            
            int i = 1;
            std::string strResponseCookies = "";
            
            while(nc)
            {
                Logger::debug("the cookie str is : " + std::string(nc->data));                
                auto cookie = RestCookie::InstanceFromNetscapeCookie(nc->data);
                restResponse->m_Cookies.push_back(cookie);
                
                strResponseCookies += nc->data;
                strResponseCookies += ";";
                nc = nc->next;
                
                i++;
            }
            
            Logger::debug("The number i is : " + StringUtils::strfval(i));
            Logger::debug("The fetching cookielist is : " + strResponseCookies);
            
            curl_slist_free_all(cookiesList);
        }
        
        CleanUpCurl(curl, sharedObj);
    }
    
    
    // # - http request methods
    RestResponsePtr MobileCurlNetwork::Get(const std::string & urlStr, const RestHeaderFieldVPtr &headers, bool usingGzip, bool contentTypeJson)
    {
        Logger::debug("Http method : GET");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;
        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers, usingGzip, contentTypeJson ? ContentTypeJSON : ContentTypeRaw)) {
            PerformAndCheckCurlResult(curl, sharedObj, restResponse, true);
            curl_slist_free_all(httpHeaders);

        }
        
        return restResponse;
    }
    
    RestResponsePtr MobileCurlNetwork::Delete(const std::string & urlStr, const RestHeaderFieldVPtr & headers)
    {
        Logger::debug("Http method : DELETE");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;

        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers)) {
            /* HTTP DELETE method */
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE"); /* !!! */
            PerformAndCheckCurlResult(curl, sharedObj, restResponse);
            curl_slist_free_all(httpHeaders);
        }
        
        return restResponse;
    }

    void MobileCurlNetwork::ZipData(const std::string &parameters, unsigned char *&dest, unsigned long &len, bool &isUsingGzip)
    {
        Logger::trace("post body len: " + StringUtils::strfval(parameters.length()));
        
        if (isUsingGzip && parameters.length() > SizeConst::SIZE_1k) {
			bool res = StringUtils::GzipData(parameters, &dest, &len);
            if (res) {
                Logger::debug("zipped len: " + StringUtils::strfval(len));
                return;
            } else {
                Logger::error("gzip error, pass raw data");
            }
        }
        isUsingGzip = false;
    }
    
    void MobileCurlNetwork::SetGzipOption(CURL *&curl, const std::string &parameters, unsigned char * dest, unsigned long len, bool isUsingGzip)
    {
        if (isUsingGzip) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dest);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len);
        } else {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, parameters.length());
        }
    }
    
    void MobileCurlNetwork::SetProgressOption(CURL *&curl)
    {
        /* progress meter */
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    }
    
    RestResponsePtr MobileCurlNetwork::Post(const std::string &urlStr, const std::string &parameters, const RestHeaderFieldVPtr & headers, bool usingGzip)
    {
        Logger::debug("Http method : POST");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;
        
        unsigned char * dest = NULL;
        unsigned long len = 0;
        ZipData(parameters, dest, len, usingGzip);
            
        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers, usingGzip)) {
            SetGzipOption(curl, parameters, dest, len, usingGzip);
            PerformAndCheckCurlResult(curl, sharedObj, restResponse, true);
            curl_slist_free_all(httpHeaders);
        }
            
            BB_RELEASE(dest);
        
        return restResponse;
    }
    
    
    RestResponsePtr MobileCurlNetwork::PostForm(const std::string & urlStr, const std::string & parameters, const RestHeaderFieldVPtr & headers, bool usingGzip)
    {
        Logger::debug("Http method : POST FORM");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;

        unsigned char * dest = NULL;
        unsigned long len = 0;
        ZipData(parameters, dest, len, usingGzip);
            
        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers, usingGzip, ContentTypeForm)) {
            SetGzipOption(curl, parameters, dest, len, usingGzip);
            PerformAndCheckCurlResult(curl, sharedObj, restResponse, true);
            curl_slist_free_all(httpHeaders);
        }
            
            BB_RELEASE(dest);
        
        return restResponse;
        
    }
    
    RestResponsePtr MobileCurlNetwork::Put(const std::string & urlStr, const std::string & body, const RestHeaderFieldVPtr & headers, bool usingGzip)
    {
        Logger::debug("Http method : PUT");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;

        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers, usingGzip)) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            Logger::trace("put body len: " + StringUtils::strfval(strlen(body.c_str())));
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
            PerformAndCheckCurlResult(curl, sharedObj, restResponse);
            curl_slist_free_all(httpHeaders);
        }
        return restResponse;
    }
    
    RestResponsePtr MobileCurlNetwork::Patch(const std::string & urlStr, const std::string & body, const RestHeaderFieldVPtr & headers, bool usingGzip)
    {
        Logger::debug("Http method : PATCH");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;
        
        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers, usingGzip)) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH"); /* !!! */
            Logger::debug("patch body len: " + StringUtils::strfval(strlen(body.c_str())));
            Logger::debug("patch body: " + body);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
            PerformAndCheckCurlResult(curl, sharedObj, restResponse);
            curl_slist_free_all(httpHeaders);
        }
        return restResponse;
    }
    
    RestResponsePtr MobileCurlNetwork::Head(const std::string & urlStr, const RestHeaderFieldVPtr & headers)
    {
        Logger::debug("Http method : HEAD");
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;

        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, urlStr, headers))
        {
            curl_easy_setopt(curl, CURLOPT_NOBODY , 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEHEADER, this);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, cb_parse_headers_handle);
            curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
            PerformAndCheckCurlResult(curl, sharedObj, restResponse);
            curl_slist_free_all(httpHeaders);
        }
        
        return restResponse;
    }
        
    RestResponsePtr MobileCurlNetwork::Download(const std::string &url, const std::string &path, const RestHeaderFieldVPtr & headers, curl_off_t resume_file_len)
    {
        RestResponsePtr restResponse(new RestResponse);
        CURL* curl;
        CurlSharedObjectPtr sharedObj;
        struct curl_slist * httpHeaders = nullptr;
        
        if (InitCurlCommonOps(curl, sharedObj, httpHeaders, url, headers))
        {
           
			if (resume_file_len > 0)
			{
                m_LengthOfResumeFile = resume_file_len;
				curl_easy_setopt(curl, CURLOPT_RESUME_FROM, resume_file_len);

				/* open the files: Append mode */
				m_pDownloadFile = FileUtils::OpenFileForAppendingAtPath(path);
			}
			else
			{
				/* open the files: Write mode */
				m_pDownloadFile = FileUtils::OpenFileForWritingAtPath(path);
			}

            if (m_pDownloadFile == NULL)
            {
                Logger::error("create download file failed : " + path);
                CleanUpCurl(curl, sharedObj);
                return RestResponsePtr(new RestResponse(0, content));
            }
            
            /* send all data to this function  */
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb_write_file_handle);
            
            // abort if slower than 50 bytes/sec during 60 seconds
            curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, Curl::Setting::LEAST_BYTES_WHEN_LOW_SPEED);
			curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, Curl::Setting::TIMEOUT_IN_SECONDS_WHEN_LOW_SPEED);
            
            PerformAndCheckCurlResult(curl, sharedObj, restResponse);
            fclose(m_pDownloadFile);
            m_pDownloadFile = NULL;
            
            curl_slist_free_all(httpHeaders);
        }
        
        return restResponse;
    }
    
    void MobileCurlNetwork::AbortTransfer()
    {
        m_abortTransfer = CURL_ABORT_TRANSFER;
    }
    
    void MobileCurlNetwork::ResetTransferStatusToContinue()
    {
        s_abortAllTransfer.store(CURL_CONTINUE_TRANSFER);
    }
    
    void MobileCurlNetwork::AbortAllTransfer()
    {
        s_abortAllTransfer.store(CURL_ABORT_TRANSFER);
    }
    
    RestResponsePtr MobileCurlNetwork::UploadSingleFile(const std::string &urlStr, const FileObjPtr & file, const RestHeaderFieldVPtr & headers)
    {
        RestResponsePtr restResponse(new RestResponse);

        if (file == nullptr)
        {
            restResponse->httpResponseCode = 0;
            Logger::error("no file found");
            return restResponse;
        }
        
        CURL *curl;
        CURLM *multi_handle;
        int still_running;
        
        Logger::debug("upload file to url: " + urlStr);
        
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        
        /* Add file/contenttype section */
        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, RestConst::FileUpload::FORM_KEY_FILE,
                     CURLFORM_FILE, file->GetLocalPath().c_str(),
                     CURLFORM_FILENAME, file->GetFileName().c_str(),
//                     CURLFORM_CONTENTTYPE, "text/json",   // could not get content type currently
                     CURLFORM_END);
        
        curl = curl_easy_init();
        multi_handle = curl_multi_init();
        
        /* initalize custom header list (stating that Expect: 100-continue is not
         wanted */
        
        struct curl_slist *headerlist = NULL;
        static const char FORM_HEADER[] = "Expect:";
        BuildHttpHeaders(headerlist, headers, false, false);
        
        headerlist = curl_slist_append(headerlist, FORM_HEADER);

        if(curl && multi_handle)
        {
            
            /* what URL that receives this POST */
            curl_easy_setopt(curl, CURLOPT_URL, urlStr.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handle);
            
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
            curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
            
            //Set ssl options
            SetSSLOption(curl);
            
            // cert files for SSL
            std::string certpathStr = SharedMobileConfig::m_certStoragePath;
            Logger::debug("cert file location : " + SharedMobileConfig::m_certStoragePath);
            curl_easy_setopt(curl, CURLOPT_CAINFO, SharedMobileConfig::m_certStoragePath.c_str());
            
            //Set Progress Option
            SetProgressOption(curl);
            
            curl_multi_add_handle(multi_handle, curl);
            
            curl_multi_perform(multi_handle, &still_running);
            
            do
            {
                struct timeval timeout;
                int rc; /* select() return code */
                CURLMcode mc; /* curl_multi_fdset() return code */
                
                fd_set fdread;
                fd_set fdwrite;
                fd_set fdexcep;
                int maxfd = -1;
                
                long curl_timeo = -1;
                
                FD_ZERO(&fdread);
                FD_ZERO(&fdwrite);
                FD_ZERO(&fdexcep);
                
                /* set a suitable timeout to play around with */
                timeout.tv_sec = 1;
                timeout.tv_usec = 0;
                
                curl_multi_timeout(multi_handle, &curl_timeo);
                if(curl_timeo >= 0) {
                    timeout.tv_sec = curl_timeo / 1000;
                    if(timeout.tv_sec > 1)
                        timeout.tv_sec = 1;
                    else
                        timeout.tv_usec = (curl_timeo % 1000) * 1000;
                }
                
                /* get file descriptors from the transfers */
                mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);
                
                if(mc != CURLM_OK)
                {
                    Logger::error("curl_multi_fdset() failed, code " + StringUtils::strfval(mc));
                    break;
                }
                
                /* On success the value of maxfd is guaranteed to be >= -1. We call
                 select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
                 no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
                 to sleep 100ms, which is the minimum suggested value in the
                 curl_multi_fdset() doc. */
                
                if(maxfd == -1)
                {
#ifdef  _WIN32
                    Sleep(100);
                    rc = 0;
#else
                    /* Portable sleep for platforms other than Windows. */
                    struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
                    rc = select(0, NULL, NULL, NULL, &wait);
#endif
                }
                else
                {
                    /* Note that on some platforms 'timeout' may be modified by select().
                     If you need access to the original value save a copy beforehand. */
                    rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);
                }
                
                switch(rc)
                {
                        case -1:
                        {
                            /* select error */
                            Logger::error("select error: " + StringUtils::strfval(rc));
                        }
                        break;
                    case 0:
                    default:
                        /* timeout or readable/writable sockets */
                        CURLMcode part_code = curl_multi_perform(multi_handle, &still_running);
                        if (part_code != 0)
                        {
                            Logger::error("part_code error: " + StringUtils::strfval(part_code));
                        }
                        break;
                }
            } while(still_running);
            
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            
            checkStatusCode();
            
            // clean all
            curl_multi_cleanup(multi_handle);
            curl_easy_cleanup(curl);
            curl_formfree(formpost);
            curl_slist_free_all (headerlist);
        }
        
        restResponse->httpResponseCode = static_cast<int>(httpCode);
        restResponse->strContent = content;

        Logger::debug("content: " + content);
        
        return restResponse;
    }
    
    int MobileCurlNetwork::progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
    {
        MobileCurlNetwork *curlNetwork = static_cast<MobileCurlNetwork *>(clientp);
        if (curlNetwork != nullptr && curlNetwork->m_transferCallbackFunction)
        {
            // only calculate progress when there is callback registered
            if (curlNetwork->m_transferCallbackFunction)
            {
                curl_off_t now = BB_MAX(dlnow, ulnow);
                curl_off_t total = BB_MAX(dltotal, ultotal);
                if (total > 0)
                {
                    // for resume download, progress should consider size of existed local file.
                    if (curlNetwork->m_LengthOfResumeFile > 0)
                    {
                        now += curlNetwork->m_LengthOfResumeFile;
                        total += curlNetwork->m_LengthOfResumeFile;
                    }
                    
                    double percentage = (double)now / (double)total;
                    
                    if (percentage - curlNetwork->m_previousUploadPercentage > 0.005f)
                    {
                        curlNetwork->m_transferCallbackFunction(percentage);
                        curlNetwork->m_previousUploadPercentage = percentage;
                    }
                }
                
            }
            
            return curlNetwork->m_abortTransfer + s_abortAllTransfer.load();
        }
        
        return 0;
    }
    
    void MobileCurlNetwork::SetConnectOption(CURL *& curl)
    {
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, BB_MAX(m_connectTimeout, SECONDS_DEFAULT_CONNECT_TIMEOUT));
        if (m_readTimeout > 0)
        {
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, BB_MAX(m_readTimeout, SECONDS_DEFAULT_TRANSFER_TIMEOUT));
        }
        else
        {
            // no any limitation for transfer time.
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0L);
        }
    }
    
    void MobileCurlNetwork::SetSSLOption(CURL *& curl)
    {
        //Set ssl options
        if (SharedMobileConfig::m_ignoreSSLErrors) 
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }
        
    }
    
    void MobileCurlNetwork::SetProxyOption(CURL *& curl)
    {
        Logger::debug("proxy: " + SharedMobileConfig::m_proxy);
        if (!SharedMobileConfig::m_proxy.empty())
        {
            curl_easy_setopt(curl, CURLOPT_PROXY, SharedMobileConfig::m_proxy.c_str());
        }
    }
    
    void MobileCurlNetwork::SetLastModifiedTimeStamp(long long timeStamp)
    {
        m_lastModifiedTimeStamp = timeStamp;
    }

}
