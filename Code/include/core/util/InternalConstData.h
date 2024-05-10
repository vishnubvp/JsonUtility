

#ifndef VsboardMobile_InternalConstData_h
#define VsboardMobile_InternalConstData_h

#include "shared/const//SharedInternalConst.h"
#include "core/util/TypeDefs.h"
#include <string>
#include <vector>

namespace BBMobileSDK
{
    
    namespace CourseConst
    {
        const std::vector<std::string> CourseColorPalette = {"#c56fd5", "#26d7fd", "#ffe300", "#ff6600", "#2075a3", "#39e379", "#ffe300", "#ff9600", "#157afb", "#14c6cc", "#85f3da", "#80f56b", "#ff5991","#cc14ae"};
        
        enum VisibilityHolderType
        {
            LocalSDK = 0,
            Server = 1,
            Unknown = INT_MAX
        };
    }
    
    namespace TimelineConst
    {
        constexpr int ServerTimelineType_PAST = 0;
        constexpr int ServerTimelineType_CURRENT = 1;
        constexpr int ServerTimelineType_UPCOMING = 2;
    }
    
    
    namespace MobilyticsConst
    {
        constexpr int MOBILYTICS_BACKGROUND_SESSION_TIMEOUT_SEC = 2*60;
        constexpr int MOBILYTICS_REPEAT_UPLOAD_TIMEOUT_SEC = 60;
        constexpr int MOBILYTICS_UPLOADED_THRESHOLD = 50;
        
        constexpr const_string MOBILYTICS_DOWNLOAD_CLOUD_FILE_SIZE_KEY = "fileSize";
        constexpr const_string MOBILYTICS_DOWNLOAD_CLOUD_FILE_TYPE_KEY = "fileType";
        constexpr const_string MOBILYTICS_DOWNLOAD_CLOUD_FILE_NAME_KEY = "fileName";
        constexpr const_string MOBILYTICS_DOWNLOAD_CLOUD_FILE_PROVIDER_KEY = "attachmentProvider";
        
        namespace Event
        {
            constexpr const_string MOBILYTICS_DOWNLOAD_CLOUD_FILE = "DOWNLOAD_CLOUD_FILE";
        }
    }
    
    namespace ResponseErrorMessage
    {
        constexpr const_string SYSTEM_ERROR = "System not responding. Please try again later.";
        constexpr const_string CONNECTION_ERROR = "Connection error. Please verify you are connected to the internet and try again.";
        constexpr const_string FTW_401_ERROR = "Is forceToWeb authentication, please login by web page";
    }
    
    enum HttpMethod
    {
        Get = 0,
        Post,
        PostUsingGzip,
        PostForm,
        Head,
        Put,
        Delete,
        Option,
        Patch,
        UploadSingleFile,
        Download
    };
    
    enum TaskState
    {
        None = 0,
        Running,
        Pause,
        Stop,
        Unknown,
    };
    
    namespace KVDAOConst
    {
        constexpr const_string KEY_COURSE_TIMELINES = "CoursesOfCourseTimeline";
        constexpr const_string KEY_STREAM_SECTIONS = "StreamSections";
        constexpr const_string KEY_STREAM_SECTIONS_COUNT = "StreamSectionsCount";
        constexpr const_string KEY_STREAM_VALUE_PROVIDERS = "sv_providers"; //sv_providers
        constexpr const_string KEY_STREAM_UNREADCOUNT = "StreamUnreadCount";
        constexpr const_string KEY_PROFILE_PREFIX = "SqlKeyProfile_";
        constexpr const_string KEY_PROFILE_AVATAR_PREFIX = "SqlKeyProfileAvatarPermission_";
        constexpr const_string KEY_PROFILE_MYUSERINFO_PREFIX DEPRECATED = "ProfileMyUserInfoKeyPrefix_";
        constexpr const_string KEY_PROFILE_LOCAL_TILES = BB_LABEL(KV.profile.tile.localhack);
        constexpr const_string KEY_GRADE_COURSES = "GradedCourses";
        constexpr const_string KEY_GRADE_SUBMISSIONS = "GradedSubmissions_";
        constexpr const_string KEY_PUSH_NOTIFICATION_SETTINGS = "PushNotificationSettings";
        
