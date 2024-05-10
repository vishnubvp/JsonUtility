

#ifndef SDKShared_SharedInternalConst_h
#define SDKShared_SharedInternalConst_h

#include "core/external/rapidjson/reader.h"
#include "core/util/BaseInclude.h"
#include "core/util/bb_type_traits.h"


namespace BBMobileSDK
{
    
    namespace SDKState
    {
        constexpr int PreInit = 0;
        constexpr int Running = 1;
        constexpr int Stopped = 2;
    }
    
    
    namespace IntValueForType
    {
        constexpr int BOOL_TRUE  = 1;
        constexpr int BOOL_FALSE = 0;
    }

    namespace StringValueForType
    {
        constexpr const_string BOOL_TRUE  = "true";
        constexpr const_string BOOL_FALSE = "false";
        constexpr const_string STR_ONE = "1";
        
        constexpr const_string STR_WHITESPACE = " ";
        constexpr const_string STR_EMPY = "";
    }
    
    namespace SizeConst
    {
        constexpr long long SIZE_1k = 1024;
        constexpr long long SIZE_1M = 1024 * 1024;
    }
    
    enum HttpStatusCode
    {
        HttpStatusCodeNotConnectedToServer = 0,
        
        HttpStatusCodeContinue = 100,
        HttpStatusCodeSwitchingProtocol = 101,
        
        HttpStatusCodeOk = 200,
        HttpStatusCodeCreated = 201,
        HttpStatusCodeAccepted = 202,
        HttpStatusCodeNonAuthoritativeInformation = 203,
        HttpStatusCodeNoContent = 204,
        HttpStatusCodeResetContent = 205,
        HttpStatusCodePartialContent = 206,
        
        HttpStatusCodeMultipleChoices = 300,
        HttpStatusCodeMovedPermanently = 301,
        HttpStatusCodeFound = 302,
        HttpStatusCodeSeeOther = 303,
        HttpStatusCodeNotModified = 304,
        HttpStatusCodeUseProxy = 305,
        HttpStatusCodeUnused = 306,
        HttpStatusCodeTemporaryRedirect = 307,
        
        HttpStatusCodeBadRequest = 400,
        HttpStatusCodeUnauthorized = 401,
        HttpStatusCodePaymentRequired = 402,
        HttpStatusCodeForbidden = 403,
        HttpStatusCodeNotFound = 404,
        HttpStatusCodeMethodNotAllowed = 405,
        HttpStatusCodeNotAcceptable = 406,
        HttpStatusCodeProxyAuthenticationRequired = 407,
        HttpStatusCodeRequestTimeout = 408,
        HttpStatusCodeConflict = 409,
        HttpStatusCodeGone = 410,
        HttpStatusCodeLengthRequired = 411,
        HttpStatusCodePreconditionFailed = 412,
        HttpStatusCodeRequestEntityTooLarge = 413,
        HttpStatusCodeRequestURITooLong = 414,
        HttpStatusCodeUnsupportedMediaType = 415,
        HttpStatusCodeRequestedRangeNotSatisfiable = 416,
        HttpStatusCodeExpectationFailed = 417,
        HttpStatusCodeLocked = 423, //For Completed Courses
        
        HttpStatusCodeInternalServerError = 500,
        HttpStatusCodeNotImplemented = 501,
        HttpStatusCodeBadGateway = 502,
        HttpStatusCodeServiceUnavailable = 503,
        HttpStatusCodeGatewayTimeout = 504,
        HttpStatusCodeHTTPVersionNotSupported = 505,
        
        // internal http status code
        // apply for when the user cancels http request.
        HttpStatusCodeHTTPRequestAborted = 700
    };
    
    enum ServerMinorCode
    {
        ServerMinorErrorCodeCourseNotAccessible = 23,
        ServerMinorErrorCodeNoAttemptRemain = 200,
        ServerMinorErrorCodeAttemptAlreadySubmitted = 201,

        ServerMinorErrorCodeMessageNotFound = 213,

