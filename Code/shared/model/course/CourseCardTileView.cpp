

#include "limits.h"
#include "core/util/Helpers.h"

#include "shared/model/course/CourseCardTileView.h"
#include "shared/model/SharedBaseResponse.h"
#include "shared/model/course/Course.h"
#include "shared/util/SharedModelUtil.h"

namespace BBMobileSDK
{

    CourseCardTileView::CourseCardTileView()
    : m_Courses()
    , SharedBaseResponse()
    {
        ModelUtil::InitValue(this);
    }
    

    CourseCardTileView::CourseCardTileView(const CourseVPtr &courses)
    : m_Courses(courses)
    , SharedBaseResponse()
    {

    }


    CourseCardTileView::~CourseCardTileView()
    {
    }

    CourseCardTileView::CourseCardTileView(const CourseCardTileView &rhs)
    {
         *this = rhs;
    }

    CourseCardTileView& CourseCardTileView::operator = (const CourseCardTileView &rhs)
    {
        if (&rhs != this)
        {
            m_Courses = rhs.m_Courses; 
            SharedBaseResponse::operator=(rhs);
        }

        return *this;
    }


    void CourseCardTileView::SetCourses(const CourseVPtr &courses)
    {
        m_Courses = courses;
    }

    CourseVPtr CourseCardTileView::GetCourses(void)
    {
        return m_Courses;
    }

    

    void CourseCardTileView::FromJson(rapidjson::Value &jsonItems)
    {
        if (!jsonItems.IsNull())
        {
            //JsonHelper::FromJson(m_NeedAttention, jsonItems, "needAttention");
            // m_Credits = Helpers::CheckIntegerValue(jsonItems, "credits");
            // m_SerialCode = Helpers::CheckStringValue(jsonItems, "serialCode");
        }
      if (!jsonItems.IsNull())
        {
            
            if (!Helpers::IsInvalidItem(jsonItems, "courses"))
            {
                if (jsonItems["courses"].IsArray())
                {
                    CourseVPtr courses;
                    for (int i=0; i<jsonItems["courses"].Size(); i++)
                    {
                        if (!jsonItems["courses"][i].IsNull())
                        {
                            CoursePtr coursesItem(new Course);
                            coursesItem->FromJson(jsonItems["courses"][i]);
                            courses.push_back(coursesItem);
                        }
                    }

                    m_Courses = courses;
                }
            }

        }

    }

    void CourseCardTileView::ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl)
    {
        writer.StartObject();
        ToJsonWithoutObject(writer, toJsonCtrl);
        writer.EndObject();
    }

    void CourseCardTileView::ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer, IToJsonFieldControllerPtr toJsonCtrl)
    {

        writer.String("courses");
        writer.StartArray();
        for (CourseVPtr::const_iterator iter = m_Courses.begin(); iter != m_Courses.end(); ++iter)
        {
            (*iter)->ToJson(writer);
        }
        writer.EndArray();
    }
    
    std::string CourseCardTileView::ToJsonString(ToJsonFieldControllerType jsonCtrlType)
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        auto toJsonCtrl = ToJsonFieldControllerFactory::GetToJsonFieldController(jsonCtrlType);
        ToJson(writer, toJsonCtrl);

        return buffer.GetString();
    }


}


