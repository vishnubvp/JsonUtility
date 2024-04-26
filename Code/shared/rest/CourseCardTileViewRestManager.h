

#ifndef _VSTestSDK_CourseCardTileViewRestManager_H
#define _VSTestSDK_CourseCardTileViewRestManager_H

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

#include "shared/rest/CourseCardTileViewRestManager.h"

namespace VSTestSDK
{
    BB_FORWARD_DECLARE(RestResponse)

    class CourseCardTileViewRestManager
    {
    public:
        CourseCardTileViewRestManager();
        ~CourseCardTileViewRestManager();
        CourseCardTileViewRestManager(const CourseCardTileViewRestManager &rhs);
        CourseCardTileViewRestManager& operator = (const CourseCardTileViewRestManager &rhs);

        RestResponsePtr GetFavoriteCourseIds();
        RestResponsePtr UpdateFavoriteCourseStatus(const std::map<std::string, bool> & courseIds);
        std::string JsonStringFromCourseIdsMap(const std::map<std::string, bool> & courseIds) const;


    private:
        //std::string BuildBodyForPutFavoriteCourses(const CourseVPtr &course);

    };

}

#endif // _VSTestSDK_CourseCardTileViewRestManager_H
