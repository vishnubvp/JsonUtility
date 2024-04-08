/**
 *
 * @file    ClassName.h
 * @brief   Declaration file for ClassName
 *
 */

#ifndef _VSTestSDK_ClassName_H
#define _VSTestSDK_ClassName_H

#include <memory>
#include <string>
#include <vector>

#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"
#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "shared/util/ToJsonFieldController.h"

IncludeList
namespace VSTestSDK
{
    BB_FORWARD_DECLARE(ClassName)
PtrDefList
    class ClassName BaseClassList
    {
    public:
        ClassName();
ConstructorWithParameterDeclare
        virtual ~ClassName();
        ClassName(const ClassName &rhs);
        ClassName& operator = (const ClassName &rhs);

MethodDeclaration
JsonDeclaration
    protected:
JsonProtectedDeclaration
    private:
        VariableList
    };

}

#endif // _VSTestSDK_ClassName_H
