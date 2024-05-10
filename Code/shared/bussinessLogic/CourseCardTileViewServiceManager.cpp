

#include "shared/bussinessLogic/CourseCardTileViewServiceManager.h"

#include "RestResponse.h"
#include "core/util/BasicUtils.h"
#include "core/util/Helpers.h"
#include "core/util/InternalConstData.h"
#include "core/log/Logger.h"
#include "core/util/TimeUtils.h"
#include "CourseCardTileViewRestManager.h"
#include "RestHelper.h"

namespace BBMobileSDK
{

    // MARK: Class CourseCardTileViewServiceManager implementation
    CourseCardTileViewServiceManager::CourseCardTileViewServiceManager()
    :m_CourseCardTileViewRestMgr(new CourseCardTileViewRestManager())
    {
    }
    
    CourseCardTileViewServiceManager::~CourseCardTileViewServiceManager()
    {
    }
    
  
    
    SharedBaseResponsePtr CourseCardTileViewServiceManager::UpdateFavoriteCourseStatus(const std::map<std::string, bool> & courseIds)
    {
        CourseCardTileViewPtr serviceResponse(new CourseCardTileView);

        CourseCardTileViewRestManager courseCardTileViewRestMgr;

        long long cacheUpdateTime = 0LL;
        std::map<std::string,bool> favcourseIdsMap;
        std::map<std::string,bool> favcourseIdsFromCache;
        std::map<std::string,bool>::const_iterator itr = courseIds.begin();
        
        
        Logger::debug("Favorite CourseIds Received for Update" + courseCardTileViewRestMgr.JsonStringFromCourseIdsMap(courseIds));
        //favcourseIdsMap = courseTimelineSvcMgr.GetFavoriteCoursesFromLocal(cacheUpdateTime); // This is data will be received from a separate api 
       
        //To Maintain the Copy of data inserting the data in below map if the API Call Failed.
        favcourseIdsFromCache.insert(favcourseIdsMap.begin(), favcourseIdsMap.end());

        // while (itr != courseIds.end())
        // {
        //     std::string courseIdWithoutUltra;
        //     courseIdWithoutUltra = RemoveUltraKeyword(itr->first);
        //     if(itr->second == true)
        //     {
        //         favcourseIdsMap.insert(std::make_pair(courseIdWithoutUltra,true));
        //     }
        //     else
        //     {
        //         std::map<std::string,bool>::iterator innerit = favcourseIdsMap.begin();
        //         innerit=favcourseIdsMap.find(courseIdWithoutUltra);
        //         if(innerit != favcourseIdsMap.end())
        //             favcourseIdsMap.erase(innerit);
                
        //     }
        //     itr++;
        // }

        //Update the Table Before API Call
        //The Table will have the Existing Course Ids from Local and the new CourseIds Changed from Frontend
        std::string jsonStrForCache="{\"favoriteCourseIds\":";
        std::string temp = courseCardTileViewRestMgr.JsonStringFromCourseIdsMap(favcourseIdsMap);
        jsonStrForCache.append(temp);
        jsonStrForCache.append("}");
        
        //SqliteResponsePtr sqliteResponse = m_KVPairDAOMgr->AddOrUpdateIfExists(KVDAOConst::KEY_FAVORITE_COURSES, jsonStrForCache);
        
        RestResponsePtr restResponse = m_CourseCardTileViewRestMgr->UpdateFavoriteCourseStatus(favcourseIdsMap);

        RestHelper::MapRestResponseToServiceResponse(restResponse, serviceResponse);
        
        if (ResponseCodeOk != serviceResponse->GetErrorCode())
        {
            //Revert the Cache with Older Values if Favorite Updation Failed
            std::string oldJsonStrForCache="{\"favoriteCourseIds\":";
            std::string temp = courseCardTileViewRestMgr.JsonStringFromCourseIdsMap(favcourseIdsFromCache);
            oldJsonStrForCache.append(temp);
            oldJsonStrForCache.append("}");
            //favcourseIdsMap = courseTimelineSvcMgr.GetFavoriteCoursesFromLocal(cacheUpdateTime);
            return serviceResponse;
        }
        
        //favcourseIdsMap = courseTimelineSvcMgr.GetFavoriteCoursesFromLocal(cacheUpdateTime); // This is data will be received from a separate api

        return serviceResponse;
        
    }

    SharedBaseResponsePtr CourseCardTileViewServiceManager::UpdateSingleFavoriteCourseStatus(const std::string &courseId, bool Favoritestatus)
    {
        SharedBaseResponsePtr serviceResponse; //(new SharedBaseResponse);
        std::map<std::string, bool>  courseIdss;
        courseIdss.insert(std::make_pair(courseId,Favoritestatus)); //Whenever a Single Course Id is passed from Frontend SDK itself will frame a map and pass
        serviceResponse = UpdateFavoriteCourseStatus(courseIdss);
        
        return serviceResponse;
        
    }



    
}

