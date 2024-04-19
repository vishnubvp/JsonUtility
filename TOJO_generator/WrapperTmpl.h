/**
 *
 * @file    BBMClassName.h
 * @brief   Declaration file for BBMClassName
 *
 */

#import <Foundation/Foundation.h>

PreDeclarationList
classComment
@interface BBMClassName : NSObject

VariableList

-(id) initWithSDKClass:(NSValue *)ClassObject;
-(void) toSDKObject:(NSValue *)value;
@end
