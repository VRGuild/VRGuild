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
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
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
    FRegexPattern GetProjectListPattern(TEXT(R"(GET\s+/api/project/list/(\d+)$)"));
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

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectCreateCallBack();
    }
}

void UCWGProjectAPI::ProjectGetCall(const int64& ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectGetCallBack();
    }
}

void UCWGProjectAPI::ProjectUpdateCall(const int64& ProjectId, const FProjectInfo& ProjectInfo)
{
    this->API = FString::Printf(TEXT("api/project/%d"), ProjectId);
    HttpPatchCall<FProjectInfo>(ProjectInfo);
}

void UCWGProjectAPI::ProjectUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectUpdateCallBack();
    }
}

void UCWGProjectAPI::ProjectDetailGetCall(const int64& ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/detail/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectDetailResponse ParsedResponse = JsonPerse<FProjectDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectDetailGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectDetailGetCallBack();
    }
}

void UCWGProjectAPI::ProjectListGetCall(const int64& Number)
{
    this->API = FString::Printf(TEXT("api/project/list/%d"), Number);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectListResponse ParsedResponse = JsonPerse<FProjectListResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectListGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectListGetCallBack();
    }
}

void UCWGProjectAPI::ProjectTeamListGetCall(const int64& ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/team/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectTeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectTeamListResponse ParsedResponse = JsonPerse<FProjectTeamListResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectTeamListGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailProjectTeamListGetCallBack();
    }
}

void UCWGProjectAPI::ProjectCommentListGetCall(const int64& ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/comment/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectCommentListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FProjectResponse ParsedResponse = JsonPerse<FProjectResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnProjectCommentListGetCallBack(ParsedResponse.data.commentList);
    }
    else
    {
        OnFailProjectCommentListGetCallBack();
    }
}

void UCWGProjectAPI::ProjectApplyCall(const int64& ProjectId)
{
    this->API = FString::Printf(TEXT("api/project/apply/%d"), ProjectId);
    HttpGetCall();
}

void UCWGProjectAPI::ProjectApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
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