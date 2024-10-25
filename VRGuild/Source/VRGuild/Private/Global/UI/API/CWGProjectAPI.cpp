// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGProjectAPI.h"

void UCWGProjectAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+))"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
    FRegexPattern GetProjectAllPattern(TEXT(R"(GET\s+/api/project/summary)"));

    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support)"));
    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support/(\d+))"));
    FRegexPattern GetProjectSupportPorjectPattern(TEXT(R"(GET\s+/api/support/project/(\d+))"));
    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+))"));

    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("%s"), *UrlToMatch);
    if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("POST new project"));
        ProjectNewProjectPostCallBack(req, res);
    }
    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("PATCH update project"));
        ProjectPatchCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectByIdPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetProjectByIdPattern, UrlToMatch);
        Matcher.FindNext();
        FString ProjectId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET Project ID: %s"), *ProjectId);
        ProjectDetailGetCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(DeleteProjectPattern, UrlToMatch);
        Matcher.FindNext();
        FString ProjectId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("DELETE Project ID: %s"), *ProjectId);
        ProjectDetailDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectAllPattern, UrlToMatch).FindNext())
    {
        ProjectAllGetCallBack(req, res);
    }
    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
    {
        ProjectSupportPostCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
    {
        ProjectSupportDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectSupportPorjectPattern, UrlToMatch).FindNext())
    {
        ProjectSupportGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectSupportTeamPattern, UrlToMatch).FindNext())
    {
        ProjectSupportTeamGetCallBack(req, res);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}


void UCWGProjectAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+))"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
    FRegexPattern GetProjectAllPattern(TEXT(R"(GET\s+/api/project/summary)"));

    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support)"));
    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support/(\d+))"));
    FRegexPattern GetProjectSupportPorjectPattern(TEXT(R"(GET\s+/api/support/project/(\d+))"));
    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+))"));

    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("%s"), *UrlToMatch);
    if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("POST new project"));
        OnFailProjectNewProjectPostCallBack();
    }
    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("PATCH update project"));
        OnFailProjectPatchCallBack();
    }
    else if (FRegexMatcher(GetProjectByIdPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetProjectByIdPattern, UrlToMatch);
        Matcher.FindNext();
        FString ProjectId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET Project ID: %s"), *ProjectId);
        OnFailProjectDetailGetCallBack();
    }
    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(DeleteProjectPattern, UrlToMatch);
        Matcher.FindNext();
        FString ProjectId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("DELETE Project ID: %s"), *ProjectId);
        OnFailProjectDetailDeleteCallBack();
    }
    else if (FRegexMatcher(GetProjectAllPattern, UrlToMatch).FindNext())
    {
        OnFailProjectAllGetCallBack();
    }
    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportPostCallBack();
    }
    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportDeleteCallBack();
    }
    else if (FRegexMatcher(GetProjectSupportPorjectPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportGetCallBack();
    }
    else if (FRegexMatcher(GetProjectSupportTeamPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportTeamGetCallBack();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}

void UCWGProjectAPI::ProjectNewProjectPostCall(FProjectAPI projectInfo)
{
    this->API = "api/project";

    HttpPostCall<FProjectAPI>(projectInfo);
}

void UCWGProjectAPI::ProjectNewProjectPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectInfoAPI ParseData;
    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
    OnProjectNewProjectPostCallBack(ParseData);
}

void UCWGProjectAPI::ProjectPatchCall(FProjectAPI projectInfo)
{
    this->API = "api/project";

    HttpPostCall<FProjectAPI>(projectInfo);
}

void UCWGProjectAPI::ProjectPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectInfoAPI ParseData;
    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
    OnProjectPatchCallBack(ParseData);
}

void UCWGProjectAPI::ProjectDetailGetCall(int32 projectId)
{
    this->API = "api/project/" + FString::FromInt(projectId) + "/detail";

    HttpGetCall();
}

void UCWGProjectAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectDetailAPI ParseData;
    ParseData = JsonPerse<FProjectDetailAPI>(jsonString);
    OnProjectDetailGetCallBack(ParseData);
}

void UCWGProjectAPI::ProjectDetailDeleteCall(int32 projectId)
{
    this->API = "api/project/" + FString::FromInt(projectId);

    HttpDeleteCall();
}

void UCWGProjectAPI::ProjectDetailDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnProjectDetailDeleteCallBack();
}

void UCWGProjectAPI::ProjectAllGetCall()
{
    this->API = "api/project/summary";

    HttpGetCall();
}

void UCWGProjectAPI::ProjectAllGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectAllGetCallBack(ParseData);
}

void UCWGProjectAPI::ProjectSupportPostCall(FProjectSupportAPI supportInfo)
{
    this->API = "api/support";

    HttpPostCall<FProjectSupportAPI>(supportInfo);
}

void UCWGProjectAPI::ProjectSupportPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportPostCallBack(ParseData);
}
void UCWGProjectAPI::ProjectSupportDeleteCall(int32 supportId)
{
    this->API = "api/support" + FString::FromInt(supportId);

    HttpDeleteCall();
}

void UCWGProjectAPI::ProjectSupportDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportDeleteCallBack(ParseData);
}

void UCWGProjectAPI::ProjectSupportGetCall(int32 supportId)
{
    this->API = "api/support/project/" + FString::FromInt(supportId);

    HttpGetCall();
}

void UCWGProjectAPI::ProjectSupportGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportGetCallBack(ParseData);
}
void UCWGProjectAPI::ProjectSupportTeamGetCall(int32 teamId)
{
    this->API = "api/support/team/" + FString::FromInt(teamId);

    HttpGetCall();
}

void UCWGProjectAPI::ProjectSupportTeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportTeamGetCallBack(ParseData);
}