        ServerMinorCodeCredentialInvalidLicense = 301,
        ServerMinorCodeCredentialInvalidRole = 302,
        
        ServerMinorCodeSchoolUnavailable = 10001,
        ServerMinorCodeB2Unavailable = 10002,
        ServerMinorCodeB2NotSupportVsboard = 10004,
        
        // Student
        ServerMinorErrorCodeIPRestrictedToSubmitCourseWork = 10301,
        ServerMinorCodeDiscussionForumUnavailable = 10303,
        ServerMinorCodeCourseVisibilityUnsupport = 10304,
        ServerMinorCodeDiscussionForumDeleted = 10307,
        ServerMinorCodeDiscussionThreadUnavailable = 10308,
        ServerMinorCodeDiscussionThreadDeleted = 10309,
        ServerMinorCodeSubmissionAttemptCleared = 10310,
        ServerMinorCodeTestBadPassword = 10305, //bad password when user preview/start continue Test submission
        
        // Instructor
        ServerMinorCodeB2NotSupportBbInstructor = 30001,
        ServerMinorCodeLearnVersionNotSupportEntitlementCheck = 30002,
        ServerMinorCodeAppVersionTooLowToGrade =  30401,
        
        // BBID
        ServerMinorCodeRegisterInvalidEmail = 40101,
        ServerMinorCodeRegisterForbiddenSchoolEmail = 40102,
        ServerMinorCodeRegisterInvalidPassword = 40103,
        ServerMinorCodeRegisterEmailAlreadyExists = 40104,
        ServerMinorCodeLoginForbiddenSchoolEmail = 40105,
        ServerMinorCodeLoginInvalidEmail = 40106,
        ServerMinorCodeLoginEmailNotRegistered = 40107,
        ServerMinorCodeLoginIncorrectPassword = 40108,
        ServerMinorCodeLoginEmailNotVerified = 40109,
        
        // Apt
        ServerMinorErrorCodeExceedCreditsLimitation = 20301,
        ServerMinorErrorCodeAlreadyExistInTrem = 20302,
        ServerMinorErrorCodeNotExistInTrem = 20303,
        ServerMinorErrorCodeNoEnoughTerms = 20308
    };
    
    namespace RestConst
    {
        constexpr const_string PARAM_APP_TYPE = "appType";
        constexpr int MAX_REDIRECT_COUNT = 10;
        constexpr long TCP_KEEPALIVE_IDLE_SEC = 10L;
        constexpr long TCP_KEEPALIVE_INTVL_SEC = 1L;
        constexpr long long CURL_RETRY_TIMEOUT_MILLISEC = 2000LL;
        constexpr int DNS_CACHE_TIMEOUT_SEC = 120;
        
        enum AppType {
            AppTypeStudent = 0,
            AppTypeInstructor = 1
        };
        
        namespace ServerbaasVersion
        {
            constexpr const_string VERSION_1 = "v1";
            constexpr const_string VERSION_2 = "v2";
        }
        
        namespace Announcements
        {
            constexpr const_string PATH_ANNOUNCEMENTS = "announcements";
            constexpr const_string PATH_NOTIFICATIONS = "notifications";
            constexpr const_string PATH_COURSE = "courses";
            constexpr const_string KEY_ANNOUNCEMENT = "announcement";
            constexpr const_string KEY_TITLE = "title";
            constexpr const_string KEY_BODY = "body";
        }
        
        namespace Entitlements
        {
            constexpr const_string PATH_COURSES = "courses";
            constexpr const_string PATH_ENTITLEMENTS = "entitlements";
            constexpr const_string KEY_ENTITLEMENTS = "entitlements";
            constexpr const_string KEY_ENTITLEMENT_KEYS = "entitlementKeys";
            constexpr const_string KEY_IS_ORGANIZATION = "isOrganization";
        }
        
        namespace Organization
        {
            constexpr const_string PATH_ORGANIZATIONS = "organizations";
            constexpr const_string PARAM_IS_ORGANIZATION = "isOrganization";
        }
        