        constexpr const_string KEY_OUTLINE_PREFIX = "OutlineKeyPrefix_";
        constexpr const_string KEY_MEMBERSHIP_PREFIX = "MembershipsPrefix_";

        constexpr const_string KEY_OAUTH_TOKEN_PREFIX = "OAuthTokenKeyPrefix_";
        constexpr const_string KEY_OAUTH_CLIENT_INFO_PREFIX = "OAuthClientInfoKeyPrefix_";
        constexpr const_string KEY_OAUTH_USER_INFO_PREFIX = "OAuthUserInfoKeyPrefix_";
        
        constexpr const_string KEY_PREVIOUS_SCHOOL_ID = BB_LABEL(KV.Previous_School_Id);
        constexpr const_string KEY_FEATURE_LIST_ID = BB_LABEL(kv.feature_list);
        
        constexpr const_string KEY_COURSE_DETAILS_PREFIX = "CourseDetails_";
        
        constexpr const_string KEY_COURSE_GRADE_PREFIX = "CourseGrade_";
        
        constexpr const_string KEY_HIDE_COURSES = "HideCourses";
        constexpr const_string KEY_HIDE_ORGANIZATIONS = "HideOrganizations";
        constexpr const_string KEY_SHOW_HIDE_UPLOAD = "ShowHidenShouldUpload";
        constexpr const_string KEY_ORG_SHOW_HIDE_UPLOAD = "OrganizationShowHidenShouldUpload";
   	
        constexpr const_string KEY_OFFLINE_COURSE_METADATA = "OfflineCourseMetadata";
        constexpr const_string KEY_FAVORITE_COURSES = "FavoriteCourses";
        constexpr const_string KEY_DESCRIPTION_EXPANDED_STATUS = "ContentExpandedStatus";
        constexpr const_string KEY_GRADE_EXPANDED_STATUS = "GradeExpandedStatus";
        constexpr const_string KEY_FEEDBACK_EXPANDED_STATUS = "FeedbackExpandedSatus";
        constexpr const_string KEY_REFRESH_COURSE_CONTENT_LIST = "RefreshCourseContentList";
        constexpr const_string KEY_PLAIN_GRADE_TEXT = BB_LABEL(kv.plain_grade_text);
        constexpr const_string KEY_BB_ASSIST = "BB_ASSIST";
        constexpr const_string KEY_DISMISS_IDS = "DismissIds";
        constexpr const_string KEY_ADMIN_PREFERENCE = "AdminPreference";
        constexpr const_string KEY_USER_PREFERENCE  = "UserPreference";
        constexpr const_string KEY_ADMIN_NOTIFICATION_SETTINGS  = "AdminNotificationSettings";

        constexpr const_string KEY_COURSE_MESSAGES_COUNT = "CourseMessagesCount_";
        constexpr const_string KEY_COURSE_MESSAGES_FOLDER = "CourseMessagesFolder_";
        constexpr const_string KEY_COURSE_MESSAGES_CUSTOM_FOLDER = "CourseMessagesCustomFolder_";
        constexpr const_string KEY_COURSE_MESSAGES = "CourseMessages";
        constexpr const_string KEY_PARTICIPANTS = "Participants";
        constexpr const_string KEY_COURSE_MESSAGE_BODY = "CreateMessageBody";
        constexpr const_string KEY_REPLY_MESSAGE_BODY = "ReplyMessageBody";
        constexpr const_string KEY_SEND_EMAIL_TO_PARTICIPANTS = "SendEmailToParticipants";
        constexpr const_string KEY_MESSAGE_CONVERSATION_ID = "ConversationId";
        constexpr const_string KEY_MESSAGE_HAS_PARTICIPANTS = "HasParticipants";
        constexpr const_string KEY_CREATE_DISCUSSION_BODY = "CreateDiscussionBody";
        constexpr const_string KEY_CREATE_DISCUSSION_GROUP_ID = "CreateDiscussionGroupId";
        constexpr const_string KEY_CREATE_DISCUSSION_PARENT_FOLDER_ID = "CreateDiscussionParentFolderId";
        constexpr const_string KEY_ASSIGNED_GROUP_ID = "AssignedGroupId";
        constexpr const_string KEY_REPLY_DISCUSSION_IS_GRADABLE_DISC_THREAD = "ReplyDiscussionIsGradableDiscussionThread";
        constexpr const_string KEY_REPLY_DISCUSSION_IS_GRADABLE_DISC_GROUP= "ReplyDiscussionIsGradableDiscussionGroup";
        constexpr const_string KEY_REPLY_DISCUSSION_THREAD_OUTLINE_ID = "ReplyDiscussionThreadOutlineId";
        constexpr const_string KEY_REPLY_DISCUSSION_SELF_COMMENT_COUNT = "ReplyDiscussionSelfCommentCount";
        constexpr const_string KEY_REPLY_DISCUSSION_POST_ID = "ReplyDiscussionPostId";
        constexpr const_string KEY_REPLY_DISCUSSION_SAVE_AS_DRAFT = "ReplyDiscussionSaveAsDraft";
        constexpr const_string KEY_DISCUSSION_PARTICIPANTS = "DiscussionParticipants_";

    }
    
