

#include "shared/rest/CourseCardTileViewRestManager.h"
#include "shared/businessLogic/PerformanceTagger.h"
#include "core/external/rapidjson/document.h"
#include "core/http/RestResponse.h"
#include "core/util/Helpers.h"

#include "shared/rest/RestHelper.h"
#include "shared/rest/RestManager.h"
#include "shared/businessLogic/SharedCredSvcMgr.h"

using namespace std;

namespace BBMobileSDK
{

	CourseCardTileViewRestManager::CourseCardTileViewRestManager()
	{

	}

	CourseCardTileViewRestManager::~CourseCardTileViewRestManager()
	{
	}

	CourseCardTileViewRestManager::CourseCardTileViewRestManager(const CourseCardTileViewRestManager &rhs)
	{
	     *this = rhs;
	}

	CourseCardTileViewRestManager& CourseCardTileViewRestManager::operator = (const CourseCardTileViewRestManager &rhs)
	{
	    if (&rhs != this)
	    {
	    }

	    return *this;
	}
    RestResponsePtr CourseCardTileViewRestManager::GetFavoriteCourseIds()
     {
        RestManager restMgr({RestConst::CourseOutline::PATH_COURSE, RestConst::CourseOutline::KEY_FAVORITE_COURSE}, HttpMethod::Get);
        SharedMobilyticsManager::GetInstance().TagPerformance(PerformanceTag::ServerbaasCourseTimelineStart);
        RestResponsePtr response = restMgr.SendRestRequest();
        SharedMobilyticsManager::GetInstance().TagPerformance(PerformanceTag::ServerbaasCourseTimelineEnd);
        
        return response;
     }
    RestResponsePtr CourseCardTileViewRestManager::UpdateFavoriteCourseStatus(const std::map<std::string, bool> & courseIds)
    {
        return RestManager({RestConst::CourseOutline::PATH_COURSE, RestConst::CourseOutline::KEY_FAVORITE_COURSE}, HttpMethod::Post, CourseCardTileViewRestManager::JsonStringFromCourseIdsMap(courseIds)).SendRestRequest();
        
    }
    std::string CourseCardTileViewRestManager::JsonStringFromCourseIdsMap(const std::map<std::string, bool> & courseIds) const
    {
      
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            writer.StartArray();
        
            std::map<std::string, bool>::const_iterator it;
            for (it = courseIds.begin(); it != courseIds.end(); it++)
            {
                if(it->second == true ) //Send only the Courses that are favorite to Serverbaas
                {
                    writer.String(it->first.c_str());

                }
            }
        
            writer.EndArray();
            
            return buffer.GetString();
    }
   

}