        namespace HeaderKeys
        {
            constexpr const_string COOKIE_KEY_SCHOOL_ID = "school_id";
            constexpr const_string COOKIE_KEY_SCHOOL_NAME = "sna";
            constexpr const_string COOKIE_KEY_USER_ID = "user_id";
            constexpr const_string KEY_COOKIE_VALUE_ENCODE = "CookieEncoded";
            constexpr const_string KEY_IS_PROSPECTIVE_STUDENT = "is-prospective-student";
            constexpr const_string COOKIE_KEY_SITE_ID = "site-id";
        }
        
        namespace SharedInstitutionConst
        {
            constexpr const_string PATH = "institutions/search";
            constexpr const_string PATH_PING = "institutions/ping";
            constexpr const_string KEY_Q = "q";
        }
        
        namespace SharedCredentialConst
        {
            constexpr const_string PATH_LOGIN = "credential/login";
            constexpr const_string PATH_POST_LOGIN = "credential/postLogin";
            constexpr const_string PATH_LOGOUT = "credential/logout";
            
            constexpr const_string KEY_USERNAME = "userName";
            constexpr const_string KEY_PASSWORD = "password";
            
            constexpr const_string PARAM_KEY_KEEP_ME_LOGGED_IN = "keepMeLogin";
            
            constexpr const_string PATH_LICENSE_CHECK = "licenses/userpay";
            constexpr const_string PATH_ROLE_CHECK = "licenses/instructorPermission";
        }
        
        namespace TOSConst
        {
            constexpr const_string PATH = "userAgreements";
        }
        
        enum class PathBuilderType
        {
            Default,
            ServerbaasV1,
            ServerbaasV2
        };

        enum class AllyPathBuilderType
        {
            Default,
            AllyV1
        };
        
        namespace Feedback
        {
            constexpr const_string PATH = "feedbacks";
            constexpr const char * const FeedbackCategoryValue[] = {"QUESTION_OTHER", "PROBLEM_ISSUE", "FEATURE_REQUEST", "FEEDBACK_GOOD", "OTHER_OTHER" };
        }

        namespace ResetPasswordConst
        {
            constexpr const_string PATH = "password/resetUrl";
            constexpr const_string KEY_REGISTRATION_ID = "registrationId";
            constexpr const_string SEPARATOR = "&";
        }

    }
    
    namespace SDKConstant
    {
        namespace Version
        {

            constexpr const_string SDK_BASIC_VERSION = "3.11.40";
            constexpr int SDK_BUILD_VERSION = 1;
            /**
             * Note:
             *  for release branch, the value is empty.
             *  for develop branch, the value is "dev".
             */
            constexpr const_string SDK_BRANCH_NAME ="";
            constexpr int CURRENT_DB_VERSION = 20;
            constexpr const_string MOBILYTICS_LOG_VERSION = "1";
        }
        
        namespace DB
        {
            constexpr const_string LOCAL_STORAGE_NAME = "bbstudent.db";
            constexpr const_string DATABASE_EXTENSION = "db";
#ifdef _WIN32
            constexpr int SQLITE3_TIMEOUT_MS = 1000;
#else
            constexpr int SQLITE3_TIMEOUT_MS = 200;
#endif
        }
        
        enum DataSource
        {
            Offline = 0,
            Online = 1
        };
    }
    
    namespace SharedDAOConst
    {
        namespace KV
        {
            constexpr const_string TABLE_SDK_BASIS = "sdk_basis";
            constexpr const_string TABLE_KV_CRED = "kv_cred";
            constexpr const_string TABLE_KV_UGC = "kv_ugc";
            constexpr const_string TABLE_KV_USER_CACHE = "kv_cache";
            constexpr const_string TABLE_KV_GLOBAL_CACHE = "kv_global_cache";
            constexpr const_string TABLE_KV_DISCUSSION = "kv_discussion";
            
            constexpr const_string COL_ID = "id";
            constexpr const_string COL_KEY = "kv_key";
            constexpr const_string COL_KEY2 = "kv_key2";
            constexpr const_string COL_VALUE = "kv_value";
            constexpr const_string COL_UPDATE_TIME = "update_time";
            
