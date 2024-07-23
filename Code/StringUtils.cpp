

#include "core/util/StringUtils.h"

#include <string.h>
#include <zlib.h>

#include <algorithm>    // std::remove_if
#include <cctype>
#include <functional>

#include "core/log/Logger.h"

#ifdef _WIN32
#include "core/win32/WInStringUtils.h"
#include <wctype.h>
#endif

using namespace VSMobileSDK;


//
// StringUtils
//

std::string StringUtils::CombineStr(const std::string &separator, std::vector<std::string> list, bool separatorAtEnd)
{
    std::string builtStr = "";
    for(std::string elem : list)
    {
        builtStr += elem + separator;
    }
    if (!separatorAtEnd && list.size() > 0)
    {
        // double check
        if (StringUtils::EndsWith(builtStr, separator))
        {
            builtStr = builtStr.erase(builtStr.rfind(separator));
        }
    }
    return builtStr;
}

bool StringUtils::EndsWith(const std::string &str1, const std::string &str2)
{
    if (str2.empty())
        return true;
    auto pos = str1.rfind(str2);
    if (pos == std::string::npos)
        return false;
    return (pos == str1.size() - str2.size());
}

std::vector<std::string> StringUtils::Split(const std::string & s, const std::string & spliter)
{
    std::vector<std::string> svec;
    svec.reserve(100);
    
    size_t pos = 0;
    size_t start = 0;
    
    if (spliter.empty()) {
        Logger::error("string split should not be empty");
        svec.push_back(s);
        return svec;
    }
    
    while (pos != std::string::npos) {
        pos = s.find(spliter, start);
        
        std::string splited;
        
        if (pos == std::string::npos)
        {
            splited = s.substr(start);
        }
        else
        {
            splited = s.substr(start, pos - start);
        }
        
        svec.push_back(splited);
        start = pos + spliter.length();
    }
    
    return svec;
}

int StringUtils::CompareIgnoreCase(const std::string &lhs, const std::string &rhs)
{
#ifdef _WIN32
	std::wstring lwStr = WinStringUtils::utf8_decode(lhs);
	std::wstring rwStr = WinStringUtils::utf8_decode(rhs);

	for (int i = 0; i < lwStr.size() && i < rwStr.size(); i++) {
		if (!iswalnum(lwStr[i]) && !iswalnum(rwStr[i])) {
			if (lwStr[i] > rwStr[i]) {
				return 1;
			}
			if (lwStr[i] < rwStr[i]) {
				return -1;
			}
		} else if (!iswalnum(lwStr[i])) {
			return 1;
		} else if (!iswalnum(rwStr[i])) {
			return -1;
		} else {
			if (ToUpper(lwStr[i]) > ToUpper(rwStr[i])) {
				return 1;
			}
			if (ToUpper(lwStr[i]) < ToUpper(rwStr[i])) {
				return -1;
			}
		}
	}
    return (int)lwStr.size() - (int)rwStr.size();
#else
    for (int i = 0; i < lhs.size() && i < rhs.size(); i++) {
        if (!std::isalnum(lhs[i]) && !std::isalnum(rhs[i])) {
            if (lhs[i] > rhs[i]) {
                return 1;
            }
            if (lhs[i] < rhs[i]) {
                return -1;
            }
        } else if (!std::isalnum(lhs[i])) {
            return 1;
        } else if (!std::isalnum(rhs[i])) {
            return -1;
        } else {
            if (ToUpper(lhs[i]) > ToUpper(rhs[i])) {
                return 1;
            }
            if (ToUpper(lhs[i]) < ToUpper(rhs[i])) {
                return -1;
            }
        }
	}
    return (int)lhs.size() - (int)rhs.size();
#endif
}

KVPair StringUtils::KVPairFromStr(const std::string & s, const std::string & spliter)
{
    std::vector<std::string> kvp = Split(s, spliter);
    if (kvp.size() >= 1 && kvp.size() <= 2)
    {
        KVPair kvPair(Trim(kvp[0]), "");
        
        if (kvp.size() == 2)
        {
            kvPair.second = Trim(kvp[1]);
        }
        
        return kvPair;
    }
    
    KVPair emptyKvPair;
    return emptyKvPair;
}

std::string StringUtils::StrFromKVPairVector(std::vector<KVPair> & pairs, const std::string & firstSpliter, const std::string & secondSpliter)
{
    std::string s = "";
    
    if (pairs.empty())
    {
        return s;
    }
    
    for (int i = 0; i < pairs.size() - 1; i++)
    {
        KVPair pair = pairs.at(i);
        s += pair.first + secondSpliter + pair.second + firstSpliter;
    }
    
    // last one, we shouldn't add "firstSpliter" at end of string.
    KVPair lastPair = pairs[pairs.size() - 1];
    
    if (lastPair.second.empty())
    {
        s += lastPair.first;
    }
    else
    {
        s += lastPair.first + secondSpliter + lastPair.second;
    }
    
    return s;
}

