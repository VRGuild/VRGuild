#include "Global/API/CACProjectAPI.h"
#include "Global/API/BPL/CBPLProject.h"

UCACProjectAPI::UCACProjectAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACProjectAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACProjectAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACProjectAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateProjectPattern(TEXT(R"(POST\s+/api/project$)"));
    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/project/(\d+)$)"));
    FRegexPattern UpdateProjectPattern(TEXT(R"(PATCH\s+/api/project/(\d+)$)"));
    FRegexPattern GetProjectDetailPattern(TEXT(R"(GET\s+/api/project/detail/(\d+)$)"));
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
    FRegexPattern GetProjectDetailListPattern(TEXT(R"(GET\s+/api/project/detail/list/(\d+)$)"));
    FRegexPattern GetProjectTeamPattern(TEXT(R"(GET\s+/api/project/team/(\d+)$)"));
    FRegexPattern GetProjectCommentPattern(TEXT(R"(GET\s+/api/project/comment/(\d+)$)"));
    FRegexPattern ApplyProjectPattern(TEXT(R"(GET\s+/api/project/apply/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateProjectPattern, UrlToMatch).FindNext())
    {
        ProjectCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectPattern, UrlToMatch).FindNext())
    {
        ProjectGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateProjectPattern, UrlToMatch).FindNext())
    {
        ProjectUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectDetailPattern, UrlToMatch).FindNext())
    {
        ProjectDetailGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectListPattern, UrlToMatch).FindNext())
    {
        ProjectListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectDetailListPattern, UrlToMatch).FindNext())
    {
        ProjectDetailListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectTeamPattern, UrlToMatch).FindNext())
    {
        ProjectTeamListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectCommentPattern, UrlToMatch).FindNext())
    {
        ProjectCommentListGetCallBack(req, res);
    }
    else if (FRegexMatcher(ApplyProjectPattern, UrlToMatch).FindNext())
    {
        ProjectApplyCallBack(req, res);
    }
}

void UCACProjectAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern CreateProjectPattern(TEXT(R"(POST\s+/api/project$)"));
    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/project/(\d+)$)"));
    FRegexPattern UpdateProjectPattern(TEXT(R"(PATCH\s+/api/project/(\d+)$)"));
    FRegexPattern GetProjectDetailPattern(TEXT(R"(GET\s+/api/project/detail/(\d+)$)"));
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
    FRegexPattern GetProjectDetailListPattern(TEXT(R"(GET\s+/api/project/detail/list/(\d+)$)"));
    FRegexPattern GetProjectTeamPattern(TEXT(R"(GET\s+/api/project/team/(\d+)$)"));
    FRegexPattern GetProjectCommentPattern(TEXT(R"(GET\s+/api/project/comment/(\d+)$)"));
    FRegexPattern ApplyProjectPattern(TEXT(R"(GET\s+/api/project/apply/(\d+)$)"));

    if (FRegexMatcher(CreateProjectPattern, UrlToMatch).FindNext())
    {
        OnFailProjectCreateCallBack();
    }
    else if (FRegexMatcher(GetProjectPattern, UrlToMatch).FindNext())
    {
        OnFailProjectGetCallBack();
    }
    else if (FRegexMatcher(UpdateProjectPattern, UrlToMatch).FindNext())
    {
        OnFailProjectUpdateCallBack();
    }
    else if (FRegexMatcher(GetProjectDetailPattern, UrlToMatch).FindNext())
    {
        OnFailProjectDetailGetCallBack();
    }
    else if (FRegexMatcher(GetProjectListPattern, UrlToMatch).FindNext())
    {
        OnFailProjectListGetCallBack();
    }
    else if (FRegexMatcher(GetProjectDetailListPattern, UrlToMatch).FindNext())
    {
        OnFailProjectDetailListGetCallBack();
    }
    else if (FRegexMatcher(GetProjectTeamPattern, UrlToMatch).FindNext())
    {
        OnFailProjectTeamListGetCallBack();
    }
    else if (FRegexMatcher(GetProjectCommentPattern, UrlToMatch).FindNext())
    {
        OnFailProjectCommentListGetCallBack();
    }
    else if (FRegexMatcher(ApplyProjectPattern, UrlToMatch).FindNext())
    {
        FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");
        if (res->GetResponseCode() == 400)
        {
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                ErrorMessage = JsonObject->GetStringField(TEXT("message"));
            }
        }
        OnFailProjectApplyCallBack(ErrorMessage);
    }
}

void UCACProjectAPI::ProjectCreateCall(const FProjectInfo& ProjectInfo)
{
    this->API = TEXT("api/project");
    HttpPostCall<FProjectInfo>(ProjectInfo);
}

void UCACProjectAPI::ProjectCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectCreateCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpGetCall();
}

void UCACProjectAPI::ProjectGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectGetCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectUpdateCall(const int64 ProjectId, const FProjectInfo& ProjectInfo)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpPatchCall<FProjectInfo>(ProjectInfo);
}

void UCACProjectAPI::ProjectUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectUpdateCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectDetailGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/detail/list/%d"), ProjectId);
    HttpGetCall();
}

void UCACProjectAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectDetailResponse ParsedResponse = JsonPerse<FProjectDetailResponse>(JsonString);

    OnProjectDetailGetCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectListGetCall(const int64 Number)
{
    this->API = FString::Printf(TEXT("api/project/list/%d"), Number);
    
    HttpGetCall();
}

void UCACProjectAPI::ProjectListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectPagedResponse ParsedResponse = JsonPerse<FProjectPagedResponse>(JsonString);

    OnProjectListGetCallBack(ParsedResponse);

}

void UCACProjectAPI::ProjectDetailListGetCall(const int64 Number)
{
    this->API = FString::Printf(TEXT("api/project/detail/list/%d"), Number);
    HttpGetCall();
}

void UCACProjectAPI::ProjectDetailListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectDetailPagedResponse ParsedResponse = JsonPerse<FProjectDetailPagedResponse>(JsonString);

    OnProjectDetailListGetCallBack(ParsedResponse);
}

void UCACProjectAPI::ProjectTeamListGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/team/%d"), ProjectId);
    HttpGetCall();
}

void UCACProjectAPI::ProjectTeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectTeamListResponse ParsedResponse = JsonPerse<FProjectTeamListResponse>(JsonString);

    OnProjectTeamListGetCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectCommentListGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/comment/%d"), ProjectId);
    HttpGetCall();
}

void UCACProjectAPI::ProjectCommentListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectCommentListGetCallBack(ParsedResponse.data);
}

void UCACProjectAPI::ProjectApplyCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/apply/%d"), ProjectId);
    HttpGetCall();
}

void UCACProjectAPI::ProjectApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectTeamListResponse ParsedResponse = JsonPerse<FProjectTeamListResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectApplyCallBack(ParsedResponse.data);
    }
    else
    {
        FString ErrorMessage = TEXT("프로젝트 지원에 실패했습니다.");
        if (res->GetResponseCode() == 400)
        {
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                ErrorMessage = JsonObject->GetStringField(TEXT("message"));
            }
        }
        OnFailProjectApplyCallBack(ErrorMessage);
    }
}