            constexpr const_string BCOL_ID = "#id";
            constexpr const_string BCOL_KEY = "#kv_key";
            constexpr const_string BCOL_KEY2 = "#kv_key2";
            constexpr const_string BCOL_VALUE = "#kv_value";
            constexpr const_string BCOL_UPDATE_TIME = "#update_time";
            
            constexpr const_string KEY_SDK_BASIS = BB_LABEL(shared.sdk_basis);
            
            constexpr const_string KEY_MY_SCHOOL = BB_LABEL(shared.cred.school);
            
            constexpr const_string KEY_MY_CREDENTIALS = BB_LABEL(shared.cred.credentials);
            constexpr const_string KEY_COURSE_GRADE = BB_LABEL(shared.course.grade);
            
        }
        
        namespace Announcements
        {
            constexpr const_string KEY_COURSE_ANNOUNCEMENTS = BB_LABEL(Shared.Announcements);
            constexpr const_string KEY_COURSE_ANNOUNCEMENT_REUSABLE_OBJECTS = BB_LABEL(Shared.AnnouncementsReUsableObject);
        }
        
        namespace Entitlements
        {
            constexpr const_string KEY_ENTITLEMENTS = BB_LABEL(Shared.Entitlements);
        }
        
        namespace CourseOverview
        {
            constexpr const_string KEY_DUE_ITEMS = BB_LABEL(CourseOverview.DueItems);
        }
        
        namespace Organization
        {
            constexpr const_string KEY_ORGANIZATION_TIMELINE = BB_LABEL(Organization.Timeline);
        }
        
        namespace Discussion
        {
            constexpr const_string KEY_DISSCUSSION_LIST = BB_LABEL(shared.discussion.list);
            constexpr const_string KEY_THREAD = BB_LABEL(shared.discussion.thread);
            constexpr const_string KEY_GROUP = BB_LABEL(shared.discussion.group);
            
            constexpr const_string KEY_POST = BB_LABEL(shared.discussion.post);
            constexpr const_string KEY_POST_REPLY = BB_LABEL(shared.discussion.postReply);
            
            constexpr const_string COL_TYPE = "type";
            constexpr const_string COL_COURSE_ID = "course_id";
            constexpr const_string COL_THREAD_ID = "thread_outline_id";
            constexpr const_string COL_POST_ID = "post_id";
            constexpr const_string COL_PARENT_POST_ID = "parent_post_id";
            constexpr const_string COL_REPLY_COUNT = "reply_count";
            constexpr const_string COL_REPLY_READ_COUNT = "reply_read_count";
            constexpr const_string COL_JSON_VALUE = "json_value";
            constexpr const_string COL_UPDATE_TIME = "update_time";
            
            constexpr const_string BCOL_TYPE = "#type";
            constexpr const_string BCOL_COURSE_ID = "#course_id";
            constexpr const_string BCOL_THREAD_ID = "#thread_outline_id";
            constexpr const_string BCOL_ASSIGNED_GROUP_ID = "#assigned_group_id";
            constexpr const_string BCOL_POST_ID = "#post_id";
            constexpr const_string BCOL_PARENT_POST_ID = "#parent_post_id";
            constexpr const_string BCOL_REPLY_COUNT = "#reply_count";
            constexpr const_string BCOL_REPLY_READ_COUNT = "#reply_read_count";
            constexpr const_string BCOL_JSON_VALUE = "#json_value";
            constexpr const_string BCOL_UPDATE_TIME = "#update_time";
            
            constexpr const_string POST_IDS_PLACEHOLDER = "#post_ids_placeholder";
            constexpr const_string PARENT_POST_IDS_PLACEHOLDER = "#parent_post_ids_placeholder";
        }
        
        namespace GradeCriteria
        {
            constexpr const_string KEY_GRADE_CRITERIA = BB_LABEL(shared.gradeCriteria);
        }
        
