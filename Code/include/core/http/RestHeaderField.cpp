
#include "core/http/RestHeaderField.h"

using namespace BBMobileSDK;

RestHeaderField::RestHeaderField()
: Name("")
, Value("")
{
    
}

RestHeaderField::RestHeaderField(const std::string & name, const std::string & value)
: Name(name)
, Value(value)
{
    
}

RestHeaderField::RestHeaderField(const RestHeaderField & rhs)
{
    *this = rhs;
}

RestHeaderField& RestHeaderField::operator = (const RestHeaderField & rhs)
{
    if (&rhs != this)
    {
        Name = rhs.Name;
        Value = rhs.Value;
    }
    return *this;
}


RestHeaderField::~RestHeaderField()
{
    
}

std::string RestHeaderField::toString()
{
	return this->Name + ": " + this->Value;
}

std::string RestHeaderField::TrimHeaderString(const std::string & headerStr)
{
    std::string newStr = headerStr;
    newStr = StringUtils::Trim(newStr, '\n');
    newStr = StringUtils::Trim(newStr, '\r');
    newStr = StringUtils::Trim(newStr);
    return newStr;
}

RestHeaderField RestHeaderField::InstanceFromHeaderString(const std::string & headerString)
{
    auto firstColon = headerString.find_first_of(':');
    
    if (firstColon == std::string::npos)
        return RestHeaderField(TrimHeaderString(headerString), "");
    
    std::string name = headerString.substr(0, firstColon);
    std::string value = (firstColon != headerString.length() - 1) ? headerString.substr(firstColon + 1) : "";
    return RestHeaderField(TrimHeaderString(name), TrimHeaderString(value));
}
