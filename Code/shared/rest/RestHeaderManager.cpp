

#include "shared/rest/RestHeaderManager.h"

#include "core/config/SharedMobileConfig.h"
#include "core/http/RestHeaderField.h"
#include "core/notification/NotificationCenter.h"
#include "core/util/StringUtils.h"
#include "shared/const/NotificationNames.h"
#include "shared/model/credential/SharedCredentials.h"
#include "shared/rest/RestManager.h"

namespace BBMobileSDK
{    
    RestHeaderManager::RestHeaderManager()
    : m_mtx()
    , m_restHeaders()
    {
        AddObserver();
    }
    
    RestHeaderManager::~RestHeaderManager()
    {
    }
    
    RestHeaderFieldVPtr RestHeaderManager::GetHeaders()
    {
        // use recursive lock here to avoid headers be modified after empty detect is true
        BBRecursiveScopeLock recurive_lock(m_mtx);
        if (m_restHeaders.empty())
            RefreshHeader();
        return m_restHeaders;
    }
    
    void RestHeaderManager::RefreshHeader()
    {
        BBRecursiveScopeLock recurive_lock(m_mtx);
        if (!m_restHeaders.empty())
            m_restHeaders.clear();
        
        m_restHeaders.push_back(std::make_shared<RestHeaderField>(RestHeaderKeys::KEY_USER_AGENT,
                                                                  StringUtils::UrlEncode(RestManager::GetUserAgentFromConfig())));
        m_restHeaders.push_back(std::make_shared<RestHeaderField>(RestConst::HeaderKeys::KEY_COOKIE_VALUE_ENCODE,
                                                                  StringValueForType::BOOL_TRUE));
        m_restHeaders.push_back(std::make_shared<RestHeaderField>(RestHeaderKeys::KEY_ACCEPT_LANGUAGE,
                                                                  SharedMobileConfig::m_Locale));
        //SharedCredSvcMgr credMgr;
        //auto myCred = credMgr.GetMyCredentials();
        // if (myCred && myCred->GetIsLoggedIn())
        // {
        //     m_restHeaders.push_back(std::make_shared<RestHeaderField>(RestConst::HeaderKeys::KEY_IS_PROSPECTIVE_STUDENT,
        //                                                               myCred->GetIsProspectiveStudent() ? StringValueForType::BOOL_TRUE : StringValueForType::BOOL_FALSE));
        // }
        // m_restHeaders.push_back(std::make_shared<RestHeaderField>(RestConst::HeaderKeys::COOKIE_KEY_SITE_ID,
        //                                                           myCred->GetSiteId()));
    }
    
    void RestHeaderManager::AddObserver()
    {
        NotificationCenter::AddObserver(NotificationNames::REFRESH_REST_HEADER,
                                        this,
                                        [this](void*){
                                            RefreshHeader();
                                        });
    }
}
