// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACProjectNoticeAPI.h"
#include "Global/API/BPL/CBPLProject.h"

UCACProjectNoticeAPI::UCACProjectNoticeAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

//void UCACProjectNoticeAPI::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//void UCACProjectNoticeAPI::InitializeComponent()
//{
//	Super::InitializeComponent();
//}
//
//void UCACProjectNoticeAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    //https://claude.ai/chat/be261741-4a3c-42af-bdd7-137bde4455a2 참고
//
//    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
//    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
//    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+))"));
//    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
//    FRegexPattern GetProjectAllPattern(TEXT(R"(GET\s+/api/project/summary)"));
//
//    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support)"));
//    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support/(\d+))"));
//    FRegexPattern GetProjectSupportPorjectPattern(TEXT(R"(GET\s+/api/support/project/(\d+))"));
//    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+))"));
//
//    // Implementation of routing logic
//    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
//    UE_LOG(LogTemp, Display, TEXT("%s"), *UrlToMatch);
//    if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
//    {
//        UE_LOG(LogTemp, Display, TEXT("POST new project"));
//        ProjectNewProjectPostCallBack(req, res);
//    }
//    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
//    {
//        UE_LOG(LogTemp, Display, TEXT("PATCH update project"));
//        ProjectPatchCallBack(req, res);
//    }
//    else if (FRegexMatcher(GetProjectByIdPattern, UrlToMatch).FindNext())
//    {
//        FRegexMatcher Matcher(GetProjectByIdPattern, UrlToMatch);
//        Matcher.FindNext();
//        FString ProjectId = Matcher.GetCaptureGroup(1);
//        UE_LOG(LogTemp, Display, TEXT("GET Project ID: %s"), *ProjectId);
//        ProjectDetailGetCallBack(req, res);
//    }
//    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
//    {
//        FRegexMatcher Matcher(DeleteProjectPattern, UrlToMatch);
//        Matcher.FindNext();
//        FString ProjectId = Matcher.GetCaptureGroup(1);
//        UE_LOG(LogTemp, Display, TEXT("DELETE Project ID: %s"), *ProjectId);
//        ProjectDetailDeleteCallBack(req, res);
//    }
//    else if (FRegexMatcher(GetProjectAllPattern, UrlToMatch).FindNext())
//    {
//        ProjectAllGetCallBack(req, res);
//    }
//    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
//    {
//        ProjectSupportPostCallBack(req, res);
//    }
//    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
//    {
//        ProjectSupportDeleteCallBack(req, res);
//    }
//    else if (FRegexMatcher(GetProjectSupportPorjectPattern, UrlToMatch).FindNext())
//    {
//        ProjectSupportGetCallBack(req, res);
//    }
//    else if (FRegexMatcher(GetProjectSupportTeamPattern, UrlToMatch).FindNext())
//    {
//        ProjectSupportTeamGetCallBack(req, res);
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
//        // Handle 404 case
//    }
//}
//
//void UCACProjectNoticeAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
//    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/project)"));
//    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/project)"));
//    FRegexPattern GetProjectByIdPattern(TEXT(R"(GET\s+/api/project/(\d+))"));
//    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/project/(\d+))"));
//    FRegexPattern GetProjectAllPattern(TEXT(R"(GET\s+/api/project/summary)"));
//
//    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support)"));
//    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support/(\d+))"));
//    FRegexPattern GetProjectSupportPorjectPattern(TEXT(R"(GET\s+/api/support/project/(\d+))"));
//    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+))"));
//
//    // Implementation of routing logic
//    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
//    UE_LOG(LogTemp, Display, TEXT("%s"), *UrlToMatch);
//    if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
//    {
//        UE_LOG(LogTemp, Display, TEXT("POST new project"));
//        OnFailProjectNewProjectPostCallBack();
//    }
//    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
//    {
//        UE_LOG(LogTemp, Display, TEXT("PATCH update project"));
//        OnFailProjectPatchCallBack();
//    }
//    else if (FRegexMatcher(GetProjectByIdPattern, UrlToMatch).FindNext())
//    {
//        FRegexMatcher Matcher(GetProjectByIdPattern, UrlToMatch);
//        Matcher.FindNext();
//        FString ProjectId = Matcher.GetCaptureGroup(1);
//        UE_LOG(LogTemp, Display, TEXT("GET Project ID: %s"), *ProjectId);
//        OnFailProjectDetailGetCallBack();
//    }
//    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
//    {
//        FRegexMatcher Matcher(DeleteProjectPattern, UrlToMatch);
//        Matcher.FindNext();
//        FString ProjectId = Matcher.GetCaptureGroup(1);
//        UE_LOG(LogTemp, Display, TEXT("DELETE Project ID: %s"), *ProjectId);
//        OnFailProjectDetailDeleteCallBack();
//    }
//    else if (FRegexMatcher(GetProjectAllPattern, UrlToMatch).FindNext())
//    {
//        OnFailProjectAllGetCallBack();
//    }
//    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
//    {
//        OnFailProjectSupportPostCallBack();
//    }
//    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
//    {
//        OnFailProjectSupportDeleteCallBack();
//    }
//    else if (FRegexMatcher(GetProjectSupportPorjectPattern, UrlToMatch).FindNext())
//    {
//        OnFailProjectSupportGetCallBack();
//    }
//    else if (FRegexMatcher(GetProjectSupportTeamPattern, UrlToMatch).FindNext())
//    {
//        OnFailProjectSupportTeamGetCallBack();
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
//        // Handle 404 case
//    }
//}
//
//void UCACProjectNoticeAPI::ProjectNewProjectPostCall(FProjectAPI projectInfo)
//{
//	this->API = "api/project";
//
//    HttpPostCall<FProjectAPI>(projectInfo);
//}
//
//void UCACProjectNoticeAPI::ProjectNewProjectPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectInfoAPI ParseData;
//    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
//    OnProjectNewProjectPostCallBack(ParseData);
//}
//
//void UCACProjectNoticeAPI::ProjectPatchCall(FProjectAPI projectInfo)
//{
//    this->API = "api/project";
//
//    HttpPostCall<FProjectAPI>(projectInfo);
//}
//
//void UCACProjectNoticeAPI::ProjectPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectInfoAPI ParseData;
//    ParseData = JsonPerse<FProjectInfoAPI>(jsonString);
//    OnProjectPatchCallBack(ParseData);
//}
//
//void UCACProjectNoticeAPI::ProjectDetailGetCall(int32 projectId)
//{
//    this->API = "api/project/" + projectId;
//    this->API += "/detail";
//
//    HttpGetCall();
//}
//
//void UCACProjectNoticeAPI::ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectDetailAPI ParseData;
//    ParseData = JsonPerse<FProjectDetailAPI>(jsonString);
//    OnProjectDetailGetCallBack(ParseData);
//}
//
//void UCACProjectNoticeAPI::ProjectDetailDeleteCall(int32 projectId)
//{
//    this->API = "api/project/" + projectId;
//
//    HttpDeleteCall();
//}
//
//void UCACProjectNoticeAPI::ProjectDetailDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    OnProjectDetailDeleteCallBack();
//}
//
//void UCACProjectNoticeAPI::ProjectAllGetCall()
//{
//    this->API = "api/project/summary";
//
//    HttpGetCall();
//}
//
//void UCACProjectNoticeAPI::ProjectAllGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectAllDataAPI ParseData;
//    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
//    OnProjectAllGetCallBack(ParseData);
//}
//
//void UCACProjectNoticeAPI::ProjectSupportPostCall(FProjectSupportAPI supportInfo)
//{
//    this->API = "api/support";
//
//    HttpPostCall<FProjectSupportAPI>(supportInfo);
//}
//
//void UCACProjectNoticeAPI::ProjectSupportPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectAllDataAPI ParseData;
//    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
//    OnProjectSupportPostCallBack(ParseData);
//}
//void UCACProjectNoticeAPI::ProjectSupportDeleteCall(int32 supportId)
//{
//    this->API = "api/support" + FString::FromInt(supportId);
//
//    HttpDeleteCall();
//}
//
//void UCACProjectNoticeAPI::ProjectSupportDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectAllDataAPI ParseData;
//    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
//    OnProjectSupportDeleteCallBack(ParseData);
//}
//
//void UCACProjectNoticeAPI::ProjectSupportGetCall(int32 supportId)
//{
//    this->API = "api/support/project/" + FString::FromInt(supportId);
//
//    HttpGetCall();
//}
//
//void UCACProjectNoticeAPI::ProjectSupportGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectAllDataAPI ParseData;
//    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
//    OnProjectSupportGetCallBack(ParseData);
//}
//void UCACProjectNoticeAPI::ProjectSupportTeamGetCall(int32 teamId)
//{
//    this->API = "api/support/team/" + FString::FromInt(teamId);
//
//    HttpGetCall();
//}
//
//void UCACProjectNoticeAPI::ProjectSupportTeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
//{
//    FString jsonString = res->GetContentAsString();
//    FProjectAllDataAPI ParseData;
//    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
//    OnProjectSupportTeamGetCallBack(ParseData);
//}
