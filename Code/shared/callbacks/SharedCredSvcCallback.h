

#ifndef SHAREDCREDSVCCALLBACK_H_
#define SHAREDCREDSVCCALLBACK_H_

#include "core/util/TypeDefs.h"
#include "core/log/Logger.h"

BB_CALLBACK_DEF(RequestAuthorizationFailed, IBBRequestAuthorizationFailedCallback, void, void);

using UserCookieRefreshedCallback = std::function<void()>;

#endif /* SHAREDCREDSVCCALLBACK_H_ */
