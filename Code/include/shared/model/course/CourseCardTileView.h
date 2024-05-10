

#ifndef _BBMobileSDK_CourseCardTileView_H
#define _BBMobileSDK_CourseCardTileView_H

#include <memory>
#include <string>
#include <vector>

#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"
#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "shared/util/ToJsonFieldController.h"
#include "shared/model/SharedBaseResponse.h"


namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(CourseCardTileView)

    BB_FORWARD_DECLARE(Course)

    class CourseCardTileView : public SharedBaseResponse
    {
    public:
        CourseCardTileView();
        CourseCardTileView(const CourseVPtr &courses);
        virtual ~CourseCardTileView();
        CourseCardTileView(const CourseCardTileView &rhs);
        CourseCardTileView& operator = (const CourseCardTileView &rhs);


        void SetCourses(const CourseVPtr &courses);
        CourseVPtr GetCourses(void);


        virtual void FromJson(rapidjson::Value &json);
        virtual void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl = nullptr);

        std::string ToJsonString(ToJsonFieldControllerType jsonCtrlType = ToJsonFieldControllerType::ToServer);

    protected:

        virtual void ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                                         IToJsonFieldControllerPtr toJsonCtrl = nullptr);

    private:
        CourseVPtr m_Courses;
    };

}

#endif // _BBMobileSDK_CourseCardTileView_H