        namespace TOS
        {
            constexpr const_string KEY_TOS = BB_LABEL(shared.TOS);
        }
        
        namespace InstMetadata
        {
            constexpr const_string KEY_GRADEBASE_METADATA = BB_LABEL(inst.metadata.gradebase);
            constexpr const_string KEY_COURSE_ASSESSMENT_METADATA = BB_LABEL(inst.metadata.course_assessment);
            constexpr const_string KEY_ASSESSMENT_METADATA = BB_LABEL(inst.metadata.assessments);
            constexpr const_string KEY_SUBMISSION_METADATA = BB_LABEL(inst.metadata.submission);
            constexpr const_string KEY_OUTLINE_METADATA = BB_LABEL(inst.metadata.outlines);
        }
        
        namespace ServerDiven
        {
            constexpr const_string KEY_SERVER_DRIVEN_GRADE = BB_LABEL(shared.serverDriven.grade);
        }
        
        constexpr const_string SQLITE_BIND_SYMBOL = "?";
        constexpr const_string SQLITE_IN_SPERATOR = ",";
    }
    
    namespace CachingConst
    {
        constexpr const_string UNKNOWN_FILE_EXTENSION = "";
        constexpr const_string DOWNLOADING_FILE_EXTENSION = ".bbdownloading";
#ifndef _WIN32
        constexpr const_string DIRECTORY_SEPARATOR = "/";
        constexpr const char   DIRECTORY_SEPARATOR_CHAR = '/';
#else
        constexpr const_string DIRECTORY_SEPARATOR = "\\";
        constexpr const char   DIRECTORY_SEPARATOR_CHAR = '\\';
#endif
        
        constexpr const_string FILE_SEPARATOR = ".";
        constexpr const_string OFFLINE_FILE_CACHE_FOLDER = "courses";
        constexpr const_string DOWNLOAD_FILE_CACHE_FOLDER = "cache";
        constexpr const_string UNTITLED_FILE_NAME = "Untitled";
    }
    
    namespace DownloadConst
    {
        constexpr int MAX_DOWNLOAD_QUEUE = 3;
        constexpr const_string NOTIFY_KEY_COMPLETED_PREFIX = "Completed";
        constexpr const_string NOTIFY_KEY_PROGRESS_PREFIX = "Progress";
        constexpr const_string NOTIFY_KEY_SPLIT = "-";
        constexpr const_string POSIX_FOLDER_OF_OLD_VERSION_FILES = "_old";
        constexpr double ONE_HUNDRED_PERCENT = 100.00;
        constexpr int MAX_DOWNLOAD_FILES_FOR_ONLINE = 10;
        constexpr int LEGENCY_VERSION = 1;
        constexpr int CURRENT_VERSION = 0;
        // unit: Byte
        constexpr int MINIMUM_FREE_SPACE_FOR_DOWNLOAD = 10240;
    }
    
    namespace ProfileConst
    {
        namespace TileDataKey
        {
            namespace School
            {
                constexpr const_string SchoolId = "schoolId";
                constexpr const_string SchoolName = "schoolName";
                constexpr const_string SchoolInitial = "schoolInitial";
                constexpr const_string GraduationDate = "graduationDate";
                constexpr const_string Color = "color";
                constexpr const_string State = "state";
                constexpr const_string City = "city";
            }
            
            namespace Focus
            {
                constexpr const_string Study = "study";
                constexpr const_string Level = "focusLevel";
                constexpr const_string Degree = "degree";
            }
            
            namespace Hometown
            {
                constexpr const_string Hometown = "hometown";
            }
        }
        
        namespace TileDataVal
        {
            namespace Focus
            {
                constexpr const_string LevelMajor = "Major";
                constexpr const_string LevelMinor = "Minor";
                constexpr const_string LevelNeither = "Neither";
                
                constexpr const_string DegreeAssociates = "Associates";
                constexpr const_string DegreeBachelors = "Bachelors";
                constexpr const_string DegreeMinor = "Minor";
                constexpr const_string DegreeCertificate = "Certificate";
                constexpr const_string DegreeMasters = "Masters";
                constexpr const_string DegreePhD = "PhD";
            }
        }
    }