    namespace TwoKeyDAOConst
    {
        constexpr const_string KEY_DISCUSSION_DESC = "DiscussionObjectKey";
        constexpr const_string KEY_DISCUSSION_LIST = "DiscussionListKey";
        constexpr const_string PLACEHOLDER_KEY = "NullKey";
        constexpr const_string KEY_DISCUSSION_POST = "DiscussionPostKey";
        
        constexpr const_string KEY_COURSE_COLLABORATE = BB_LABEL("Shared.Course.Collaborate");
    }
    
    namespace LocalCacheStatus
    {
        constexpr int TOO_NEW_TO_MANDATORY = 1;
        constexpr int TOO_NEW_TO_REFRESH = 2;
        constexpr int TOO_OLD = 3;
    }
    
    namespace RestConst
    {
        constexpr const_string KEY_EXTRA = "ext";
        constexpr const_string EXTRA_ENCODE_FILE_NAME = "URL_DECODE_FILE_NAME";
        constexpr const_string EXTRA_EXTRACT_RICH_TEXT = "EXTRACT_RICH_TEXT";
        constexpr const_string EXTRA_NEED_DESC_RICH_TEXT = "NEED_DESC_RICH_TEXT";
        constexpr const_string EXTRA_CONTENT_LAZY_LOADING = "CONTENT_LAZY_LOADING";
        constexpr const_string EXTRA_NEED_REDIRECT_AVATAR_URL = "NEED_REDIRECT_AVATAR_URL";
        constexpr const_string PATH_ME = "me";
        constexpr const_string LIST_PARAM_SEPARATOR = ",";
        

        namespace CourseOutline
        {
            constexpr const_string PATH_COURSE = "courses";
            constexpr const_string PATH_OUTLINE = "courseOutlines";
            constexpr const_string PATH_OUTLINES = "outlines";
            constexpr const_string PATH_COLLABSESSIONS = "collabSessions";
            constexpr const_string PATH_MEMBERSHIP = "memberships";
            constexpr const_string PATH_DETAIL = "details";
            constexpr const_string PATH_GRADE = "grade";
            constexpr const_string PATH_DUEITEMS = "dueItems";
            constexpr const_string PATH_SIZE = "size";
            constexpr const_string PATH_METADATA = "metadata";
            constexpr const_string PATH_METADATA_SYNC = "metadata/sync";
            constexpr const_string PATH_COLLABSESSION = "collabSession";

            constexpr const_string KEY_COURSE_ID = "courseId";
            constexpr const_string KEY_OUTLINE_TYPE = "outlineType";
            constexpr const_string KEY_FORCE_SUBMIT = "skipForceSubmit";
            constexpr const_string KEY_STARTDATE = "startDate";
            constexpr const_string KEY_ENDDATE = "endDate";
            
            constexpr const_string KEY_SOURCE = "source";
            constexpr const_string KEY_SOURCE_VALUE = "pn";

