// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGProjectAPI.h"

void UCWGProjectAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+)/detail)"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
    FRegexPattern GetProjectAllPattern(TEXT(R"(GET\s+/api/project/summary)"));

    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}


void UCWGProjectAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
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
    this->API = "api/project/" + projectId;
    this->API += "/detail";

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
    this->API = "api/project/" + projectId;

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