    namespace FTUEConst
    {
        constexpr int FTUE_TRUE = 1;
        constexpr int FTUE_FALSE = 0;
    }
    
    namespace SDPConst
    {
        constexpr const_string SDPKeyInstructorGradingConcurrentCourseDefault = "3";
        constexpr const_string SDPKeyInstructorGradingConcurrentAssessmentDefault = "5";
        constexpr const_string SDPKeyOfflineAutoSyncIntervalInSecondDefault = "300";
    }
    
    enum class AppType
    {
        BbStudent,
        BbInstructor
    };
    
    namespace PerformanceTagAttribute
    {
        constexpr const_string SubmissionId = "SubmissionId";
        constexpr const_string SubmissionState = "SubmissionState";
        constexpr const_string CourseId = "CourseId";
        constexpr const_string CourseOutlineId = "CourseOutlineId";
    }
    
    namespace PromptConst
    {
        constexpr const_string KEY_PROMPT = BB_LABEL(shared.prompt);
        
        enum PromptLocationType
        {
            PromptLocationTypeStream,
            PromptLocationTypeCourseOrOrgTimeline
        };
    }
    
    namespace EntitlementConst
    {
        namespace PermissionUID
        {
            constexpr const_string PermissionUID_ViewUnavailableCourse = "course.unavailable-course.VIEW";
            constexpr const_string PermissionUID_CreateAnnouncements = "course.announcements.CREATE";
            constexpr const_string PermissionUID_ViewDiscussionBoards = "course.cp_discussion.VIEW";
            constexpr const_string PermissionUID_SendEmailToAllInstructors = "course.email-all-instructors.EXECUTE";
            constexpr const_string PermissionUID_SendEmailToAllTAs = "course.email-all-tas.EXECUTE";
            constexpr const_string PermissionUID_SendEmailToSingleUser = "course.email-students.EXECUTE";
            constexpr const_string PermissionUID_SendEmailToAllUsers = "course.email-all-users.EXECUTE";
            constexpr const_string PermissionUID_ViewSendEmailTool = "course.email.EXECUTE";
            constexpr const_string PermissionUID_SendEmailToCourseMembersEvenTheyElectNotToRecieve = "course.email.override.privacy.VIEW";
            constexpr const_string PermissionUID_EditCourseMaterials = "course.content.MODIFY";
            constexpr const_string PermissionUID_ViewGradeBook = "course.gradebook.MODIFY";
        }
    }
    
    enum class CourseAssessmentMetadataFilter
    {
        NeedGrading = 0,
        Posted = 1,
        NoSubmission = 2,
        All,
        Max
    };
    constexpr const char * const CourseAssessmentMetadataFilterValue[] = {"NEEDS_GRADING", "POSTED", "NO_SUBMISSION", ""};
    static_assert(static_cast<size_t>(CourseAssessmentMetadataFilter::Max) == size_of_array(CourseAssessmentMetadataFilterValue),
                  "Size of CourseAssessmentMetadataFilterValue not equal to enum CourseAssessmentMetadataFilter");
    
    enum CourseAssessmentLoaderStatus
    {
        CourseAssessmentLoaderStatusNotStart,
        CourseAssessmentLoaderStatusRunning,
        CourseAssessmentLoaderStatusCanceled,
        CourseAssessmentLoaderStatusCompleted
    };
    
    namespace CourseWorkConst
    {
        constexpr const_string SUBMISSION_ID = "SUBMISSION_ID";
    }
    
    namespace DiscussionConst
    {
        constexpr const_string IS_COURSE_SUPPORT_DISCUSSION_FILE_ATTACHMENT = "IS_COURSE_SUPPORT_DISCUSSION_FILE_ATTACHMENT";
        constexpr const_string INITIAL_COMMENT_STATUS_DELETED = "DELETED";

    }
    