            constexpr const_string KEY_FAVORITE_COURSE = "favorites";
            constexpr const_string KEY_DOCUMENT_OPENED_STATE = "state";

            constexpr const_string KEY_CHECK_PASSWORD = "checkpassword";
            constexpr const_string PARAM_START_ATTEMPT = "startAttempt";

            constexpr const_string PARAM_SUBMISSION_IDS = "submissionIds";
            constexpr const_string PARAM_USER_ID = "userId";
        }
        
        namespace CourseCalendar
        {
            constexpr const_string KEY_FILTER = "filter";
            constexpr const_string VALUE_TEST = "Test";
            constexpr const_string VALUE_ASSIGNMENT = "Assignment";
            constexpr const_string VALUE_SURVEY = "Survey";
            constexpr const_string VALUE_FORUM = "Forum";
            constexpr const_string VALUE_DISCUSSION = "Discussion";
            constexpr const_string VALUE_WIKI = "Wiki";
            constexpr const_string VALUE_BLOG = "Blog";
            constexpr const_string VALUE_JOURNAL = "Journal";
            constexpr const_string VALUE_TURNITIN = "Turnitin";
            constexpr const_string VALUE_SELF_AND_PEER = "SelfAndPeerAssessment";
            constexpr const_string VALUE_DISCUSSION_BOARD = "DiscussionBoard";
            constexpr const_string VALUE_DISCUSSION_MESSAGE = "DiscussionMessage";
            constexpr const_string VALUE_SCORM = "Scorm";

        }
        
        namespace CourseTimeline
        {
            constexpr const_string PATH = "timelines";
            constexpr const_string KEY_SHOWHIDE = "showHiddenCourses";
            constexpr const_string KEY_SHOW_GRID_VIEW = "showGridView";
        }
        
        namespace Institution
        {
            constexpr const_string PATH = "institutions/search";
            
            constexpr const_string KEY_Q = "q";
        }
        
        namespace UserCredentials
        {
            constexpr const_string PATH     = "credential/login";
            
            constexpr const_string KEY_USERNAME  = "userName";
            constexpr const_string KEY_PASSWORD  = "password";
            
            constexpr const_string PATH_LICENSE_CHECK = "licenses/userpay";
            
            //BBID
            constexpr const_string PATH_BBID_REGISTER = "bbidUsers/register";
            constexpr const_string PATH_BBID_LOGIN = "bbidUsers/login";
        }
        
        namespace StreamSections
        {
            constexpr const_string PATH     = "streams/search";
            constexpr const_string PATH_V2  = "v2/streams/search";
        }
        
        namespace StreamUnreadCount
        {
            constexpr const_string PATH     = "streams/count";
            
            constexpr const_string KEY_UNREAD  = "unread";
            constexpr const_string VALUE_UNREAD_TRUE = "true";
        }
        
        namespace Dismiss
        {
            constexpr const_string PATH		= "streams";
            constexpr const_string KEY_STREAM_EVENTTYPE = "streamEventType";
        }
        
        //
        namespace ServerDriven
        {
            constexpr const_string PATH = "serverDrivenParameters";
            constexpr const_string PATH_GRADE = "grade";
        }
        
        namespace PrivacyPolicy
        {
            constexpr const_string PATH = "system/privacyPolicy";
        }
        
        namespace FeatureList
        {
            constexpr const_string PATH = "features";
            constexpr const_string PARAM_COURSE_ID = "courseId";
            
            constexpr int FEATURE_TYPE_MENU = 0;
            constexpr const_string FEATURE_NAME_CALENDAR = "Calendar";
            
            constexpr const_string FEATURE_NAME_PROGRAM = "Program";
        }
        
        namespace Profile
        {
            constexpr const_string PATH_PREFIX = "users";
            constexpr const_string PATH_MY_AVATAR = "users/me/avatars";
            constexpr const_string PATH_PERMISSIONS = "permissions";
            constexpr const_string PATH_EDIT_AVATAR = "editAvatar";

        }
        
        namespace MobilyticsModule
        {
            constexpr const_string PATH = "analytics";
        }
        