std::vector<KVPair> StringUtils::KVPairsFromStr(const std::string & s, const std::string & firstSpliter, const std::string & secondSpliter)
{
    std::vector<std::string> splited = Split(s, firstSpliter);
    
    std::vector<KVPair> kvPairs;
    
    for (std::string kv : splited)
    {
        std::vector<std::string> kvp = Split(kv, secondSpliter);
        if (kvp.size() >= 1 && kvp.size() <= 2)
        {
            KVPair kvPair(Trim(kvp[0]), "");
            
            if (kvp.size() == 2)
            {
                kvPair.second = Trim(kvp[1]);
            }
            
            kvPairs.push_back(kvPair);
        }
    }
    
    return kvPairs;
}

std::string StringUtils::LTrim(const std::string & s, const char c)
{
    std::string str = s;
    std::function<bool(int)> equal_char = [c](char trim_c){ return trim_c == c;};
    string::iterator p = find_if(str.begin(), str.end(), not1(equal_char));
    str.erase(str.begin(),p);
    return str;
}

std::string StringUtils::RTrim(const std::string & s, const char c)
{
    std::string str = s;
    std::function<bool(int)> equal_char = [c](char trim_c){ return trim_c == c;};
    string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(equal_char));
    str.erase(p.base(), str.end());
    return str;
}


std::string StringUtils::Trim(const std::string & s, const char c)
{
    std::string str = s;
    std::string lTrimed = LTrim(str, c);
    std::string trimed = RTrim(lTrimed, c);
    return trimed;
}


bool StringUtils::GzipData(const std::string & str, unsigned char ** dest, unsigned long *len)
{
    unsigned long streamSize = str.length() / 2;
    *dest = (unsigned char *)calloc(streamSize, sizeof(unsigned char));
    
    unsigned long sourceLen = str.length();
    unsigned char * source = (unsigned char *)calloc(sourceLen, sizeof(unsigned char));
    memcpy(source, str.c_str(), sourceLen);
    
    // setup deflate stream
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = (unsigned int)sourceLen;
    stream.next_in = source;
    stream.total_out = 0;
    stream.avail_out = 0;
    
    unsigned long bytesAlready = stream.total_out;

    int status = deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, MAX_WBITS + 16, 8, Z_DEFAULT_STRATEGY);
    
    if (status != Z_OK)
    {
        Logger::error("compress failed!");
        
        BB_RELEASE(source);
        deflateEnd(&stream);
        return false;
    }
    
    bool result = false;
    while (stream.avail_out == 0)
    {
        // realloc more space for *dest
        // if the dest len is not large enough, this function will go to compression failed
        if (stream.total_out - bytesAlready >= streamSize)
        {
            streamSize = streamSize*2;
            *dest = (unsigned char *)realloc(*dest, streamSize);
        }
        
        stream.next_out = *dest + stream.total_out - bytesAlready;
        stream.avail_out = (uInt)(streamSize - (stream.total_out - bytesAlready));
        int status = deflate(&stream, Z_FINISH);
        
        if (status == Z_STREAM_END)
        {
            result = true;
            break;
        }
        else if (status != Z_OK)
        {
            result = false;
            break;
        }
    }
    streamSize = stream.total_out - bytesAlready;
    *len = streamSize;
    
    if (!result)
    {
        Logger::error("compress failed!");
    }
    
    deflateEnd(&stream);
    BB_RELEASE(source);
    
    return result;
}

bool StringUtils::GuzipData(unsigned char * src, unsigned long srcLen, std::string &destStr, unsigned long *pDestLen)
{
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = (uInt)srcLen;
    stream.next_in = src;
    stream.total_out = 0;
    stream.avail_out = 0;
    
    unsigned char * data = (unsigned char *)malloc(*pDestLen * sizeof(unsigned char));
    
    if (inflateInit2(&stream, MAX_WBITS + 32) == Z_OK)
    {
        int status = Z_OK;
        while (status == Z_OK)
        {
            stream.next_out = (uint8_t *)data + stream.total_out;
            stream.avail_out = (uInt)((*pDestLen) - stream.total_out);
            status = inflate (&stream, Z_SYNC_FLUSH);
        }
        if (inflateEnd(&stream) == Z_OK)
        {
            if (status == Z_STREAM_END)
            {
                *pDestLen = stream.total_out;
                std::string str((char *)data, *pDestLen);
                destStr = str;
                return true;
            }
        }
    }
    
    unsigned long bytesProcessedAlready = stream.total_out;
    while (stream.avail_in != 0) {
        
        stream.next_out = data + stream.total_out - bytesProcessedAlready;
        stream.avail_out = (unsigned int)(*pDestLen - (stream.total_out - bytesProcessedAlready));
        
        int status = inflate(&stream, Z_NO_FLUSH);
        
        if (status == Z_STREAM_END) {
            break;
        } else if (status != Z_OK) {
            return false;
        }
    }
    
    // Set real length
    *pDestLen = stream.total_out - bytesProcessedAlready;
    
    BB_RELEASE(data);
    
    return true;
}

