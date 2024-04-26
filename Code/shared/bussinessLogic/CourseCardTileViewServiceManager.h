

#ifndef CourseCardTileViewSERVICEMANAGER_H_
#define CourseCardTileViewSERVICEMANAGER_H_

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "shared/const/SharedConst.h"

namespace VSTestSDK
{
    BB_FORWARD_DECLARE(CourseCardTileView)
    BB_FORWARD_DECLARE(CourseCardTileViewRestManager)
    BB_FORWARD_DECLARE(SharedBaseResponse)
    BB_FORWARD_DECLARE(Course)
    BB_FORWARD_DECLARE(KeyValuePairDAOManager)
    BB_FORWARD_DECLARE(SqliteResponse)
    
	class CourseCardTileViewServiceManager
	{
    public:
        CourseCardTileViewServiceManager();
        virtual ~CourseCardTileViewServiceManager();
        
    public:
        
        std::string RemoveUltraKeyword(const std::string &courseId);
        SharedBaseResponsePtr UpdateFavoriteCourseStatus(const std::map<std::string, bool> & courseIds);
        SharedBaseResponsePtr UpdateSingleFavoriteCourseStatus(const std::string &courseId, bool status);
        bool CheckIsCourseFavorite(const std::string &courseId);
        
    private:
        CourseCardTileViewRestManagerPtr m_CourseCardTileViewRestMgr;
        KeyValuePairDAOManagerPtr m_KVPairDAOMgr;
        
	};

	GLB_SMART_PTR_DEF(CourseCardTileViewServiceManager);
}



#endif /* CourseCardTileViewSERVICEMANAGER_H_ */