        namespace Grade
        {
            constexpr const_string PATH = "courseGrades";
        }
        
        namespace CourseWork
        {
            constexpr const_string PATH_SUBMISSIONS = "submissions";
            constexpr const_string PATH_QUESTIONS = "questions";
            constexpr const_string PATH_COMMENTS = "submissionComments";
            
            constexpr const_string KEY_SUBMISSION_TYPE = "submissionType";
            constexpr const_string KEY_SUBMISSION_ID = "submissionId";
            constexpr const_string KEY_PASSWORD = "password";
            constexpr const_string KEY_REMOVE_CA = "removeCA";
            constexpr const_string KEY_DELETE_GRADES = "deleteGrades";
            
        }
        
        namespace PushNotificationSettings
        {
            constexpr const_string PATH_REGISTRATION = "notificationRegistrations";
            constexpr const_string PATH_SETTINGS = "notificationSettings";
            
            constexpr const_string KEY_TYPE = "type";
            constexpr const_string KEY_ANROID_GCM = "googleMessageType";
            constexpr const_string KEY_DEVICE_TOKEN = "deviceToken";
            
            constexpr int VALUE_TYPE_SCHOOL_AVAILABILITY = 0;
            constexpr int VALUE_TYPE_USER_CONTENT = 1;
            
            constexpr int VALUE_GoogleCloudMessageTypeC2DM = 0;
            constexpr int VALUE_GoogleCloudMessageTypeGCM = 1;
        }
        
        namespace FileUpload
        {
            constexpr const_string PATH = "files";
            constexpr const_string FORM_KEY_FILE = "file";
            constexpr const_string COURSE_ID = "courseId";
        }
        
        namespace Calendar
        {
            constexpr const_string PATH = "calendarEvents";
            
            constexpr const_string KEY_STARTDATE = "startDate";
            constexpr const_string KEY_ENDDATE = "endDate";
            constexpr const_string KEY_MIN_SIZE = "minSize";
            constexpr const_string KEY_SCROLL_TYPE = "scrollType";
            constexpr const_string KEY_VIEW_TYPE = "calendarViewType";
            constexpr const_string KEY_FILTER = "filter";
            constexpr const_string VALUE_TEST = "Test";
            constexpr const_string VALUE_ASSIGNMENT = "Assignment";
            constexpr const_string VALUE_DISCUSSION = "Discussion";
            constexpr const_string VALUE_TURNITIN = "Turnitin";
            constexpr const_string VALUE_SURVEY = "Survey";
            constexpr const_string VALUE_FORUM = "Forum";
            constexpr const_string VALUE_WIKI = "Wiki";
            constexpr const_string VALUE_BLOG = "Blog";
            constexpr const_string VALUE_JOURNAL = "Journal";
            constexpr const_string VALUE_SELF_AND_PEER = "SelfAndPeerAssessment";
            constexpr const_string VALUE_DISCUSSION_BOARD = "DiscussionBoard";
            constexpr const_string VALUE_DISCUSSION_MESSAGE = "DiscussionMessage";
            constexpr const_string VALUE_SCORM = "Scorm";

        }
        
        namespace ThirdContent
        {
            constexpr const_string PATH_CLOUD_FILE = "cloudFiles";
            
            constexpr const_string PARAM_KEY_CLOUD_FILE_SOURCE = "fileSource";
            
            constexpr const_string KEY_FILENAME = "fileName";
            constexpr const_string KEY_ACCESS_TOKEN = "accessToken";
            constexpr const_string KEY_TOKEN_TYPE = "accessTokenType";
            constexpr const_string KEY_FILE_PATH = "filePath";
            constexpr const_string KEY_FILE_ID = "fileId";
            
            // for dropbox only
            constexpr const_string KEY_APPKEY = "appKey";
            constexpr const_string KEY_APPSECRET = "appSecret";
            constexpr const_string KEY_ACCESSTOKENSECRET = "accessTokenSecret";
            
