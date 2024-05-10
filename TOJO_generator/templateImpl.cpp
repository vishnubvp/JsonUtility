/**
 *
 * @file    ClassName.cpp
 * @brief   Definition file for ClassName
 *
 */

#include "limits.h"
#include "core/util/Helpers.h"

JsonIncludeList

namespace BBMobileSDK
{

    ClassName::ClassName()
    DefaultInitializationList
    {
        ModelUtil::InitValue(this);
    }
    
ConstructorWithParameterImpl
    
    ClassName::~ClassName()
    {
    }

    ClassName::ClassName(const ClassName &rhs)
    {
         *this = rhs;
    }

    ClassName& ClassName::operator = (const ClassName &rhs)
    {
        if (&rhs != this)
        {
            AssignmentList
        }

        return *this;
    }

MethodImpl
    
JsonImplementation

}