    namespace FileUploadConst
    {
        constexpr const int CHECK_DRIVE_UPLOADING_INTERVAL = 2;
        constexpr const int MAX_UPLOADING_TIME_FOR_SINGLE_CLOUD_FILE_IN_SEC = 5*60;
        
    }
    
    
    namespace Logging
    {
        constexpr const_string LOG_TAG = "mSDK";
        
        constexpr const_string CONSOLE_LOGGER_NAME = "CONSOLE_LOGGER";
        constexpr const_string FILE_LOGGER_NAME = "FILE_LOGGER";
    }
    
    const int RAPIDJSON_DEFAULT_PARSE_FLAG = rapidjson::kParseNumbersAsStringsFlag;
    
    namespace GradeDisplaySetting
    {
        enum class PageType
        {
            Course,
            Outline,
            Submission,
            Rubric,
            Question
        };
        
        namespace FieldName
        {
            constexpr const_string GRADE = "grade";
            constexpr const_string TOTAL_GRADE = "totalGrade";
            constexpr const_string CELL = "cell";
        }
        
        namespace Settings
        {
            constexpr const_string DIGIT_COUNT = "digitCount";
            constexpr const_string ROUNDING_MODE = "roundingMode";
            constexpr const_string INPUT_CHARACTER_COUNT = "inputCharacterCount";
            
        }
    }

    namespace RWDManifest
    {
        constexpr const_string CONTAINER_ID = "sdk_rwd_container";
        constexpr const_string CONTAINER_NAME = "manifest";
        constexpr const_string CONTAINER_FILENAME = "rwd-manifest.appcache";
        constexpr const_string CONATINER_EXTENSION = "appcache";
        constexpr const_string CONTAINER_PATH = "RWDContainer";
        constexpr const_string CONTAINER_VERSION = "version";
        constexpr const_string CONTAINER_ASSETS = "applicationAssets";
        constexpr const_string CONTAINER_RESOURCE_PATH = "resourcePath";
        constexpr const_string PATH = "path";
        constexpr const_string TYPE = "type";
    }
    namespace BannerImageConst
    {
        constexpr const_string ID = "0000";
        constexpr const_string FILENAME = "bannerImage";
    }

    namespace TelemetryConst
    {
        constexpr const_string TELEMETRY_OFFLINE_DOWNLOAD = "OFFLINE_DOWNLOAD";
        constexpr const_string TELEMETRY_MOBILE_STUDENT = "MOBILE-STUDENT";
        constexpr const_string TELEMETRY_COURSE = "COURSE";
        constexpr const_string TELEMETRY_OFFLINE_DOWNLOAD_SUCCESS = "success";
        constexpr const_string TELEMETRY_OFFLINE_DOWNLOAD_FAIL = "fail";
    }

    namespace TelemetryKey
    {
        constexpr const_string USER_AGENT = "UserAgent";
        constexpr const_string INSTANCE_ID = "InstanceId";
        constexpr const_string CLIENT_ID = "ClientId";
        constexpr const_string USER_ID = "UserId";        
        constexpr const_string CONTEXT_ID = "ContextId";        
        constexpr const_string CONTEXT_TYPE = "ContextType";        
        constexpr const_string CORRELATION_ID = "CorrelationId";        
        constexpr const_string DATE = "Date";        
        constexpr const_string ENVIRONMENT_ID = "EnvironmentId";        
        constexpr const_string OBJECT_ID = "ObjectId";        
        constexpr const_string OBJECT_TYPE = "ObjectType";        
        constexpr const_string PRODUCT_ID = "ProductId";        
        constexpr const_string RESULT = "Result";        
        constexpr const_string SCHEMA = "Schema";        
        constexpr const_string TYPE = "Type";        
        constexpr const_string USER_TYPE = "UserType";
        constexpr const_string CLASSIFICATION = "Classification";
    }

    namespace BBAssistConst
    {
        constexpr const_string PATH = "bbassist/status";
        constexpr const_string EXTENSION_ID = "bbAssist";
    }
}

#endif