            constexpr const_string VALUE_CLOUD_FILE_ONEDRIVE = "OneDrive";
            constexpr const_string VALUE_CLOUD_FILE_GOOGLEDRIVE = "GoogleDrive";
            constexpr const_string VALUE_CLOUD_FILE_DROPBOX = "Dropbox";
            
            constexpr const_string VALUE_CLOUD_FILE_SOURCES[5] = {"Unknown", VALUE_CLOUD_FILE_ONEDRIVE, VALUE_CLOUD_FILE_GOOGLEDRIVE, VALUE_CLOUD_FILE_DROPBOX, VALUE_CLOUD_FILE_ONEDRIVE};
            
            constexpr const_string PATH_CLOUD_FILE_TASK_PREFIX = "cloudFiles";
            
            
            constexpr const_string KEY_ONEDRIVESDKTYPE = "oneDriveSDKType";
            
            constexpr const_string VALUE_DRIVESDK = "ONEDRIVESDK";
            constexpr const_string VALUE_LIVESDK = "LIVESDK";
            
            constexpr const_string KEY_OATHTYPE = "oauthType";
            constexpr const_string VALUE_OAUTH1 = "OAUTH1";
            constexpr const_string VALUE_OAUTH2 = "OAUTH2";

            constexpr const_string VALUE_URL_DECODE_FILEPATH = "URL_DECODE_FILE_PATH";
        }
        
        namespace Discussion
        {
            constexpr const_string PATH_DISCUSSION_LIST = "discussions";
            constexpr const_string KEY_COURSE_ID = "courseId";
            
            constexpr const_string KEY_OUTLINE_TYPE = "outlineType";
            
            constexpr const_string PATH_POSTS = "posts";
            constexpr const_string PATH_REPLIES = "replies";
            constexpr const_string KEY_DISCUSSIONGROUP_ID = "discussionGroupId";
            constexpr const_string KEY_REPLYLEVEL = "replyLevel";
            constexpr const_string KEY_DELETE_ATTACHMENT = "deleteAttachment";
            constexpr const_string PATH_THREADS = "threads";
            constexpr const_string KEY_CONTENT_ID = "contentId";
            constexpr const_string KEY_PARENT_FOLDER_ID = "parentFolderId";
            constexpr const_string KEY_IS_SOFT_DELETE = "isSoftDelete";
            constexpr const_string PATH_READ = "read";
            constexpr const_string KEY_ASSIGNED_GROUP_ID = "assignedGroupId";
            
            enum DiscussionType
            {
                DiscussionThread = 0,
                DiscussionGroup
            };
        }
        
        namespace UserPreference
        {
            enum SourceType
            {
                Learn = 0,
                Planner
            };
        }
        
        namespace RosterFilter
        {
            constexpr const_string KEY_ROSTER_FILTER = "rosterFilter";
            constexpr const_string VALUE_INSTRUCTOR = "INSTRUCTOR";
            constexpr const_string VALUE_TA = "TEACHING_ASSISTANT";
            constexpr const_string VALUE_GRADER = "GRADER";
            constexpr const_string VALUE_CB = "COURSE_BUILDER";
            constexpr const_string VALUE_STUDENT = "STUDENT";
        }

        namespace Logo
        {
            constexpr const_string PATH = "brands/current";
        }

        namespace NotificationSettings
        {
            constexpr const_string PATH_PUSH_SETTINGS = "push/settings";
            constexpr const_string PATH_PUSH_GENERALSETTINGS = "push/generalSettings";
        }

        namespace Ally
        {
            constexpr const_string PATH_LEARN_API_V1 = "learn/api/v1/";
            constexpr const_string PATH_LEARN_API_V2 = "api/v2/";
            constexpr const_string PATH_ALLY = "ally";
            constexpr const_string PATH_CONFIG = "config";
            constexpr const_string PATH_COURSES = "courses";
            constexpr const_string PATH_TOKEN = "token";
            constexpr const_string PATH_CLIENT = "clients";
            constexpr const_string PATH_FILE = "files";

        }

