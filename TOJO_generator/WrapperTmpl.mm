/**
 *
 * @file    BBMClassName.mm
 * @brief   Definition file for BBMClassName
 *
 */

#import "ProjectName/model/SDKSubPath.h"

IncludeList

@implementation BBMClassName : NSObject

-(id) initWithClassName:(NSValue *)ClassObject {
    self = [BaseClassInitList];
    if(self)
    {
DefaultInitializationList
    }
    return self ;
}


-(void) toSDKObject:(NSValue *)value
{
    if(self)
    {
        BBMobileSDK::SDKClass *ClassObjectObj = (BBMobileSDK::SDKClass*)[value pointerValue];
        if (ClassObjectObj == NULL)
        {
            return;
        }
        
ToSDKObjectList
        
    }
    return ;
}

MethodImpl

@end
