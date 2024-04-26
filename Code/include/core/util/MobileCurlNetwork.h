
#ifndef _BBMobileSDK_MobileCurlNetwork_H
#define _BBMobileSDK_MobileCurlNetwork_H

#include <map>

#include "curl.h"
#include "shared/callbacks/ProgressMeterCallback.h"
#include "core/log/Logger.h"
#include "core/http/RestResponse.h"
#include "core/file/FileObj.h"

namespace BBMobileSDK {
    
    BB_FORWARD_DECLARE(RestHeaderField);
    BB_FORWARD_DECLARE(CurlSharedObject);
    
    enum ContentType {
        ContentTypeRaw,
        ContentTypeJSON,
        ContentTypeForm
    };
    
    /**
     *  Networking class for Android that is built ontop of Curl
     */
    class MobileCurlNetwork {
    private:
        /**
         *  Curl method to take the HTTP response and store it in a String. This is the static method for C++ which calls the C callback
         *
         *  @param data  char* The actual data that was returned from the HTTP response
         *  @param size  size_t Size of the response
         *  @param nmemb size_t Size of each member
         *  @param p     void* Pointer to callback
         *
         *  @return size of handled content.
         */
        static size_t handle(char * data, size_t size, size_t nmemb, void * p);
        /**
         *  C method that actually takes the response and converts it to String
         *
         *  @param data  char* The actual data that was returned from the HTTP response
         *  @param size  size_t Size of the response
         *  @param nmemb size_t Size of each member
         *
         *  @return Returns the size of the string and updates a global string with content
         */
        size_t handle_impl(char * data, size_t size, size_t nmemb);
        
        static size_t cb_parse_headers_handle(char * data, size_t size, size_t nmemb, void *p);
        
        size_t cb_parse_headers_impl(char * data, size_t size, size_t nmemb);
        
        static size_t cb_write_file_handle(void *data, size_t size, size_t nmemb, void *p);
        size_t cb_write_file_impl(void *data, size_t size, size_t nmemb);
        
        /**
         *  Check the HTTP status code that was received and do the apporiate action
         *
         */
        void checkStatusCode();
        
        void BuildHttpHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers, bool usingGzip = false, bool contentTypeJson = true);
        
        void BuildFormHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers, bool usingGzip = false);
        
        void BuildCurlHeaders(curl_slist *& http_headers, const RestHeaderFieldVPtr &headers);
        
        static int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
        
        bool InitCurlCommonOps(CURL *&curl, CurlSharedObjectPtr &sharedObj, struct curl_slist *& httpHeaders, const std::string &urlString, const RestHeaderFieldVPtr &headers, bool isUsingGzip = false, ContentType contentType = ContentTypeJSON);
        
        void CleanUpCurl(CURL *curl, CurlSharedObjectPtr &sharedObj);
        
        void PerformAndCheckCurlResult(CURL *&curl, CurlSharedObjectPtr &sharedObj, RestResponsePtr & restResponse, bool hasCookie = false);
        
        void ZipData(const std::string & parameters, unsigned char *&dest, unsigned long &len, bool &isUsingGzip);
        
        void SetGzipOption(CURL *&curl, const std::string &parameters, unsigned char * dest, unsigned long len, bool isUsingGzip);
        
        void SetProgressOption(CURL *&curl);
        
    private:
       
        std::string url;
        long httpCode;
        std::string content;
        
        std::vector<RestHeaderField> m_responseHeaders;
        
        FILE *m_pDownloadFile;
        curl_off_t m_LengthOfResumeFile;
        
        sf_callback_progress_meter m_transferCallbackFunction;
        
        double m_previousUploadPercentage;
        
        int m_connectTimeout;
        int m_readTimeout;
        int m_abortTransfer;
        long long m_lastModifiedTimeStamp;
        
        static std::atomic<int> s_abortAllTransfer;
        
    public:
        /**
         *  Constructor to create object with no url
         */
        MobileCurlNetwork(int connectionTimeout, int readTimeout);

		virtual ~MobileCurlNetwork();

        void RegisterTransferCallback(sf_callback_progress_meter transferCallback);

        RestResponsePtr Get(const std::string & urlStr, const RestHeaderFieldVPtr &headers, bool usingGzip = false, bool contentTypeJson = true);

        RestResponsePtr Delete(const std::string & uri, const RestHeaderFieldVPtr & headers);
        
        RestResponsePtr Post(const std::string & uri, const std::string & parameters, const RestHeaderFieldVPtr & headers, bool usingGzip = false);
        
        RestResponsePtr Head(const std::string & uri, const RestHeaderFieldVPtr & headers);
        
        RestResponsePtr Put(const std::string & uri, const std::string & body, const RestHeaderFieldVPtr & headers, bool usingGzip = false);
        
        RestResponsePtr Patch(const std::string & uri, const std::string & body, const RestHeaderFieldVPtr & headers, bool usingGzip = false);

        RestResponsePtr Download(const std::string &urlStr, const std::string &path, const RestHeaderFieldVPtr & headers, curl_off_t resume_file_len = 0L);

        void AbortTransfer();

        static void ResetTransferStatusToContinue();
        static void AbortAllTransfer();
        
        RestResponsePtr UploadSingleFile(const std::string &uri, const FileObjPtr & file, const RestHeaderFieldVPtr & headers);
        
        RestResponsePtr PostForm(const std::string & uri, const std::string & parameters, const RestHeaderFieldVPtr & headers, bool usingGzip = false);
        
        
        void SetConnectOption(CURL *& curl);
        void SetSSLOption(CURL *& curl);
        void SetProxyOption(CURL *& curl);
        void SetLastModifiedTimeStamp(long long timeStamp);
    };
}
#endif