        namespace CourseMessages
        {
            constexpr const_string PATH_COURSE_MESSAGES = "courseMessages";
            constexpr const_string PATH_COUNTS = "counts";
            constexpr const_string PATH_CONVERSATION = "conversation";
            constexpr const_string PATH_REPLY = "replyMessage";
            constexpr const_string PARAM_FOLDER_TYPE = "folderType";
            constexpr const_string PARAM_FOLDER_ID = "folderId";
            constexpr const_string PARAM_FOLDERS = "folders";
            constexpr const_string PATH_PARTICIPANTS = "participants";
            constexpr const_string PATH_DELETE = "delete";
            constexpr const_string PARAM_SEND_EMAIL = "sendEmailToParticipants";
            constexpr const_string PARAM_HAS_PARTICIPANTS = "hasParticipants";
            constexpr const_string PARAM_OFFSET = "offset";
            constexpr const_string PARAM_LIMIT = "limit";
        }
    }
    
    
    namespace DAOConst
    {
        constexpr const_string LazyLoaingSuffix = "LazyLoading";
        constexpr const_string KeySeparator = "-";
        constexpr const_string ServerDrivenParameterKey = "ServerDrivenParameters";
        constexpr const_string PrivacyPolicyKey = "PrivacyPolicy";
        namespace CourseWork
        {
            enum CourseWorkType
            {
                CourseWorkTypeOverView = 0,
                CourseWorkTypeSubmissions = 1,
            };
            
            constexpr const_string SubmissionDraftIdNone = "__SubmissionDraft__";
        }
        
        namespace DBTableName
        {
            constexpr const_string TABLE_COURSE = "courses";
            constexpr const_string TABLE_SDK_BASIS = "sdk_basis";
            constexpr const_string TABLE_PROFILE = "bb_profile";
            constexpr const_string TABLE_USERCREDENTIAL = "user_credentials";
            constexpr const_string TABLE_KEYVALUEPAIR = "keyvalue_pairs";
            constexpr const_string TABLE_MOBILYTICS = "mobilytics";
            constexpr const_string TABLE_QUEUE = "http_queue";
        }
        
        namespace CourseDAOConst
       	{
           	enum COURSE_TYPE {OUTLINE_COURSE=0, GRADED_COURSE};
       	}
        
        namespace SqliteDBType
        {
            constexpr const_string TEXT = "TEXT";
            constexpr const_string INTEGER = "INETEGER";
        }
    }
    
    enum MetadataType {
        MetadataTypeSubmissionAttachments,
    };
    
    namespace Threads
    {
        namespace Labels
        {
            constexpr const_string CALLBACK_ = BB_THREAD_LABEL(Callback);
            constexpr const_string QUEUE = BB_THREAD_LABEL(Queueing);
            constexpr const_string POLLING = BB_THREAD_LABEL(PollingAlive);
            
            constexpr const_string LOGGER =  BB_THREAD_LABEL(Logger);
            constexpr const_string MOBILYTICS = BB_THREAD_LABEL(Mobilytics);
            constexpr const_string FILE_DOWNLOAD = BB_THREAD_LABEL(FILE_DOWNLOAD);
            
            constexpr const_string COURSE_OVERVIEW = BB_THREAD_LABEL(shared.courseOverview);
            constexpr const_string COURSE_CONTENT = BB_THREAD_LABEL(shared.courseContent);
            constexpr const_string COURSEWORK = BB_THREAD_LABEL(shared.coursework);
            constexpr const_string ANNOUNCEMENT_REUSABLE = BB_THREAD_LABEL(shared.announcementReUsableObjects);
            constexpr const_string STREAM_SETTINGS = BB_THREAD_LABEL(StreamSettings);
            constexpr const_string ACTIVITY_STREAM = BB_THREAD_LABEL(ActivityStream);
        }
    }
    
    namespace OAuth
    {
        namespace ThirdPartyUploadStatus
        {
            constexpr const_string WAITING = "Waiting";
            constexpr const_string IN_PROGRESS = "InProgress";
            constexpr const_string NOT_FOUND = "NotFound";
            constexpr const_string SUCCESS = "Success";
            constexpr const_string FAIL = "Fail";
            constexpr const_string INVALID_TOKEN = "InvalidToken";
            constexpr const_string FILE_NOT_FOUND = "FileNotFound";
        }
        
