


#include "core/util/StringWrapper.h"

namespace VSMobileSDK
{
	StringWrapper::StringWrapper()
	{}

	StringWrapper::StringWrapper(std::string& str)
	{
		m_str = str;
	}

	StringWrapper::StringWrapper(const char* chstr)
	{
		m_str = chstr;
	}

	StringWrapper::~StringWrapper()
	{}

	StringWrapper::operator std::string()
	{
		return m_str;
	}

	StringWrapper::operator const char*()
	{
		return m_str.c_str();
	}

	StringWrapper StringWrapper::operator =(std::string & rhs)
	{
		m_str = rhs;
		return *this;
	}

	StringWrapper& StringWrapper::operator= (StringWrapper&& wrapper)
	{
		if (&wrapper != this)
		{
			m_str = std::move(wrapper.m_str);
		}

		return *this;
	}

	StringWrapper& StringWrapper::operator= (const StringWrapper & wrapper)
	{
		if (&wrapper != this)
		{
			m_str = wrapper.m_str;
		}

		return *this;
	}

	StringWrapper::StringWrapper(const StringWrapper & wrapper)
	{
		if (&wrapper != this)
		{
			m_str = wrapper.m_str;
		}
	}

	std::string StringWrapper::GetString()
	{
		return m_str;
	}

	void StringWrapper::SetString(const std::string & str)
	{
		m_str = str;
	}

	std::vector<std::string> StringWrapper::ConvertToStdVec(const std::vector<StringWrapper> & wrapperVec)
	{
		std::vector<std::string> stdVec;
		for (StringWrapper wrap : wrapperVec)
		{
			stdVec.push_back(wrap.GetString());
		}

		return stdVec;
	}

	std::vector<StringWrapper> StringWrapper::ConvertToWrapVec(std::vector<std::string> & stdVec)
	{
		std::vector<StringWrapper> wrapVec;
		for (std::string str : stdVec)
		{
			wrapVec.push_back(StringWrapper(str));
		}

		return wrapVec;
	}
    
#ifdef ANDROID
    std::vector<StringWrapper> StringWrapper::ConvertToProperStringVec(std::vector<std::string> & stdVec)
    {
        return ConvertToWrapVec(stdVec);
    }
    
    std::vector<std::string> StringWrapper::ConvertPlatformSpecificStrsToStdVec(std::vector<StringWrapper> &strWraps)
    {
        return ConvertToStdVec(strWraps);
    }
#endif
    
    void StringWrapper::ConvertMapToVec(const std::map<std::string, std::string> & map, std::vector<StringWrapper> & wrapperVec)
    {
        for (std::pair<std::string, std::string> p: map)
        {
            wrapperVec.push_back(p.first);
            wrapperVec.push_back(p.second);
        }
    }
    void StringWrapper::ConvertVecToMap(const std::vector<StringWrapper> & wrapperVec, std::map<std::string, std::string> & map)
    {
        //avoid invalid vector which contains odd number of elements
        int pairCount = (int)wrapperVec.size() / 2;
        
        for (int i = 0; i < pairCount; i++)
        {
            std::string key = ((StringWrapper)wrapperVec[2*i]).GetString();
            std::string value = ((StringWrapper)wrapperVec[2*i+1]).GetString();
            map.insert(std::make_pair(key,value));
        }
    }

}
