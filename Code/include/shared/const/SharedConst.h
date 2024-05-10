

#ifndef SDKShared_SharedConst_h
#define SDKShared_SharedConst_h

#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK
{

    enum CourseBatchFields
    {
        CourseBatchFieldsOutlines = 1,       // 1
        CourseBatchFieldsGrades = 2,         // 1 << 1
        CourseBatchFieldsDiscussions = 4,    // 1 << 2
        CourseBatchFieldsDetails = 8,        // 1 << 3
        CourseBatchFieldsRoster = 16,        // 1 << 4
        CourseBatchFieldsAll = 31            // CourseBatchFieldsOutlines | CourseBatchFieldsGrades | CourseBatchFieldsDiscussions | CourseBatchFieldsDetails | CourseBatchFieldsRoster
    };

    namespace CourseConst
    {
        constexpr int CourseWorkState_New = 0;
        constexpr int CourseWorkState_Default = 1;
        constexpr int CourseWorkState_DraftSaved = 2;
        constexpr int CourseWorkState_Submitted = 3;
        constexpr int CourseWorkState_Graded = 4;
        constexpr int CourseWorkState_OverdueLateSubmissionsAccepted = 5;
        constexpr int CourseWorkState_SubmittedLateGradePending = 6;
        constexpr int CourseWorkState_SubmittedLateGraded = 7;
        constexpr int CourseWorkState_Missed = 8;                            // overdue, not allow late submit
        constexpr int CourseWorkState_Exempt = 9;
        constexpr int DocumentState_New = 100;
        constexpr int DocumentState_Default = 101;
        constexpr int DocumentState_Viewed = 102;
        constexpr int LinkState_New = 200;
        constexpr int LinkState_Default = 201;
        constexpr int LinkState_Viewed = 202;
        constexpr int DiscussionState_New = 400;
        constexpr int DiscussionState_Default = 401;
        constexpr int DiscussionState_Commented = 402;
        constexpr int GradeDiscussionState_New = 500;
        constexpr int GradeDiscussionState_Default = 501;
        constexpr int GradeDiscussionState_CommentAdded = 502;
        constexpr int GradeDiscussionState_Score = 503;
        constexpr int GradeDiscussionState_OverDue = 504;
        constexpr int GradeDiscussionState_CommentLate = 505;
        constexpr int GradeDiscussionState_ScoreLate = 506;
        constexpr int GradeDiscussionState_Missed = 507;
        constexpr int GradeDiscussionState_WillBeAvailable = 508;
        constexpr int GradeDiscussionState_NotAvailable = 509;
        constexpr int DiscussionGroupOutlineState_Default = 600;
        constexpr int GradedDiscussionGroupOutlineState_Default = 700;
        constexpr int GradedDiscussionGroupGradedState_Default = 800;
    }

    namespace SharedAppNames
    {
        constexpr const_string APPNAME_STU = "BBStudent";
        constexpr const_string APPNAME_INST = "BBInstructor";
    }

    enum ResponseCode
    {
        // common errors                                                // common errors
        ResponseCodeOk = 0,                                             // OK
        ResponseCodeDatabaseError = 1,                                  // database error
        ResponseCodeNetworkError = 2,                                   // no connection, poor connection
        ResponseCodeNeedAuthorization = 3,                              // http status code 401
        ResponseCodeRequestError = 4,                                   // client parameter error
        ResponseCodeServerError = 5,                                    // http status code 5XX
        ResponseCodeForbidden = 6,                                      // http status code 403
        ResponseCodeEntityTooLarge = 7,                                 // http status code 413
        ResponseCodeInvalidJson = 8,
        ResponseCodeUnknwonError = 9,                                   // please do not use it
        ResponseCodeB2Unavailable = 10,                                 // B2 unavailable
        ResponseCodeB2NotSupportBbInstructor = 11,                      // B2 not support version not support Vsboard Instructor
        ResponseCodeEmptyFileDownloaded = 12,                           // when download a file with zero bytes
        ResponseCodeDownloadFileCanceled = 13,                          // the user Cancel downloading file
        ResponseCodeDownloadFileFailed = 14,                            // failed when download a file
        ResponseCodeDiscussionForumUnavailable = 10303,                 // discussion Forum unavailable
        ResponseCodeSchoolUnavailable = 16,                             // School Unavailable
        ResponseCodeNetworkStatusNotSatisfied = 17,                     // current network status is lower than system setting.
        ResponseCodeB2NotSupportVsboard = 18,                        // B2 version not support Vsboard
        ResponseCodeLearnNotSupportEntitlementCheck = 19,               // Learn version is not support for entitlement check
        ResponseCodeResourceNotFound = 20,                              // Network Resource not found
        ResponseCodeCouldNotResolveHostName = 21,                       // Could not resolve the host name, may caused by DNS server down, broken network
        ResponseCodeCouldNotConnectToServer = 22,                       // Could not connect to server, may cause by server is out of service, server is not exist, broken network
        ResponseCodeCourseNotAccessible = 23,                           // User is not permitted to access the requested course
        // login and credentials related                                // login and credentials related
        ResponseCodeUserNamePasswordError = 101,
        ResponseCodeInvalidLicense = 102,
        ResponseCodeInvalidRole = 103,
        ResponseCodeInvalidEmail = 104,
        ResponseCodeForbiddenEduEmail = 105,
        ResponseCodePasswordNotMatchRule = 106,
        ResponseCodePasswordIncorrect = 107,
        ResponseCodeAccountNeedVerification = 108,
        ResponseCodeEmailNotInSystem = 109,
        ResponseCodeEmailAlreadyInSystem = 110,
        ResponseCodeAccountAlreadyVerification = 111,
        ResponseCodeIncorrectCode = 112,
        ResponseCodeExpiredCode = 113,
        ResponseCodeUsedCode = 114,
        ResponseCodeNotSupportProspectiveLogin = 115,
        // test assignment                                              // test assignment
        ResponseCodeTestAssignmentPasswordError = 201,                  // wrong password in test/assignment
        ResponseCodeFileNotExist = 202,                                 // local file not found
        ResponseCodeNoAttemptRemain = 203,                              // test/assignment no attempt remains
        ResponseCodeAttemptAlreadySubmitted = 204,                      // test/assignment attempt already submitted
        ResponseCodeNewVersionDraftFound = 205,                         // new version of draft found
        ResponseCodeDraftFoundInNewAttempt = 206,                       // draft found when start new attempt
        ResponseCodeDriveFileUploadFail = 207,                          // cloud file upload fail
        ResponseCodeInvalidThirdPartyAccessToken = 208,                 // cloud file access token expired or invalid
        ResponseCodeIpRestrictedToSubmit = 209,                         // current ip address is restricted to submit test/assignment
        ResponseCodeIncorrectPassword = 210,                            // Incorrect password
        ResponseCodeIpTooManyIncorrectAttempts = 211,                   // Too many incorrect attempts
        ResponseCodeMessageNotFound = 213,                              // Meesage not found
        // Discussion error code                                        // Discussion error code
        ResponseCodeDiscussionPostNotFound = 250,                       // discussion post not found, discussion post has been deleted
        // apt course errors                                            // apt course errors
        ResponseCodeExceedCreditsLimitationError = 301,                 // exceed credits limitation
        ResponseCodeCourseAlreadyExistInTermError = 302,                // course has already existed in term
        ResponseCodeCourseNotExistInTermError = 303,                    // course is not existed in term
        ResponseCodeNoEnoughTermsError = 308,                           // no enough terms
        // Instructor error code                                        // Instructor error code
        ResponseCodeNoAttemptToLoad = 401,                              // no course work avaliable in GradebookService LoadFirst/NextCourseWork api
        ResponseCodeNoGraingSummaryItemToLoad = 402,                    // indicate all grading summary content is loaded, return in GradebookService LoadGradingSummary api only
        ResponseCodeAppVersionTooLowToGrade = 403,
        // Fatal Error                                                  // Fatal Error
        ResponseCodeAutoSyncFailed = 501,                               // indicate autosync course fails.
        ResponseCodeDownloadCourseOutlineObjectFailed = 502,            // indicate download course outline object fails.
        ResponseCodeDownloadCourseOutlineObjectCanceled = 503,          // indicate download course outline object is canceled by the user.
        ResponseCodeDownloadCourseOutlineObjectIsNotSupported = 504,    // indicate download course outline object doesn't support offline.
        ResponseCodeCourseMetadataValidRecordNotFoundInDb = 505,        // course metadata's valid record not found in database
        ResponseCodeDownloadCourseFailed = 506,                         // indicate download course failed
        ResponseCodeCalculateFolderSizeError = 507,                     // Offline Downloaded Summary Error
        ResponseCodeNoEnoughSpace = 508,                                // indicate that disk is full
        ResponseCodeDatabaseFatalError = 9001,                          // database migration failed
        ResponseCodeCurlFatalError = 9002,                              // libCurl initialization failed
        ResponseCodeCurlPartialFileError = 9003,                        // LibCurl error: CURLE_PARTIAL_FILE
        ResponseCodeCurlWriteError = 9004,                              // LibCurl error: CURLE_WRITE_ERROR
        ResponseCodeDiscussionForumDeleted = 10307,                     // discussion Forum Deleted
        ResponseCodeDiscussionThreadUnavailable = 10308,                // discussion Thread unavailable
        ResponseCodeDiscussionThreadDeleted = 10309,                    // discussion Thread Deleted
        ResponseCodeAllyServiceNotAvailable = 9005,                     // Ally service UnAvailable
        ResponseCodeAttemptCleared = 10310,                             // Attempt was cleared by an instructor or grader
        ResponseCodeCourseCompleted = 423                               // The course is closed, You can only view the course content
    };

    enum LicenseStatus
    {
        LicenseStatusInvalid = 0,
        LicenseStatusValid = 1
    };

    namespace SDPKey
    {
        constexpr const_string SDPKeyHelpPageUrl = "NEED_HELP_PAGE_URL";
        constexpr const_string SDPKeyTermOfUse = "TERM_OF_USE_URL";
        constexpr const_string SDPKeyLocalizedTermOfUse = "LOCALIZED_TERM_OF_USE_URL";
        constexpr const_string SDPKeyPrivacyPolicy = "PRIVACY_POLICY_URL";
        constexpr const_string SDPKeyLocalizedPrivacyPolicy = "LOCALIZED_PRIVACY_POLICY_URL";
        constexpr const_string SDPKeyLocalizedHelpPageUrl = "LOCALIZED_HELP_PAGE_URL";
        constexpr const_string SDPKeyCollabHelpPageUrl = "COLLAB_NEED_HELP_PAGE_URL";
        constexpr const_string SDPKeyCollabLocalizedHelpPageUrl = "LOCALIZED_COLLAB_HELP_PAGE_URL";
        constexpr const_string SDPKeyInstructorHelpPageUrl = "INS_NEED_HELP_PAGE_URL";
        constexpr const_string SDPKeyInstructorLocalizedHelpPageUrl = "INS_LOCALIZED_HELP_PAGE_URL";
        constexpr const_string SDPKeyInstructorCollabHelpPageUrl = "INS_COLLAB_NEED_HELP_PAGE_URL";
        constexpr const_string SDPKeyInstructorLocalizedCollabHelpPageUrl = "INS_LOCALIZED_COLLAB_HELP_PAGE_URL";
        constexpr const_string SDPKeyInstructorGradingConcurrentCourse = "SDK_GRADING_COURSE_CONCURRENT_BATCH_SIZE";
        constexpr const_string SDPKeyInstructorGradingConcurrentAssessment = "SDK_GRADING_ASSESSMENT_CONCURRENT_BATCH_SIZE";
        constexpr const_string SDPKeyMobilyticsUploadBatchSizeThrehold = "MOBILYTICS_UPLOAD_BATCH_SIZE_THRESHOLD";
        constexpr const_string SDPKeyOfflineAutoSyncIntervalInSecond = "SDK_OFFLINE_AUTOSYNC_INTERVAL_IN_SECOND";
        constexpr const_string SDPKeyOnlineFileCachingThresholdPerCourse = "SDK_ONLINE_FILE_CACHING_THRESHOLD_PER_COURSE";
    }

    namespace SubmissionConst
    {
        constexpr int SubmissionBlockType_Text = 0;
        constexpr int SubmissionBlockType_Attachment = 1;
    }

    enum class GradeCriteriaLevelType
    {
        NO_POINTS = 0,
        POINTS,
        POINT_RANGE,
        PERCENTAGE,
        PERCENTAGE_RANGE
    };

    enum GradeCategoryType
    {
        GradeCategory_TEST,
        GradeCategory_ASSIGNMENT,
        GradeCategory_SURVEY,
        GradeCategory_EXAM,
        GradeCategory_HOMEWORK,
        GradeCategory_PRESENTATION,
        GradeCategory_QUIZ,
        GradeCategory_DISCUSSION,
        GradeCategory_CUSTOM_ASSESSMENT
    };

    enum QuestionTypeConst
    {
        QuestionType_TrueFalse = 0,
        QuestionType_EitherOr = 1,
        QuestionType_FillInBlank = 2,
        QuestionType_MulitpleFillInBlank = 3,
        QuestionType_MutlipleChoice = 4,
        QuestionType_MultipleAnswer = 5,
        QuestionType_ShortAnswer = 6,
        QuestionType_Essay = 7,
        QuestionType_Assignment = 8,
        QuestionType_Text = 10,
        QuestionType_Attachment = 11
    };

    enum QuestionBlockType
    {
        QuestionBlockTypeText = 0,
        QuestionBlockTypeAttachment = 1
    };

    namespace SubmissionConst
    {
        constexpr int SubmissionStatus_NEW = 0;
        constexpr int SubmissionStatus_DRAFT = 1;
        constexpr int SubmissionStatus_SUBMITTED = 2;
        constexpr int SubmissionStatus_GRADED = 3;
    }

    enum SubmissionType
    {
        SubmissionTypeTest,
        SubmissionTypeAssignment
    };

    enum SubmissionGradeStatus
    {
        SubmissionGradeStatusNeedGrade = 0,
        SubmissionGradeStatusDraft = 1,
        SubmissionGradeStatusGraded = 2,
        SubmissionGradeStatusNotSubmitted = 3
    };

    enum SubmissionMetadataStatusType
    {
        SubmissionMetadataStatusTypeNeedGrade = 1,       // 1 << 0
        SubmissionMetadataStatusTypeDraft = 2,           // 1 << 1
        SubmissionMetadataStatusTypeGraded = 4,          // 1 << 2
        SubmissionMetadataStatusTypeNotSubmitted = 8,    // 1 << 3
        SubmissionMetadataStatusTypeAll = 15             // All - 1 << 4
    };

    enum GradeFormatType
    {
        GradeFormatType_SCORE = 0,
        GradeFormatType_PERCENT,
        GradeFormatType_TEXT,
        GradeFormatType_COMPLETE,
        GradeFormatType_TABULAR,
        GradeFormatType_COLORLESS
    };

    enum FileDownloadCachePolicy
    {
        FileDownloadCachePolicyCheckUpdate = 0,     // check the last modify date of the file, if it is later than donwload time, refresh cache
        FileDownloadCachePolicyForceRefresh = 1,    // force download the file from server
        FileDownloadCachePolicyUseLocal = 2         // use local cache
    };

    namespace ProfileConst
    {
        enum ProfileType
        {
            ProfileTypeInstructor = 0,
            ProfileTypeTeachingAssistant,
            ProfileTypeStudent
        };
    } 

    namespace PerformanceTag
    {
        // SDK Bb Student                                                                                               // SDK Bb Student
        constexpr const_string SDKLoginStart = "sdk_login_start";
        constexpr const_string SDKLoginEnd = "sdk_login_end";
        constexpr const_string SDKUpdateAvatarStart = "sdk_update_avatar_start";
        constexpr const_string SDKUpdateAvatarEnd = "sdk_update_avatar_end";
        constexpr const_string SDKLoadStreamStart = "sdk_load_stream_start";
        constexpr const_string SDKLoadStreamEnd = "sdk_load_stream_end";
        constexpr const_string SDKCourseTimelineStart = "sdk_course_timeline_start";
        constexpr const_string SDKCourseTimelineEnd = "sdk_course_timeline_end";
        constexpr const_string SDKOrganizationTimelineStart = "sdk_organization_timeline_start";
        constexpr const_string SDKOrganizationTimelineEnd = "sdk_organization_timeline_end";
        constexpr const_string SDKLoadCourseDiscussionStart = "sdk_load_course_discussions_start";
        constexpr const_string SDKLoadCourseDiscussionEnd = "sdk_load_course_discussions_end";
        constexpr const_string SDKLoadCourseOutlineStart = "sdk_load_course_outline_start";
        constexpr const_string SDKLoadCourseOutlineEnd = "sdk_load_course_outline_end";
        constexpr const_string SDKLoadCourseGradesStart = "sdk_load_course_grades_start";
        constexpr const_string SDKLoadCourseGradesEnd = "sdk_load_course_grades_end";
        constexpr const_string SDKLoadCourseRosterStart = "sdk_load_course_roster_start";
        constexpr const_string SDKLoadCourseRosterEnd = "sdk_load_course_roster_end";
        constexpr const_string SDKLoadCourseContentStart = "sdk_load_course_content_start";
        constexpr const_string SDKLoadCourseContentEnd = "sdk_load_course_content_end";
        constexpr const_string SDKBBSLoadCourseDetailsStart = "sdk_bbs_load_course_details_start";
        constexpr const_string SDKBBSLoadCourseDetailsEnd = "sdk_bbs_load_course_details_end";
        constexpr const_string SDKLoadCourseOutlineObjectStart = "sdk_load_course_outline_object_start";
        constexpr const_string SDKLoadCourseOutlineObjectEnd = "sdk_load_course_outline_object_end";
        constexpr const_string SDKLoadDiscussionGroupStart = "sdk_load_discussion_group_start";
        constexpr const_string SDKLoadDiscussionGroupEnd = "sdk_load_discussion_group_end";
        constexpr const_string SDKLoadDiscussionThreadStart = "sdk_load_discussion_thread_start";
        constexpr const_string SDKLoadDiscussionThreadEnd = "sdk_load_discussion_thread_end";
        constexpr const_string SDKLoadPostStart = "sdk_load_post_start";
        constexpr const_string SDKLoadPostEnd = "sdk_load_post_end";
        constexpr const_string SDKCreateDiscussionThreadStart = "sdk_create_thread_start";
        constexpr const_string SDKCreateDiscussionThreadEnd = "sdk_create_thread_end";
        constexpr const_string SDKReplyPostStart = "sdk_add_reply_start";
        constexpr const_string SDKReplyPostEnd = "sdk_add_reply_end";
        constexpr const_string SDKUpdatePostStart = "sdk_update_post_start";
        constexpr const_string SDKUpdatePostEnd = "sdk_update_post_end";
        constexpr const_string SDKDeletePostStart = "sdk_delete_post_start";
        constexpr const_string SDKDeletePostEnd = "sdk_delete_post_end";
        constexpr const_string SDKReadDiscussionPostStart = "sdk_read_discussion_post_start";
        constexpr const_string SDKReadDiscussionPostEnd = "sdk_read_discussion_post_end";
        constexpr const_string SDKLoadGradeStart = "sdk_load_grade_start";
        constexpr const_string SDKLoadGradeEnd = "sdk_load_grade_end";
        constexpr const_string SDKLoadDueDateStart = "sdk_load_due_date_start";
        constexpr const_string SDKLoadDueDateEnd = "sdk_load_due_date_end";
        constexpr const_string SDKSaveTestStart = "sdk_save_test_start";
        constexpr const_string SDKSaveTestEnd = "sdk_save_test_end";
        constexpr const_string SDKSubmitTestStart = "sdk_submit_test_start";
        constexpr const_string SDKSubmitTestEnd = "sdk_submit_test_end";
        constexpr const_string SDKSaveAssignmentStart = "sdk_save_assignment_start";
        constexpr const_string SDKSaveAssignmentEnd = "sdk_save_assignment_end";
        constexpr const_string SDKSubmitAssignmentStart = "sdk_submit_assignment_start";
        constexpr const_string SDKSubmitAssignmentEnd = "sdk_submit_assignment_end";
        constexpr const_string SDKSaveFileStart = "sdk_save_file_start";
        constexpr const_string SDKSaveFileEnd = "sdk_save_file_end";
        constexpr const_string SDKJoinCollabStart = "sdk_join_collab_start";
        constexpr const_string SDKJoinCollabEnd = "sdk_join_collab_end";
        // SDK Bb Instructor                                                                                            // SDK Bb Instructor
        constexpr const_string SDKGradeBaseStart = "sdk_load_grade_base_start";
        constexpr const_string SDKGradeBaseEnd = "sdk_load_grade_base_end";
        constexpr const_string SDKCourseAssessmentStart = "sdk_load_course_assessment_start";
        constexpr const_string SDKCourseAssessmentEnd = "sdk_load_course_assessment_end";
        constexpr const_string SDKAssessmentOverviewStart = "sdk_load_assessment_overview_start";
        constexpr const_string SDKAssessmentOverviewEnd = "sdk_load_assessment_overview_end";
        constexpr const_string SDKSinglePostingStart = "sdk_single_posting_start";
        constexpr const_string SDKSinglePostingEnd = "sdk_single_posting_end";
        constexpr const_string SDKAssessmentGradingStart = "sdk_loading_assessment_grading_start";
        constexpr const_string SDKAssessmentGradingEnd = "sdk_loading_assessment_grading_end";
        constexpr const_string SDKSaveDraftStart = "sdk_single_grading_start";
        constexpr const_string SDKSaveDraftEnd = "sdk_single_grading_end";
        // SDK NWTC                                                                                                     // SDK NWTC
        constexpr const_string SDKAcademicPlanStart = "sdk_academic_plan_start";
        constexpr const_string SDKAcademicPlanEnd = "sdk_academic_plan_end";
        constexpr const_string SDKAddCourseStart = "sdk_add_course_start";
        constexpr const_string SDKAddCourseEnd = "sdk_add_course_end";
        constexpr const_string SDKChangePaceStart = "sdk_change_pace_start";
        constexpr const_string SDKChangePaceEnd = "sdk_change_pace_end";
        constexpr const_string SDKProgramOverviewStart = "sdk_program_overview_start";
        constexpr const_string SDKProgramOverviewEnd = "sdk_program_overview_end";
        constexpr const_string SDKClassScheduleStart = "sdk_class_schedule_start";
        constexpr const_string SDKClassScheduleEnd = "sdk_class_schedule_end";
        constexpr const_string SDKUpdatePerferenceStart = "sdk_update_perference_start";
        constexpr const_string SDKUpdatePerferenceEnd = "sdk_update_perference_end";
        constexpr const_string SDKRegistSuccessStart = "sdk_regist_success_start";
        constexpr const_string SDKRegistSuccessEnd = "sdk_regist_success_end";
        constexpr const_string SDKRegistWaitlistAddStart = "sdk_regist_waitlist_add_start";
        constexpr const_string SDKRegistWaitlistAddEnd = "sdk_regist_waitlist_add_end";
        constexpr const_string SDKRemoveCourseStart = "sdk_remove_course_start";
        constexpr const_string SDKRemoveCourseEnd = "sdk_remove_course_end";
        constexpr const_string SDKRemoveCoursePreviewStart = "sdk_remove_course_preview_start";
        constexpr const_string SDKRemoveCoursePreviewEnd = "sdk_remove_course_preview_end";
        constexpr const_string SDKChangeCourseStart = "sdk_change_course_start";
        constexpr const_string SDKChangeCourseEnd = "sdk_change_course_end";
        // SDK Planner                                                                                                  // SDK Planner
        constexpr const_string SDKLoadPersonalInfoStart = "sdk_load_personal_info_start";
        constexpr const_string SDKLoadPersonalInfoEnd = "sdk_load_personal_info_end";
        constexpr const_string SDKSavePersonalInfoStart = "sdk_save_personal_info_start";
        constexpr const_string SDKSavePersonalInfoEnd = "sdk_save_personal_info_end";
        constexpr const_string SDKLoadInterestsInfoStart = "sdk_load_interests_info_start";
        constexpr const_string SDKLoadInterestsInfoEnd = "sdk_load_interests_info_end";
        constexpr const_string SDKSaveInterestsInfoStart = "sdk_save_interests_info_start";
        constexpr const_string SDKSaveInterestsInfoEnd = "sdk_save_interests_info_end";
        constexpr const_string SDKDiscoverInterestStart = "sdk_discover_interest_start";
        constexpr const_string SDKDiscoverInterestEnd = "sdk_discover_interest_end";
        constexpr const_string SDKDiscoverCareerStart = "sdk_discover_career_start";
        constexpr const_string SDKDiscoverCareerEnd = "sdk_discover_career_end";
        constexpr const_string SDKDiscoverMajorStart = "sdk_discover_major_start";
        constexpr const_string SDKDiscoverMajorEnd = "sdk_discover_major_end";
        constexpr const_string SDKDiscoverSkillStart = "sdk_discover_skill_start";
        constexpr const_string SDKDiscoverSkillEnd = "sdk_discover_skill_end";
        constexpr const_string SDKDiscoverPeopleStart = "sdk_discover_people_start";
        constexpr const_string SDKDiscoverPeopleEnd = "sdk_discover_people_end";
        constexpr const_string SDKDiscoverJobStart = "sdk_discover_job_start";
        constexpr const_string SDKDiscoverJobEnd = "sdk_discover_job_end";
        constexpr const_string SDKDiscoverProgramStart = "sdk_discover_program_start";
        constexpr const_string SDKDiscoverProgramEnd = "sdk_discover_program_end";
        constexpr const_string SDKLoadLocationStart = "sdk_load_location_start";
        constexpr const_string SDKLoadLocationEnd = "sdk_load_location_end";
        constexpr const_string SDKSaveLocationStart = "sdk_save_location_start";
        constexpr const_string SDKSaveLocationEnd = "sdk_save_location_end";
        constexpr const_string SDKLoadProgramListStart = "sdk_load_program_list_start";
        constexpr const_string SDKLoadProgramListEnd = "sdk_load_program_list_end";
        constexpr const_string SDKLoadSingleProgramStart = "sdk_load_single_program_start";
        constexpr const_string SDKLoadSingleProgramEnd = "sdk_load_single_program_end";
        constexpr const_string SDKLoadProgramCurriculumStart = "sdk_load_program_curriculum_start";
        constexpr const_string SDKLoadProgramCurriculumEnd = "sdk_load_program_curriculum_end";
        constexpr const_string SDKLoadCourseDetailsStart = "sdk_load_course_details_start";
        constexpr const_string SDKLoadCourseDetailsEnd = "sdk_load_course_details_end";
        constexpr const_string SDKLoadBaseStart = "sdk_load_base_start";
        constexpr const_string SDKLoadBaseEnd = "sdk_load_base_end";
        constexpr const_string SDKLoadFavoriteListStart = "sdk_load_favorite_list_start";
        constexpr const_string SDKLoadFavoriteListEnd = "sdk_load_favorite_list_end";
        constexpr const_string SDKAddRemoveFavoriteStart = "sdk_add_remove_favorite_start";
        constexpr const_string SDKAddRemoveFavoriteEnd = "sdk_add_remove_favorite_end";
        constexpr const_string SDKSubmitContactFormStart = "sdk_submit_contact_form_start";
        constexpr const_string SDKSubmitContactFormEnd = "sdk_submit_contact_form_end";
        constexpr const_string SDKLoadProgramPlansStart = "sdk_load_program_plans_start";
        constexpr const_string SDKLoadProgramPlansEnd = "sdk_load_program_plans_end";
        constexpr const_string SDKLoadAcademicPlanStart = "sdk_load_academic_plan_start";
        constexpr const_string SDKLoadAcademicPlanEnd = "sdk_load_academic_plan_end";
        constexpr const_string SDKLoadCourseTimelineStart = "sdk_load_course_timeline_start";
        constexpr const_string SDKLoadCourseTimelineEnd = "sdk_load_course_timeline_end";
        // SDK Shared Component                                                                                         // SDK Shared Component
        constexpr const_string SDKCourseBaseLoadStart = "sdk_course_timeline_start";
        constexpr const_string SDKCourseBaseLoadEnd = "sdk_course_timeline_end";
        constexpr const_string SDKShowHideCourseStart = "sdk_show_hide_course_start";
        constexpr const_string SDKShowHideCourseEnd = "sdk_show_hide_course_end";
        constexpr const_string SDKCourseOverviewStart = "sdk_course_overview_start";
        constexpr const_string SDKCourseOverviewEnd = "sdk_course_overview_end";
        constexpr const_string SDKCourseCalendarStart = "sdk_course_calendar_start";
        constexpr const_string SDKCourseCalendarEnd = "sdk_course_calendar_end";
        constexpr const_string SDKLoadAnnouncementStart = "sdk_course_annoucement_start";
        constexpr const_string SDKLoadAnnouncementEnd = "sdk_course_annoucement_end";
        constexpr const_string SDKSubmitAnnouncementStart = "sdk_submit_announcement_start";
        constexpr const_string SDKSubmitAnnouncementEnd = "sdk_submit_announcement_end";
        constexpr const_string SDKEditAnnouncementStart = "sdk_edit_announcement_start";
        constexpr const_string SDKEditAnnouncementEnd = "sdk_edit_announcement_end";
        constexpr const_string SDKDeleteAnnouncementStart = "sdk_delete_announcement_start";
        constexpr const_string SDKDeleteAnnouncementEnd = "sdk_delete_announcement_end";
        // SDK offline Component                                                                                        // SDK offline Component
        constexpr const_string SDKRefreshMetaDataStart = "sdk_refresh_metadata_start";
        constexpr const_string SDKRefreshMetaDataEnd = "sdk_refresh_metadata_end";
        constexpr const_string SDKDownloadCourseOutlineStart = "sdk_download_course_outline_start";
        constexpr const_string SDKDownloadCourseOutlineEnd = "sdk_download_course_outline_end";
        constexpr const_string SDKDownloadCourseOutlineBatchStart = "sdk_download_course_outline_batch_start";
        constexpr const_string SDKDownloadCourseOutlineBatchEnd = "sdk_download_course_outline_batch_end";
        constexpr const_string SDKDownloadCourseStart = "sdk_download_course_start";
        constexpr const_string SDKDownloadCourseEnd = "sdk_download_course_end";
        constexpr const_string SDKAutoSyncStart = "sdk_auto_sync_start";
        constexpr const_string SDKAutoSyncEnd = "sdk_auto_sync_end";
        constexpr const_string SDKDeleteCourseOutlineStart = "sdk_delete_course_outline_start";
        constexpr const_string SDKDeleteCourseOutlineEnd = "sdk_delete_course_outline_end";
        constexpr const_string SDKDeleteCourseOutlineBatchStart = "sdk_delete_course_outline_batch_start";
        constexpr const_string SDKDeleteCourseOutlineBatchEnd = "sdk_delete_course_outline_batch_end";
        constexpr const_string SDKDeleteCourseStart = "sdk_delete_course_start";
        constexpr const_string SDKDeleteCourseEnd = "sdk_delete_course_end";
        constexpr const_string SDKClearDownloadedFilesStart = "sdk_clear_downloaded_files_start";
        constexpr const_string SDKClearDownloadedFilesEnd = "sdk_clear_downloaded_files_end";
        constexpr const_string SDKGetCourseSizeStart = "sdk_get_course_size_start";
        constexpr const_string SDKGetCourseSizeEnd = "sdk_get_course_size_end";
        constexpr const_string SDKGetOfflineDownloadedSummaryStart = "sdk_get_offline_downloaded_summary_start";
        constexpr const_string SDKGetOfflineDownloadedSummaryEnd = "sdk_get_offline_downloaded_summary_end";
        // Serverbaas Student                                                                                                // Serverbaas Student
        constexpr const_string ServerbaasLoginStart = "Serverbaas_login_start";
        constexpr const_string ServerbaasLoginEnd = "Serverbaas_login_end";
        constexpr const_string ServerbaasUpdateAvatarStart = "Serverbaas_update_avatar_start";
        constexpr const_string ServerbaasUpdateAvatarEnd = "Serverbaas_update_avatar_end";
        constexpr const_string ServerbaasLoadStreamStart = "Serverbaas_load_stream_start";
        constexpr const_string ServerbaasLoadStreamEnd = "Serverbaas_load_stream_end";
        constexpr const_string ServerbaasCourseTimelineStart = "Serverbaas_course_timeline_start";
        constexpr const_string ServerbaasCourseTimelineEnd = "Serverbaas_course_timeline_end";
        constexpr const_string ServerbaasOrganizationTimelineStart = "Serverbaas_organization_timeline_start";
        constexpr const_string ServerbaasOrganizationTimelineEnd = "Serverbaas_organization_timeline_end";
        constexpr const_string ServerbaasLoadCourseDiscussionStart = "Serverbaas_load_course_discussions_start";
        constexpr const_string ServerbaasLoadCourseDiscussionEnd = "Serverbaas_load_course_discussions_end";
        constexpr const_string ServerbaasLoadDiscussionStart = "Serverbaas_load_discussions_start";
        constexpr const_string ServerbaasLoadDiscussionEnd = "Serverbaas_load_discussions_end";
        constexpr const_string ServerbaasLoadPostStart = "Serverbaas_load_post_start";
        constexpr const_string ServerbaasLoadPostEnd = "Serverbaas_load_post_end";
        constexpr const_string ServerbaasCreateDiscussionThreadStart = "Serverbaas_create_thread_start";
        constexpr const_string ServerbaasCreateDiscussionThreadEnd = "Serverbaas_create_thread_end";
        constexpr const_string ServerbaasReplyPostStart = "Serverbaas_add_reply_start";
        constexpr const_string ServerbaasReplyPostEnd = "Serverbaas_add_reply_end";
        constexpr const_string ServerbaasUpdatePostStart = "Serverbaas_update_post_start";
        constexpr const_string ServerbaasUpdatePostEnd = "Serverbaas_update_post_end";
        constexpr const_string ServerbaasDeletePostStart = "Serverbaas_delete_post_start";
        constexpr const_string ServerbaasDeletePostEnd = "Serverbaas_delete_post_end";
        constexpr const_string ServerbaasReadDiscussionPostStart = "Serverbaas_read_discussion_post_start";
        constexpr const_string ServerbaasReadDiscussionPostEnd = "Serverbaas_read_discussion_post_end";
        constexpr const_string ServerbaasLoadGradeStart = "Serverbaas_load_grade_start";
        constexpr const_string ServerbaasLoadGradeEnd = "Serverbaas_load_grade_end";
        constexpr const_string ServerbaasLoadDueDateStart = "Serverbaas_load_due_date_start";
        constexpr const_string ServerbaasLoadDueDateEnd = "Serverbaas_load_due_date_end";
        constexpr const_string ServerbaasSaveTestStart = "Serverbaas_save_test_start";
        constexpr const_string ServerbaasSaveTestEnd = "Serverbaas_save_test_end";
        constexpr const_string ServerbaasSubmitTestStart = "Serverbaas_submit_test_start";
        constexpr const_string ServerbaasSubmitTestEnd = "Serverbaas_submit_test_end";
        constexpr const_string ServerbaasSaveAssignmentStart = "Serverbaas_save_assignment_start";
        constexpr const_string ServerbaasSaveAssignmentEnd = "Serverbaas_save_assignment_end";
        constexpr const_string ServerbaasSubmitAssignmentStart = "Serverbaas_submit_assignment_start";
        constexpr const_string ServerbaasSubmitAssignmentEnd = "Serverbaas_submit_assignment_end";
        constexpr const_string ServerbaasSaveFileStart = "Serverbaas_save_file_start";
        constexpr const_string ServerbaasSaveFileEnd = "Serverbaas_save_file_end";
        // Serverbaas Instructor                                                                                             // Serverbaas Instructor
        constexpr const_string ServerbaasOutlineMetadataStart = "Serverbaas_outline_metadata_start";
        constexpr const_string ServerbaasOutlineMetadataEnd = "Serverbaas_outline_metadata_end";
        constexpr const_string ServerbaasSubmissionMetadataStart = "Serverbaas_submission_metadata_start";
        constexpr const_string ServerbaasSubmissionMetadataEnd = "Serverbaas_submission_metadata_end";
        constexpr const_string ServerbaasSingleSubmissionStart = "Serverbaas_single_submission_start";
        constexpr const_string ServerbaasSingleSubmissionEnd = "Serverbaas_single_submission_end";
        constexpr const_string ServerbaasSiblingNavigationStart = "Serverbaas_sibling_navigation_start";
        constexpr const_string ServerbaasSiblingNavigationEnd = "Serverbaas_sibling_navigation_end";
        constexpr const_string ServerbaasGradeSaveStart = "Serverbaas_grade_save_start";
        constexpr const_string ServerbaasGradeSaveEnd = "Serverbaas_grade_save_end";
        constexpr const_string ServerbaasSaveCommentStart = "Serverbaas_save_comment_start";
        constexpr const_string ServerbaasSaveCommentEnd = "Serverbaas_save_comment_end";
        constexpr const_string ServerbaasGradePostStart = "Serverbaas_grade_post_start";
        constexpr const_string ServerbaasGradePostEnd = "Serverbaas_grade_post_end";
        constexpr const_string ServerbaasClearGradeStart = "Serverbaas_clear_grade_start";
        constexpr const_string ServerbaasClearGradeEnd = "Serverbaas_clear_grade_end";
        constexpr const_string ServerbaasAssignmentSummaryStart = "Serverbaas_assignment_summary_start";
        constexpr const_string ServerbaasAssignmentSummaryEnd = "Serverbaas_assignment_summary_end";
        // Serverbaas NWTC                                                                                                   // Serverbaas NWTC
        constexpr const_string ServerbaasAcademicPlanStart = "Serverbaas_academic_plan_start";
        constexpr const_string ServerbaasAcademicPlanEnd = "Serverbaas_academic_plan_end";
        constexpr const_string ServerbaasAddCourseStart = "Serverbaas_add_course_start";
        constexpr const_string ServerbaasAddCourseEnd = "Serverbaas_add_course_end";
        constexpr const_string ServerbaasChangePaceStart = "Serverbaas_change_pace_start";
        constexpr const_string ServerbaasChangePaceEnd = "Serverbaas_change_pace_end";
        constexpr const_string ServerbaasProgramOverviewStart = "Serverbaas_program_overview_start";
        constexpr const_string ServerbaasProgramOverviewEnd = "Serverbaas_program_overview_end";
        constexpr const_string ServerbaasClassScheduleStart = "Serverbaas_class_schedule_start";
        constexpr const_string ServerbaasClassScheduleEnd = "Serverbaas_class_schedule_end";
        constexpr const_string ServerbaasUpdatePerferenceStart = "Serverbaas_update_perference_start";
        constexpr const_string ServerbaasUpdatePerferenceEnd = "Serverbaas_update_perference_end";
        constexpr const_string ServerbaasRegistSuccessStart = "Serverbaas_regist_success_start";
        constexpr const_string ServerbaasRegistSuccessEnd = "Serverbaas_regist_success_end";
        constexpr const_string ServerbaasRegistWaitlistAddStart = "Serverbaas_regist_waitlist_add_start";
        constexpr const_string ServerbaasRegistWaitlistAddEnd = "Serverbaas_regist_waitlist_add_end";
        constexpr const_string ServerbaasRemoveCourseStart = "Serverbaas_remove_course_start";
        constexpr const_string ServerbaasRemoveCourseEnd = "Serverbaas_remove_course_end";
        constexpr const_string ServerbaasRemoveCoursePreviewStart = "mbass_remove_course_preview_start";
        constexpr const_string ServerbaasRemoveCoursePreviewEnd = "mbass_remove_course_preview_end";
        constexpr const_string ServerbaasChangeCourseStart = "Serverbaas_change_course_start";
        constexpr const_string ServerbaasChangeCourseEnd = "Serverbaas_change_course_end";
        // SDK Serverbaas Planner                                                                                            // SDK Serverbaas Planner
        constexpr const_string ServerbaasLoadPersonalInfoStart = "Serverbaas_load_personal_info_start";
        constexpr const_string ServerbaasLoadPersonalInfoEnd = "Serverbaas_load_personal_info_end";
        constexpr const_string ServerbaasSavePersonalInfoStart = "Serverbaas_save_personal_info_start";
        constexpr const_string ServerbaasSavePersonalInfoEnd = "Serverbaas_save_personal_info_end";
        constexpr const_string ServerbaasLoadInterestsInfoStart = "Serverbaas_load_interests_info_start";
        constexpr const_string ServerbaasLoadInterestsInfoEnd = "Serverbaas_load_interests_info_end";
        constexpr const_string ServerbaasSaveInterestsInfoStart = "Serverbaas_save_interests_info_start";
        constexpr const_string ServerbaasSaveInterestsInfoEnd = "Serverbaas_save_interests_info_end";
        constexpr const_string ServerbaasDiscoverInterestStart = "Serverbaas_discover_interest_start";
        constexpr const_string ServerbaasDiscoverInterestEnd = "Serverbaas_discover_interest_end";
        constexpr const_string ServerbaasDiscoverCareerStart = "Serverbaas_discover_career_start";
        constexpr const_string ServerbaasDiscoverCareerEnd = "Serverbaas_discover_career_end";
        constexpr const_string ServerbaasDiscoverMajorStart = "Serverbaas_discover_major_start";
        constexpr const_string ServerbaasDiscoverMajorEnd = "Serverbaas_discover_major_end";
        constexpr const_string ServerbaasDiscoverSkillStart = "Serverbaas_discover_skill_start";
        constexpr const_string ServerbaasDiscoverSkillEnd = "Serverbaas_discover_skill_end";
        constexpr const_string ServerbaasDiscoverProgramStart = "Serverbaas_discover_program_start";
        constexpr const_string ServerbaasDiscoverProgramEnd = "Serverbaas_discover_program_end";
        constexpr const_string ServerbaasDiscoverLocationStart = "Serverbaas_load_location_start";
        constexpr const_string ServerbaasDiscoverLocationEnd = "Serverbaas_load_location_end";
        constexpr const_string ServerbaasSaveLocationStart = "Serverbaas_save_location_start";
        constexpr const_string ServerbaasSaveLocationEnd = "Serverbaas_save_location_end";
        constexpr const_string ServerbaasLoadProgramListStart = "Serverbaas_load_program_list_start";
        constexpr const_string ServerbaasLoadProgramListEnd = "Serverbaas_load_program_list_end";
        constexpr const_string ServerbaasLoadSingleProgramStart = "Serverbaas_load_single_program_start";
        constexpr const_string ServerbaasLoadSingleProgramEnd = "Serverbaas_load_single_program_end";
        constexpr const_string ServerbaasLoadProgramCurriculumStart = "Serverbaas_load_program_curriculum_start";
        constexpr const_string ServerbaasLoadProgramCurriculumEnd = "Serverbaas_load_program_curriculum_end";
        constexpr const_string ServerbaasLoadCourseDetailsStart = "Serverbaas_load_course_details_start";
        constexpr const_string ServerbaasLoadCourseDetailsEnd = "Serverbaas_load_course_details_end";
        constexpr const_string ServerbaasLoadBaseStart = "Serverbaas_load_base_start";
        constexpr const_string ServerbaasLoadBaseEnd = "Serverbaas_load_base_end";
        constexpr const_string ServerbaasLoadFavoriteListStart = "Serverbaas_load_favorite_list_start";
        constexpr const_string ServerbaasLoadFavoriteListEnd = "Serverbaas_load_favorite_list_end";
        constexpr const_string ServerbaasAddRemoveFavoriteStart = "Serverbaas_add_remove_favorite_start";
        constexpr const_string ServerbaasAddRemoveFavoriteEnd = "Serverbaas_add_remove_favorite_end";
        constexpr const_string ServerbaasSubmitContactFormStart = "Serverbaas_submit_contact_form_start";
        constexpr const_string ServerbaasSubmitContactFormEnd = "Serverbaas_submit_contact_form_end";
        constexpr const_string ServerbaasLoadAcademicPlanStart = "Serverbaas_load_academic_plan_start";
        constexpr const_string ServerbaasLoadAcademicPlanEnd = "Serverbaas_load_academic_plan_end";
        constexpr const_string ServerbaasLoadCourseTimelineStart = "Serverbaas_load_course_timeline_start";
        constexpr const_string ServerbaasLoadCourseTimelineEnd = "Serverbaas_load_course_timeline_end";
        // Serverbaas Shared Component                                                                                       // Serverbaas Shared Component
        constexpr const_string ServerbaasCourseBaseLoadStart = "Serverbaas_course_timeline_start";
        constexpr const_string ServerbaasCourseBaseLoadEnd = "Serverbaas_course_timeline_end";
        constexpr const_string ServerbaasShowHideCourseStart = "Serverbaas_show_hide_course_start";
        constexpr const_string ServerbaasShowHideCourseEnd = "Serverbaas_show_hide_course_end";
        constexpr const_string ServerbaasCourseOverviewStart = "Serverbaas_course_overview_start";
        constexpr const_string ServerbaasCourseOverviewEnd = "Serverbaas_course_overview_end";
        constexpr const_string ServerbaasCourseCalendarStart = "Serverbaas_course_calendar_start";
        constexpr const_string ServerbaasCourseCalendarEnd = "Serverbaas_course_calendar_end";
        constexpr const_string ServerbaasLoadAnnouncementStart = "Serverbaas_course_annoucement_start";
        constexpr const_string ServerbaasLoadAnnouncementEnd = "Serverbaas_course_annoucement_end";
        constexpr const_string ServerbaasSubmitAnnouncementStart = "Serverbaas_submit_announcement_start";
        constexpr const_string ServerbaasSubmitAnnouncementEnd = "Serverbaas_submit_announcement_end";
        // Serverbaas offline Component                                                                                      // Serverbaas offline Component
        constexpr const_string ServerbaasGetMetaDataStart = "Serverbaas_get_metadata_start";
        constexpr const_string ServerbaasGetMetaDataEnd = "Serverbaas_get_metadata_end";
        constexpr const_string ServerbaasCompareMetaDataStart = "Serverbaas_compare_metadata_start";
        constexpr const_string ServerbaasCompareMetaDataEnd = "Serverbaas_compare_metadata_end";
        // Serverbaas grading api                                                                                            // Serverbaas grading api
        constexpr const_string ServerbaasGetGradeBaseMetadataStart = "Serverbaas_get_grade_base_metadata_start";
        constexpr const_string ServerbaasGetGradeBaseMetadataEnd = "Serverbaas_get_grade_base_metadata_end";
        constexpr const_string ServerbaasGetCourseAssessmentMetadataStart = "Serverbaas_get_course_assessment_metadata_start";
        constexpr const_string ServerbaasGetCourseAssessmentMetadataEnd = "Serverbaas_get_course_assessment_metadata_end";
        constexpr const_string ServerbaasGetAssessmentMetadataStart = "Serverbaas_get_assessment_metadata_start";
        constexpr const_string ServerbaasGetAssessmentMetadataEnd = "Serverbaas_get_assessment_metadata_end";
        constexpr const_string ServerbaasGetSubmissionMetadataStart = "Serverbaas_get_submission_metadata_start";
        constexpr const_string ServerbaasGetSubmissionMetadataEnd = "Serverbaas_get_submission_metadata_end";
        constexpr const_string ServerbaasGetAssessmentSubmissionStart = "Serverbaas_get_assessment_submission_start";
        constexpr const_string ServerbaasGetAssessmentSubmissionEnd = "Serverbaas_get_assessment_submission_end";
        constexpr const_string ServerbaasPostSingleGradeStart = "Serverbaas_post_single_grade_start";
        constexpr const_string ServerbaasPostSingleGradeEnd = "Serverbaas_post_single_grade_end";
        constexpr const_string ServerbaasSavingGradeStart = "Serverbaas_post_single_grade_start";
        constexpr const_string ServerbaasSavingGradeEnd = "Serverbaas_post_single_grade_end";
    }

    namespace MobilyticsConst
    {
        constexpr const_string MOBILYTICS_VERSION = "version";
        constexpr const_string MOBILYTICS_SCHEMA = "schema";
        constexpr const_string MOBILYTICS_SESSIONID = "sessionId";
        constexpr const_string MOBILYTICS_ACTION = "action";
        constexpr const_string MOBILYTICS_VALUE = "value";
        constexpr const_string MOBILYTICS_TIMESTAMP = "timeStamp";
        constexpr const_string MOBILYTICS_ELAPSE_TIME = "elapsedTime";
        constexpr const_string MOBILYTICS_DOCURL = "docUrl";
        constexpr const_string MOBILYTICS_COURSEID = "courseId";
        constexpr const_string MOBILYTICS_TABNAME = "tabName";
        constexpr const_string MOBILYTICS_TAG_SESSION = "TagSession";
        constexpr const_string MOBILYTICS_SESSION_OPEN = "SessionOpen";
        constexpr const_string MOBILYTICS_SESSION_CLOSE = "SessionClose";
        constexpr const_string MOBILYTICS_SESSION_UNEXPECTCLOSE = "SessionUnexpectClose";
        constexpr const_string MOBILYTICS_SESSION_RESUME = "SessionResume";
        constexpr const_string MOBILYTICS_TAG_EVENT = "TagEvent";
        constexpr const_string MOBILYTICS_TAG_SCREEN = "TagScreen";
        constexpr const_string MOBILYTICS_PERF_LOG_SPERATOR = ",";
        constexpr const_string MOBILYTICS_TAG_MARKER = "TagMarker";
        constexpr const_string MOBILYTICS_MARKER_CURLERROR = "CurlError";
    }

    namespace MobilyticsEventKey
    {
        constexpr const_string OpenCourseOutlineObject = "e_openCourseOutlineObject";
        constexpr const_string TagPerformance = "e_tagPerformance";
    }

    namespace MobilyticsAttributeKey
    {
        constexpr const_string DocUrl = "docUrl";
        constexpr const_string CourseId = "courseId";
        constexpr const_string TabName = "tabName";
        constexpr const_string OutlineObjectId = "outlineId";
        constexpr const_string OutlineObjectType = "outlineType";
        constexpr const_string PerfTagName = "perfTagName";
        constexpr const_string ThreadId = "threadId";
        constexpr const_string CurlErrorCode = "e_CurlErrorCode";
    }

    namespace FeatureList
    {
        constexpr const_string PageCourseDiscussion = "PAGE_COURSE_DISCUSSION";
        constexpr const_string PageCourseVisibility = "PAGE_COURSE_VISIBILITY";
        constexpr const_string NavMenuStream = "NAV_MENU_STREAM";
        constexpr const_string NavMenuCourse = "NAV_MENU_COURSE";
        constexpr const_string NavMenuGrade = "NAV_MENU_GRADE";
        constexpr const_string NavMenuCalendar = "NAV_MENU_CALENDAR";
        constexpr const_string NavMenuProgram = "NAV_MENU_PROGRAM";
        constexpr const_string NavMenuProfile = "NAV_MENU_PROFILE";
        constexpr const_string NavMenuPlanner = "NAV_MENU_PLANNER";
        constexpr const_string NavMenuOrganization = "NAV_MENU_ORGANIZATION";
        constexpr const_string NavMenuGrading = "NAV_MENU_GRADING";
        constexpr const_string LicensePlanner = "LICENSE_PLANNER";
        constexpr const_string PageCourseOverviewNextDue = "PAGE_COURSE_OVERVIEW_NEXT_DUE";
        constexpr const_string PageCourseOverviewCourseDetail = "PAGE_COURSE_OVERVIEW_COURSE_DETAIL";
        constexpr const_string PageCourseOverviewCreateAnnouncement = "PAGE_COURSE_OVERVIEW_CREATE_ANNOUNCEMENT";
        constexpr const_string PageCourseOffline = "PAGE_COURSE_OFFLINE";
        constexpr const_string PageOrganizationVisibility = "PAGE_ORGANIZATION_VISIBILITY";
        constexpr const_string PageCourseOverviewAnnoucement = "PAGE_COURSE_OVERVIEW_ANNOUNCEMENT";
        constexpr const_string PageCourseOverviewCollaborate = "PAGE_COURSE_OVERVIEW_COLLABORATE";
        constexpr const_string PageDiscussionAttachmentUpload = "PAGE_DISCUSSION_ATTACHMENT_UPLOAD";
        constexpr const_string PageCourseOverviewAnnouncementScheduling = "PAGE_COURSE_OVERVIEW_ANNOUNCEMENT_SCHEDULING";
        constexpr const_string PageGradeDelegatedGrading = "PAGE_GRADE_DELEGATEDGRADING";
        constexpr const_string PageGradeAnonymousGrading = "PAGE_GRADE_ANONYMOUSGRADING";
        constexpr const_string PageGradeColorDisplay = "PAGE_GRADE_COLOR_DISPLAY";
        constexpr const_string UltraEnabledInstance = "ULTRA_ENABLED_INSTANCE";
        constexpr const_string PageCourseOverviewEditAnnouncement = "PAGE_COURSE_OVERVIEW_EDIT_ANNOUNCEMENT";
        constexpr const_string OriginalContentSettingsEnabled = "ORIGINAL_CONTENT_SETTINGS_ENABLED";
        constexpr const_string CourseMessagesReadOnlyMode = "COURSE_MESSAGES_READONLY_MODE";
        constexpr const_string CourseMessageEnabled = "COURSE_MESSAGE_ENABLED";
        constexpr const_string OriginalMessageAttachmentEnabled = "ORIGINAL_MESSAGE_ATTACHMENT_ENABLED";
        constexpr const_string OriginalCourseMessageEnabled = "ORIGINAL_COURSE_MESSAGE_ENABLED";
        constexpr const_string OriginalMediaContentDeleteEnabled = "ORIGINAL_MEDIA_CONTENT_DELETE_ENABLED";
        constexpr const_string InstructorAssessmentPreviewEnabled = "INSTRUCTOR_ASSESSMENT_PREVIEW_ENABLED";
        constexpr const_string CollabRWDEnabled = "COLLAB_RWD_ENABLED";
        constexpr const_string AssessmentReviewAttemptNeedsColumnId = "ASSESSMENT_REVIEW_ATTEMPT_NEEDS_COLUMN_ID";
        constexpr const_string DiscussionBoardSupportDraftItems = "DISCUSSION_BOARD_SUPPORTS_DRAFT_ITEMS";
    }

    enum ObjectType
    {
        ObjectTypeDocument = 0,
        ObjectTypeTest = 1,
        ObjectTypeAssignment = 2,
        ObjectTypeLink = 3,
        ObjectTypeFolder = 4,
        ObjectTypeDiscussionThread = 5,
        ObjectTypeGradedDiscussionThread = 6,
        ObjectTypeSurvey = 7,
        ObjectTypeOther = 8,
        ObjectTypeSelfAndPeer = 9,
        ObjectTypeJournal = 10,
        ObjectTypeBlog = 11,
        ObjectTypeWiki = 12,
        ObjectTypeDiscussionGroup = 13,
        ObjectTypeGradedDiscussionGroup = 14,
        ObjectTypeCourseLink = 15,
        ObjectTypeCollabSession = 16,
        ObjectTypeTextbook = 17,
        ObjectTypeTextbookManual = 18,
        ObjectTypeSyllabus = 19,
        ObjectTypeContentItem = 20,
        ObjectTypeWebLink = 21,
        ObjectTypeWikis = 22,
        ObjectTypeBlogs = 23,
        ObjectTypeJournals = 24,
        ObjectTypeLTIConnection = 25,
        ObjectTypeCalculatedGrade = 26,
        ObjectTypeDiscussionBoard = 27,
        ObjectTypeCollabSessionUltra = 28,
        ObjectTypeGroup = 29,
        ObjectTypeGroups = 30,
        ObjectTypeAnnouncements = 31,
        ObjectTypeMyGrades = 32,
        ObjectTypeQuiz = 33,
        ObjectTypeLearningModule = 34,
        ObjectTypeTurnitin = 35,
        ObjectTypeScorm = 36,
        ObjectTypeFlickerMashup = 37,
        ObjectTypeSlideShareMashup = 38,
        ObjectTypeYoutubeMashup = 39,
        ObjectTypeNonCalculatedItem = 40,
        ObjectTypeKalturaMedia = 41,
        ObjectTypeMessages = 42,
        ObjectTypeMAX = 127
    };

    namespace TimelineConst
    {
        constexpr int SDKTimelineType_PAST = 1;
        constexpr int SDKTimelineType_CURRENT = 2;
        constexpr int SDKTimelineType_UPCOMING = 3;
    }

    enum DayOfWeek
    {
        DayOfWeekSunday = 0,
        DayOfWeekMonday = 1,
        DayOfWeekTuesday = 2,
        DayOfWeekWednesday = 3,
        DayOfWeekThursday = 4,
        DayOfWeekFriday = 5,
        DayOfWeekSaturday = 6
    };

    enum ArrangementRepeatType
    {
        DAILY,
        WEEKLY,
        MONTHLY
    };

    enum CourseOverviewField
    {
        AnnouncementField = 1,                    // 1 << 0
        CollabField = 2,                          // 1 << 1
        CourseCalendarField = 4,                  // 1 << 2
        CourseContentField = 8,                   // 1 << 3
        CourseGradeField = 16,                    // 1 << 4
        DiscussionField = 32,                     // 1 << 5
        CourseDetailField = 64,                   // 1 << 6, control detail and roster field
        FeatureListField = 128,                   // 1 << 7
        EntitlementsField = 256,                  // 1 << 8, control whether Entitlements API call is required
        FavoriteField = 512,                      // 1 << 9, contro whether favorite Api call is required
        CourseMessageInboxField = 1024,           // 1 << 10
        CourseMessageSentField = 2048,            // 1 << 11
        InstGradeAndNeedAttentionField = 4096,    // 1 << 12 , control need attention and grade count field
        StuAll = 4095,                            // Formula1 : 0B111111111111 AnnouncementField | CollabField | CourseCalendarField | CourseGradeField | CourseContentField | DiscussionField | CourseDetailField | FeatureListField | EntitlementsField | FavoriteField | CourseMessageField --- Formula 2: ( 1 << 12 ) - 1 = 4095 
        InstAll = 8175                            // Formula1 : 0B1111111101111 AnnouncementField | CollabField | CourseCalendarField | CourseContentField | DiscussionField | CourseDetailField | FeatureListField | EntitlementsField | FavoriteField | CourseMessageField | InstGradeAndNeedAttentionField ---- Formula2: ( 1 << 13 ) - ( 1 << 4 ) - 1 = 8175
    };

    enum class AnnouncementType
    {
        SchoolAnnouncement,
        CourseAnnouncement
    };

    enum CourseCalendarGroupType
    {
        Overdue = 0,
        DueSoon = 1,
        ComingUp = 2
    };

    enum CollabSessionType
    {
        COURSE_ROOM = 0,
        UER_ROOM = 1,
        COURSE = 2,
        SHARED = 3,
        PUBLIC = 4,
        VROOM = 5
    };

    enum LaunchType
    {
        JOIN = 0,
        GUEST = 1
    };

    enum CourseWorkLoadField
    {
        CourseWorkLoadFieldCourseWorkDetail = 1,    // 1 << 0
        CourseWorkLoadFieldSubmissionList = 2,      // 1 << 1
        CourseWorkLoadFieldAll = 3
    };

    enum class MobileConfigField
    {
        HostName = 0,
        AppName,
        AppVersion,
        ServerbaasName,
        ApiName,
        CarrierCode,
        CarrierName,
        DeviceOS,
        DeviceOSVesion,
        DeviceModel,
        DeviceId,
        Locale,
        Timezone,
        LocalStoragePath,
        LogLevel,
        LogMaxSize,
        LogSplitInterval,
        EnableCachingLogic,             // bool
        EnableLogToFile,                // bool
        DbStoragePath,
        IgnoreSSLError,                 // bool
        CertStoragePath,
        Proxy,
        EnableDebugMobilytics,          // bool
        NetworkStatus,
        EnableAutoSync,                 // bool
        NetworkRestriction,
        AutoSyncInterval,
        TimeWithActivityInSecond,
        DaysWithActivity,
        DismissPrompt,                  // bool
        EnableMockDiskFull,             // bool
        EnableGradingFeature,           // bool
        EnableGradingForUltraCourse,    // bool default to false
        F2WLoginCookie,
        NewRelicLoggingEnabled,         // bool
        MAX
    };

    namespace BoolAlpha
    {
        constexpr const_string True = "true";
        constexpr const_string False = "false";
    }

    enum DiscussionPostStatus
    {
        Pending = 0,
        Published,
        Rejected,
        Draft,
        RejectedExplanation,
        SoftDelete,
        Unavailable,
        Hidden
    };

    enum class CourseOutlineObjectVisibleState
    {
        Visible,
        InvisibleSinceTooEarly,
        InvisibleSinceTooLate,
        Hidden,
        ConditionalAvailabilityVisible,
        ConditionalAvailabilityHidden
    };

    enum MobilyticsLogEventType
    {
        MobilyticsLogEventTypeNormal = 0,
        MobilyticsLogEventTypeAssignment = 1,
        MobilyticsLogEventTypeTest = 2,
        MobilyticsLogEventTypeDiscussion = 3,
        MobilyticsLogEventTypeTelemetry = 4,
        MobilyticsLogEventTypeTelemetryV2 = 5
    };

    namespace TelemetryConst
    {
        constexpr const_string TELEMETRY_SESSION_START = "SESSION_START";
        constexpr const_string TELEMETRY_SESSION_END = "SESSION_END";
        constexpr const_string TELEMETRY_SESSION_PAUSE = "SESSION_PAUSE";
    }

    namespace OAuth
    {
        enum ThirdPartyProvider
        {
            OneDrive = 1,
            GoogleDrive = 2,
            DropBox = 3,
            Unknown = 0x80
        };
    } 

    enum AttachmentProvider
    {
        AttachmentProviderLocal = 0,
        AttachmentProviderOneDrive = 1,
        AttachmentProviderGoogleDrive = 2,
        AttachmentProviderDropBox = 3
    };

    enum GradedItemState
    {
        GradedItemStateExempt = 900,
        GradedItemStateMissedGraded = 901,
        GradedItemStateMissed = 902,
        GradedItemStateFinalGrade = 903,
        GradedItemStateDefault = 904,
        GradedItemStateOverdue = 905,
        GradedItemStateLateGradedNoSubmissionRemains = 906,
        GradedItemStateGradedNoSubmissionRemains = 907,
        GradedItemStateLateSubmittedGradePending = 908,
        GradedItemStateSubmittedGradePending = 909,
        GradedItemStateLateGradedSubmissionsRemain = 910,
        GradedItemStateGradedSubmissionsRemain = 911,
        GradedItemStateAllGraded = 912,
        GradedItemStateLateAllGraded = 913
    };

    enum NetworkReachabilityStatus
    {
        NetworkReachabilityStatusUnknown = 0,
        NetworkReachabilityStatusReachableViaMobile = 1,
        NetworkReachabilityStatusReachableViaWifi = 2,
        NetworkReachabilityStatusReachableViaLAN = 3,
        NetworkReachabilityStatusNotReachable = 4
    };

    enum CourseOutlineDownloadStatus
    {
        CourseOutlineDownloadStatusNone = 0,
        CourseOutlineDownloadStatusPending = 1,
        CourseOutlineDownloadStatusDownloading = 2,
        CourseOutlineDownloadStatusSuccess = 3,
        CourseOutlineDownloadStatusFailed = 4,
        CourseOutlineDownloadStatusCanceled = 5,
        CourseOutlineDownloadStatusNeedUpdate = 6,
        CourseOutlineDownloadStatusPartialDownloaded = 7,
        CourseOutlineDownloadStatusUpdatePending = 8,
        CourseOutlineDownloadStatusUpdating = 9,
        CourseOutlineDownloadStatusUpdateError = 10,
        CourseOutlineDownloadStatusContainerDownloadPending = 11
    };

    enum CourseOutlineDeleteStatus
    {
        CourseOutlineDeleteStatusNone = 0,
        CourseOutlineDeleteStatusPending = 1,
        CourseOutlineDeleteStatusDeleting = 2,
        CourseOutlineDeleteStatusSuccess = 3,
        CourseOutlineDeleteStatusFailed = 4
    };

    enum OfflineUpdateType
    {
        OfflineUpdateTypeUnchanged = 0,
        OfflineUpdateTypeUpdate = 1,
        OfflineUpdateTypeDelete = 2,
        OfflineUpdateTypeAdd = 3
    };

    enum TOSAgreementState
    {
        AgreedInOlderVersion = 1,    // 1 << 0
        AgreedCurrentVersion = 2,    // 1 << 1
        AgreedInNewerVersion = 4     // 1 << 2
    };

    enum FolderNeedLoadDetailState
    {
        FolderNeedLoadDetailStateNo = 0,
        FolderNeedLoadDetailStateYes = 1,
        FolderNeedLoadDetailStateUnknown = 2
    };

    enum LearningModuleNeedLoadDetailState
    {
        LearningModuleNeedLoadDetailStateNo = 0,
        LearningModuleNeedLoadDetailStateYes = 1,
        LearningModuleNeedLoadDetailStateUnknown = 2
    };

    enum LearningModuleVisibility
    {
        VISIBLE = 0,
        PARTIALLY_VISIBLE = 1,
        HIDDEN = 2
    };

    enum LearningModuleState
    {
        NONE = 0,
        STARTED = 1,
        COMPLETED = 2,
        UNLOCKED = 3
    };

    enum LearningModuleCurrentAvailableItemState
    {
        LearningModuleCurrentItemStateAvailable = 0,
        LearningModuleCurrentItemStateProgress = 1,
        LearningModuleCurrentItemStateCompleted = 2
    };

    enum LearningModuleCriteriaType
    {
        LM_CRITERIA_DATE_RANGE = 0,
        LM_CRITERIA_GRADE_RANGE = 1,
        LM_CRITERIA_GRADE_RANGE_PERCENTAGE = 2,
        LM_CRITERIA_PRE_CONTENT = 3
    };

    enum InstUserSubmissionType
    {
        InstUserSubmissionTypeSingleStudent = 0,
        InstUserSubmissionTypeGroup
    };

    enum FeedbackCategory
    {
        FeedbackCategoryHasQuestion = 0,
        FeedbackCategoryReportIssue,
        FeedbackCategoryFeatureRequest,
        FeedbackCategoryGoodFeedback,
        FeedbackCategoryOther,
        FeedbackCategoryMax
    };

    enum MobileGradingType
    {
        MobileGradingTypeSupported = 0,
        MobileGradingTypeUnsupported,
        MobileGradingTypeUnknown
    };

    enum class CourseViewType
    {
        OriginalCourseView = 0,    // Classical course
        UltraCourseView = 1,       // Ultra course
        MaxCourseView = 2          // Bound check use only
    };

    enum class RoundingMode
    {
        Up = 0,      // For detail rounding rule refer to: https://docs.oracle.com/javase/7/docs/api/java/math/RoundingMode.html
        Down,
        Ceiling,
        Floor,
        HalfUp,
        HalfDown,
        HalfEven
    };

    enum class CacheStrategy
    {
        FromCache = 0,
        FromServer = 1,
        WantData = 2,
        SmartCache = 3
    };

    enum InstCourseAssessmentSection
    {
        InstCourseAssessmentSectionNeedAttention = 0,    // inlcude assessment which to grade or to post count > 0
        InstCourseAssessmentSectionPosted,               // include assessment which to grade and to post count = 0 and has submission
        InstCourseAssessmentSectionNoSubmission,         // include assessment which has no submission
        InstCourseAssessmentSectionUnsupported           // Delegate or Anonymous coursework will be here, ignore the all other logics
    };

    namespace PushNotificationSettingsKey
    {
        constexpr const_string AnnouncementAvailable = "AN:AN_AVAIL";
        constexpr const_string AssignmentAvailable = "AS:AS_AVAIL";
        constexpr const_string AssignmentDue = "AS:DUE";
        constexpr const_string AssignmentPastDue = "AS:OVERDUE";
        constexpr const_string AssignmentSubmitted = "AS:AS_ATTEMPT";
        constexpr const_string BlogNeedsGrading = "BL:BL_ATTEMPT";
        constexpr const_string ContentItemAvailable = "CO:CO_AVAIL";
        constexpr const_string CourseAndOrganizationAvailable = "CR:CR_AVAIL";
        constexpr const_string CourseMessageReceived = "CM:CM_RCVD";
        constexpr const_string DiscussionBoardForumNeedsGrading = "DF:DF_ATTEMPT";
        constexpr const_string DiscussionBoardThreadNeedsGrading = "DT:DT_ATTEMPT";
        constexpr const_string DiscussionBoardThreadReply = "MD:MD_DISC_RESPONSE";
        constexpr const_string ItemDue = "GB:DUE";
        constexpr const_string ItemOverdue = "GB:OVERDUE";
        constexpr const_string ItemGraded = "GB:GB_GRA_UPDATED";
        constexpr const_string JournalNeedsGrading = "JN:JN_ATTEMPT";
        constexpr const_string SurveyAvailable = "SU:SU_AVAIL";
        constexpr const_string SurveyDue = "SU:DUE";
        constexpr const_string SurveyOverdue = "SU:OVERDUE";
        constexpr const_string TestAvailable = "TE:TE_AVAIL";
        constexpr const_string TestDue = "TE:DUE";
        constexpr const_string TestOverdue = "TE:OVERDUE";
        constexpr const_string UnreadBlogPosts = "ZZ:blogs";
        constexpr const_string UnreadDiscussionBoardMessages = "ZZ:discussions";
        constexpr const_string UnreadJournalEntries = "ZZ:journals";
        constexpr const_string WikiNeedsGrading = "WK:WK_ATTEMPT";
        constexpr const_string ScormGraded = "SC:SC_AVAIL";
    }

    namespace NotificationSettingsKey
    {
        constexpr const_string Avail = "AVAIL";
        constexpr const_string GraUpdated = "GRA_UPDATED";
        constexpr const_string Due = "DUE";
        constexpr const_string DiscResponse = "DISC_RESPONSE";
        constexpr const_string CourseMessageReceived = "CM_RCVD";
    }

    namespace DiscussionResponseRecipients
    {
        constexpr const_string FromInstructorOnly = "I";
        constexpr const_string FromEveryone = "E";
    }

    enum CourseContentDeleteCriteria
    {
        ORIGINAL_COURSE_WITH_SUBMISSION = 0,
        ORIGINAL_COURSE_WITHOUT_SUBMISSION = 1,
        ULTRA_COURSE_WITH_SUBMISSION = 2,
        ULTRA_COURSE_WITHOUT_SUBMISSION = 3,
        NON_GRADEABLE_CONTENT_TYPE = 4,
        ULTRA_GRADED_DISCUSSION = 5,
        ULTRA_NON_GRADED_DISCUSSION = 6,
        ULTRA_GRADEABLE_SCORM_WITH_SUBMISSION = 7,
        ULTRA_GRADEABLE_SCORM_WITHOUT_SUBMISSION = 8,
        ULTRA_NON_GRADEABLE_SCORM = 9,
        EMPTY_LM = 10,
        LM_WITH_GRADED_ITEMS = 11,
        LM_WITH_NONGRADED_ITEMS = 12,
        LM_WITH_DISCUSSION = 13,
        LM_WITH_SINGLE_DISCUSSION = 14,
        EMPTY_FOLDER = 15,
        FOLDER_WITH_GRADED_ITEMS_ORIGINAL = 16,
        FOLDER_WITH_NONGRADED_ITEMS_ORIGINAL = 17,
        FOLDER_WITH_DISCUSSION_ORIGINAL = 18,
        FOLDER_WITH_GRADED_ITEMS_ULTRA = 19,
        FOLDER_WITH_NONGRADED_ITEMS_ULTRA = 20,
        FOLDER_WITH_DISCUSSION_ULTRA = 21
    };

    enum RwdContentSettingsGroup
    {
        GROUP_TITLE = 0,
        DETAILS_INFORMATION = 1,
        GRADING_SUBMISSION = 2,
        MORE_OPTIONS_CONTENT = 3,
        PARTICIPATION_GRADING = 4
    };

    enum RwdContentSettingsParams
    {
        PARAM_TITLE = 0,
        VISIBILITY = 1,
        DISPLAY_IN_COURSE_CONTENT = 2,
        GRADE_DISCUSSION = 3,
        DUE_DATE = 4,
        DESCRIPTION = 5,
        ATTEMPTS = 6,
        MAX_POINTS_EDITABLE = 7,
        MAX_POINTS_NON_EDITABLE = 8,
        EDIT_ON_WEB = 9,
        POST_FIRST = 10,
        PARTICIPATE_BY = 11
    };

    enum DiscussionContentUpdateType
    {
        DISC_CONTENT_STATUS_UNCHANGED = 0,
        DISC_CONTENT_STATUS_TRUE = 1,
        DISC_CONTENT_STATUS_FALSE = 2
    };

    enum AnnouncementGroup
    {
        AnnouncementGroupDraft = 0,
        AnnouncementGroupCurrent = 1,
        AnnouncementGroupPending = 2,
        AnnouncementGroupExpired = 3
    };

    enum UltraUiLandingPageType
    {
        UltraUiLandingPageTypeActivityStream = 0,
        UltraUiLandingPageTypeCourseList = 1,
        UltraUiLandingPageTypeInstitutionPage = 2
    };

    enum ScreenLoadType
    {
        ScreenLoadTypePageStart = 0,
        ScreenLoadTypePageLazyLoad = 1,
        ScreenLoadTypeCache = 2
    };

    enum ActivityStreamApiVersion
    {
        ActivityStreamApiVersionV1 = 0,
        ActivityStreamApiVersionV2 = 1
    };

    enum UiSectionNameType
    {
        UiSectionNameTypeMoreOptionAndContent = 0
    };

    enum UiPropertyNameType
    {
        UiPropertyNameTypeViewOnWeb = 0
    };

    namespace MessageFolderType
    {
        constexpr const_string INBOX_FOLDER_MESSAGES = "0";
        constexpr const_string SENT_FOLDER_MESSAGES = "1";
        constexpr const_string CUSTOM_FODLER_MESSAGES = "2";
    }

    namespace NewRelicTransactionType
    {
        constexpr const_string NR_ACTIVITY_STREAM_SETTINGS = "ACTIVITY_STREAM_SETTINGS";
        constexpr const_string NR_RENEW_SESSION_FAILED = "RENEW_SESSION_FAILED";
        constexpr const_string NR_SESSION_EXPIRY_LOGOUT = "SESSION_EXPIRY_LOGOUT";
        constexpr const_string NR_SESSION_USER_LOGOUT = "SESSION_USER_LOGOUT";
        constexpr const_string NR_SESSION_LOGIN = "SESSION_LOGIN";
    }

    namespace NewRelicAttributeType
    {
        constexpr const_string NR_SESSION_ID = "ssessionId";
        constexpr const_string NR_TRANSACTION_TYPE = "transactionType";
        constexpr const_string NR_LOGIN_TYPE = "loginType";
        constexpr const_string NR_SCHOOL_NAME = "schoolName";
        constexpr const_string NR_SCHOOL_ID = "schoolId";
        constexpr const_string NR_USER_ID = "userId";
    }

    enum MembershipRoles
    {
        BbStudent = 0,
        BbInstructor = 1,
        BbTeachingAssistant = 2,
        BbCourseBuilder = 3,
        BbGrader = 4,
        BbGuest = 5,
        BbFacilitator = 6
    };

    enum UiExpansionContentType
    {
        LearningModuleDescriptionExpansionStatus = 0,
        DiscussionTopicExpansionStatus = 1,
        DiscussionGradeDetailsExpansionStatus = 2,
        DiscussionFeedbackExpansionStatus = 3,
        DiscussionDescriptionExpansionStatus = 4
    };

    enum RetryContentType
    {
        StartDiscussionThreadWithRetry = 0,
        ReplyDiscussionPostWithRetry = 1,
        EditDiscussionPostWithRetry = 2,
        DeleteDiscussionPostWithRetry = 3,
        PostDraftedDiscussionWithRetry = 4
    };

    namespace UiExpansionContentKeys
    {
        constexpr const_string UiExpansionContentKey_OutlineObjectId = "course_outline_id";
        constexpr const_string UiExpansionContentKey_DiscussionId = "discussion_id";
        constexpr const_string UiExpansionContentKey_AssignedGroupId = "assigned_group_id";
    }



}

#endif