        enum OAuthType
        {
            OAUTH1 = 1,
            OAUTH2 = 2
        };
    }
    
    namespace Queueing
    {
        enum Queue_State {Start = 0, Stop};
    }
    
    namespace ServerDrivenKey
    {
        namespace HTTPOption
        {
            constexpr const_string CONNECTION_TIMEOUT = "SDK_HTTP_CONNECTION_TIMEOUT_IN_SECOND";
            constexpr const_string TRANSFER_TIMEOUT = "SDK_HTTP_READ_TIMEOUT_IN_SECOND";
            constexpr const_string SDK_LOGIN_BLOCKING_TIMEOUT_IN_SECOND = "SDK_LOGIN_BLOCKING_TIMEOUT_IN_SECOND";
            constexpr int SDK_LOGIN_BLOCKING_TIMEOUT_IN_SECOND_DEFAULT = 10;
        }
    }
    
    namespace Curl
    {
        namespace Setting
        {
            constexpr long LEAST_BYTES_WHEN_LOW_SPEED = 50L;
            constexpr long TIMEOUT_IN_SECONDS_WHEN_LOW_SPEED = 60L;
        }
        
        constexpr int DEFAULT_SDK_HTTP_CONNECTION_TIMEOUT_IN_SECOND = 10;
        constexpr int DEFAULT_SDK_HTTP_READ_TIMEOUT_IN_SECOND = 60;

    }
    
    namespace DiscussionDAOConst
    {
        constexpr const_string DB_Key_Group = "GROUP";
        constexpr const_string DB_Key_Thread = "THREAD";
        constexpr const_string DB_Key_Post = "POST";
    }
    
    namespace Offline
    {
        namespace Setting
        {
            constexpr const_string AUTOSYNC_FLAG = "autosync";
            constexpr const_string NETWORK_STATUS = "networkstatus";
            constexpr const_string AUTOSYNC_INTERVAL = "autosync_interval";
        };
        
        namespace NotificationName
        {
            constexpr const_string KEY_TRIGGER_AUTO_SYNC = "offline.trigger.autosync";
            constexpr const_string KEY_PAUSE_AUTO_SYNC = "offline.pause.autosync";
            constexpr const_string KEY_RESUME_AUTO_SYNC = "offline.resume.autosync";
            constexpr const_string KEY_COURSE_CONTENT_UPDATE = "offline.course.content.update";
        };
        
        namespace NetWorkStatus
        {
            constexpr const_string UNKNOWN = "Unknown";
            constexpr const_string WIFI = "Wifi";
            constexpr const_string LAN = "LAN";
            constexpr const_string MOBILE = "Mobile";
            constexpr const_string NOTREACHABLE = "NotReachable";
        };

        namespace DownloadCourseProgress
        {
            const int DownloadCourseProgressFailed = -1;
            const int DownloadCourseProgressCompleted = 100;
        };
    }
    
    namespace File
    {
        constexpr const_string LOG_DIR_NAME = "log";
        constexpr const_string LOG_FILE_NAME = "sdklog.txt";
        const long long LOG_MAX_SIZE = 1024*1024*100;
        const long long LOG_SPLIT_INTERVAL = 60;
    }

    namespace RwdUrl
    {
        constexpr const_string UTLRA_COURSE = "/ultra/mobileApiCall?courseId";
        constexpr const_string COURSE_ID = "?courseId";
        constexpr const_string CONTENT_ID = "&contentId";
        constexpr const_string ATTEMPT_ID = "&attemptId";
        constexpr const_string COLUMN_ID = "&columnId";
        constexpr const_string ACTION = "&action";
        constexpr const_string OPEN_DOCUMNET = "OPEN_DOCUMENT";
        constexpr const_string PREVIEW_ASSESSMENT = "PREVIEW_ASSESSMENT";
        constexpr const_string COLLAB_RECORDING_PREVIEW = "COLLAB_RECORDING_PREVIEW";
        constexpr const_string COLLAB_MANAGE_SESSION = "COLLAB_MANAGE_SESSION";
    }
}

#endif
