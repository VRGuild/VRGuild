// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGProjectAPI.h"
#include "Global/API/BPL/CBPLProject.h"


void UCWGProjectAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateProjectPattern(TEXT(R"(POST\s+/api/project$)"));
    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/project/(\d+)$)"));
    FRegexPattern UpdateProjectPattern(TEXT(R"(PATCH\s+/api/project/(\d+)$)"));
    FRegexPattern GetProjectDetailPattern(TEXT(R"(GET\s+/api/project/detail/(\d+)$)"));
    FRegexPattern GetProjectAccountPattern(TEXT(R"(GET\s+/api/project/account\?page=(\d+)$)"));
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
    FRegexPattern GetProjectDetailListPattern(TEXT(R"(GET\s+/api/project/detail/list/(\d+)$)"));
    FRegexPattern GetProjectTeamPattern(TEXT(R"(GET\s+/api/project/team/(\d+)$)"));
    FRegexPattern GetProjectCommentPattern(TEXT(R"(GET\s+/api/project/comment/(\d+)$)"));
    FRegexPattern ApplyProjectPattern(TEXT(R"(POST\s+/api/project/apply/epic/(\d+)$)"));

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
    else if (FRegexMatcher(GetProjectAccountPattern, UrlToMatch).FindNext())
    {
        ProjectAccountGetCallBack(req, res);
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

void UCWGProjectAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern CreateProjectPattern(TEXT(R"(POST\s+/api/project$)"));
    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/project/(\d+)$)"));
    FRegexPattern UpdateProjectPattern(TEXT(R"(PATCH\s+/api/project/(\d+)$)"));
    FRegexPattern GetProjectDetailPattern(TEXT(R"(GET\s+/api/project/detail/(\d+)$)"));
    FRegexPattern GetProjectAccountPattern(TEXT(R"(GET\s+/api/project/account\?page=(\d+)$)"));
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
    FRegexPattern GetProjectDetailListPattern(TEXT(R"(GET\s+/api/project/detail/list/(\d+)$)"));
    FRegexPattern GetProjectTeamPattern(TEXT(R"(GET\s+/api/project/team/(\d+)$)"));
    FRegexPattern GetProjectCommentPattern(TEXT(R"(GET\s+/api/project/comment/(\d+)$)"));
    FRegexPattern ApplyProjectPattern(TEXT(R"(POST\s+/api/project/apply/epic/(\d+)$)"));

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
    else if (FRegexMatcher(GetProjectAccountPattern, UrlToMatch).FindNext())
    {
        OnFailProjectAccountGetCallBack();
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

void UCWGProjectAPI::ProjectCreateCall(const FProjectInfo& ProjectInfo)
{
    this->API = TEXT("api/project");
    HttpPostCall<FProjectInfo>(ProjectInfo);
}

void UCWGProjectAPI::ProjectCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectCreateCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectGetCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectUpdateCall(const int64 ProjectId, const FProjectInfo& ProjectInfo)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpPatchCall<FProjectInfo>(ProjectInfo);
}

void UCWGProjectAPI::ProjectUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectUpdateCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectDetailGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/detail/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectWithDetailData ParsedResponse = JsonPerse<FProjectWithDetailData>(JsonString);

    OnProjectDetailGetCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectAccountGetCall(int32 page)
{
    this->API = FString::Printf(TEXT("api/project/account?page=%d"), page);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectAccountGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectPagedResponse ParsedResponse = JsonPerse<FProjectPagedResponse>(JsonString);

    OnProjectAccountGetCallBack(ParsedResponse);
}

void UCWGProjectAPI::ProjectListGetCall(const int64 Number)
{
    this->API = FString::Printf(TEXT("api/project/list/%d"), Number);

    HttpGetCall();
}

void UCWGProjectAPI::ProjectListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectPagedResponse ParsedResponse = JsonPerse<FProjectPagedResponse>(JsonString);

    OnProjectListGetCallBack(ParsedResponse);

}

void UCWGProjectAPI::ProjectDetailListGetCall(const int64 Number)
{
    this->API = FString::Printf(TEXT("api/project/detail/list/%d"), Number);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectDetailListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectDetailPagedResponse ParsedResponse = JsonPerse<FProjectDetailPagedResponse>(JsonString);

    OnProjectDetailListGetCallBack(ParsedResponse);
}

void UCWGProjectAPI::ProjectTeamListGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/team/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectTeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectTeamListResponse ParsedResponse = JsonPerse<FProjectTeamListResponse>(JsonString);

    OnProjectTeamListGetCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectCommentListGetCall(const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/comment/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectCommentListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    OnProjectCommentListGetCallBack(ParsedResponse.data);
}

void UCWGProjectAPI::ProjectApplyCall(const FProjectTeamApply& teamInfo, const int64 ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/apply/epic/%d"), ProjectId);
    HttpPostCall<FProjectTeamApply>(teamInfo);
}

void UCWGProjectAPI::ProjectApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectTeamListResponse ParsedResponse = JsonPerse<FProjectTeamListResponse>(JsonString);

    OnProjectApplyCallBack(ParsedResponse.data);

}