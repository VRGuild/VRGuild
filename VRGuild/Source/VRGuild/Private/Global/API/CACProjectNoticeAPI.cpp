// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACProjectNoticeAPI.h"

UCACProjectNoticeAPI::UCACProjectNoticeAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACProjectNoticeAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACProjectNoticeAPI::InitializeComponent()
{
	Super::InitializeComponent();
}

void UCACProjectNoticeAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    //https://claude.ai/chat/be261741-4a3c-42af-bdd7-137bde4455a2 참고

    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+))"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" ") + req->GetURL();


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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}

void UCACProjectNoticeAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
}

void UCACProjectNoticeAPI::ProjectNewProjectPostCall(FProjectAPI projectInfo)
{
	this->API = "api/project";

    HttpPostCall<FProjectAPI>(projectInfo);
}

void UCACProjectNoticeAPI::ProjectNewProjectPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectInfoAPI ParseData;
    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
    OnProjectNewProjectPostCallBack(ParseData);
}

void UCACProjectNoticeAPI::ProjectPatchCall(FProjectAPI projectInfo)
{
    this->API = "api/project";

    HttpPostCall<FProjectAPI>(projectInfo);
}

void UCACProjectNoticeAPI::ProjectPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectInfoAPI ParseData;
    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
    OnProjectPatchCallBack(ParseData);
}

void UCACProjectNoticeAPI::ProjectDetailGetCall(int32 projectId)
{
    this->API = "api/project/" + projectId;

    HttpGetCall();
}

void UCACProjectNoticeAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectInfoAPI ParseData;
    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
    OnProjectPatchCallBack(ParseData);
}

void UCACProjectNoticeAPI::ProjectDetailDeleteCall(int32 projectId)
{
    this->API = "api/project/" + projectId;

    HttpDeleteCall();
}

void UCACProjectNoticeAPI::ProjectDetailDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnProjectDetailDeleteCallBack();
}