unsigned char StringUtils::ToHex(unsigned char x)
{
    return  x > 9 ? (x + 'A' - 10) : (x + '0');
}

unsigned char StringUtils::FromHex(unsigned char x)
{
    unsigned char y = x;
    if (x >= 'A' && x <= 'Z')
    {
        y = x - 'A' + 10;
    }
    else if (x >= 'a' && x <= 'z')
    {
        y = x - 'a' + 10;
    }
    else if (x >= '0' && x <= '9')
    {
        y = x - '0';
    }
    
    return y;
}

int StringUtils::ToUpper(int ch)
{
#ifdef _WIN32
    if (ch >= 'a' && ch <= 'z')
        return ch + 'A' - 'a';
    return ch;
#else 
    return std::toupper(ch);
#endif
}

std::string StringUtils::ToLower(const std::string &str)
{
    std::string newStr(str.length(), ' ');
    std::transform(str.begin(), str.end(), newStr.begin(), ::tolower);
    return newStr;
}

bool StringUtils::StartWithAlpha(const std::string &str)
{
#ifdef _WIN32
    std::wstring lwStr = WinStringUtils::utf8_decode(str);
    return iswalpha(lwStr[0]);
#else
    return std::isalpha(str.at(0));
#endif
}

std::string StringUtils::UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

std::string StringUtils::UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+')
        {
            strTemp += ' ';
        }
        else if (str[i] == '%')
        {
            if(i + 2 < length)
            {
                unsigned char high = FromHex((unsigned char)str[++i]);
                unsigned char low = FromHex((unsigned char)str[++i]);
                strTemp += high*16 + low;
            }
        }
        else strTemp += str[i];
    }
    return strTemp;
}

/* refer to http://stackoverflow.com/questions/1634271/url-encoding-the-space-character-or-20
 * For HTTP URLs, a space in a path fragment part has to be encoded to "%20" (not, absolutely not "+"), while the "+" character in the path fragment part can be left unencoded.
 
    Now in the query part, spaces may be encoded to either "+" (for backwards compatibility: do not try to search for it in the URI standard) or "%20" while the "+" character (as a result of this ambiguity) has to be escaped to "%2B".
 */

std::string StringUtils::UrlEncodeForQueryString(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
        strTemp += str[i];
        else if (str[i] == ' ')
        strTemp += "%20";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

std::string StringUtils::ReplaceFirst(const std::string &originalStr, const std::string &oldVal, const std::string &newVal)
{
    if (originalStr.empty() ||
        oldVal.empty())
    {
        return originalStr;
    }
    auto strCopy = originalStr;
    auto pos = strCopy.find(oldVal);
    if (pos != std::string::npos)
    {
        strCopy.replace(pos, oldVal.length(), newVal);
    }
    return strCopy;
}

std::string StringUtils::ReplaceFromStr(const std::string &originalStr, const std::string &newVal, const std::string &startStr, const std::string &endStr)
{
    if (originalStr.empty() ||
        startStr.empty())
    {
        return originalStr;
    }
    std::string strCopy = originalStr;
    auto spos = originalStr.find(startStr);
    auto epos = originalStr.find(endStr,spos); //End string will be searched from the Starting position
    
    if (spos != std::string::npos && epos != std::string::npos)
    {
        unsigned long int posdiff = epos-spos + (endStr.length());
        if ( posdiff > 0)
            strCopy.replace(spos, posdiff, newVal);
    }
    return strCopy;
}

int StringUtils::VersionCompare(const std::string &v1, const std::string &v2) 
{ 
    // vnum stores each numeric 
    // part of version 
    int vnum1 = 0, vnum2 = 0; 
  
    // loop untill both string are 
    // processed 
    for (int i = 0, j = 0; (i < v1.length() 
                            || j < v2.length());) { 
        // storing numeric part of 
        // version 1 in vnum1 
        while (i < v1.length() && v1[i] != '.') { 
            vnum1 = vnum1 * 10 + (v1[i] - '0'); 
            i++; 
        } 
  
        // storing numeric part of 
        // version 2 in vnum2 
        while (j < v2.length() && v2[j] != '.') { 
            vnum2 = vnum2 * 10 + (v2[j] - '0'); 
            j++; 
        } 
  
        if (vnum1 > vnum2) 
            return 1; 
        if (vnum2 > vnum1) 
            return -1; 
  
        // if equal, reset variables and 
        // go for next numeric part 
        vnum1 = vnum2 = 0; 
        i++; 
        j++; 
    } 
    return 0; 
} 

