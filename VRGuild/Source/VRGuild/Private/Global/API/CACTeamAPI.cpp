// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACTeamAPI.h"

UCACTeamAPI::UCACTeamAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACTeamAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACTeamAPI::InitializeComponent()
{
	Super::InitializeComponent();
}

void UCACTeamAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostTeamPattern(TEXT(R"(POST\s+/api/team)"));
    FRegexPattern PatchTeamPattern(TEXT(R"(PATCH\s+/api/team)"));
    FRegexPattern GetTeamByIdPattern(TEXT(R"(GET\s+/api/team/(\d+))"));
    FRegexPattern DeleteTeamByIdPattern(TEXT(R"(DELETE\s+/api/team/(\d+))"));
    FRegexPattern GetTeamByManagerPattern(TEXT(R"(GET\s+/api/team/manager)"));
    FRegexPattern PostTeamByMemberPattern(TEXT(R"(POST\s+/api/team/member)"));
    FRegexPattern DeleteTeamByMemberPattern(TEXT(R"(DELETE\s+/api/team/member)"));
    FRegexPattern GetTeamByMembersSearchPattern(TEXT(R"(GET\s+/api/team/members/search)"));

    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(PostTeamPattern, UrlToMatch).FindNext())
    {
        TeamPostCallBack(req, res);
    }
    else if (FRegexMatcher(PatchTeamPattern, UrlToMatch).FindNext())
    {
        TeamPatchCallBack(req, res);
    }
    else if (FRegexMatcher(GetTeamByIdPattern, UrlToMatch).FindNext())
    {
        TeamGetCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteTeamByIdPattern, UrlToMatch).FindNext())
    {
        TeamDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetTeamByManagerPattern, UrlToMatch).FindNext())
    {
        TeamManagerGetCallBack(req, res);
    }
    else if (FRegexMatcher(PostTeamByMemberPattern, UrlToMatch).FindNext())
    {
        TeamMemberPostCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteTeamByMemberPattern, UrlToMatch).FindNext())
    {
        TeamMemberDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetTeamByMembersSearchPattern, UrlToMatch).FindNext())
    {
        TeamMemberSearchGetCallBack(req, res);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}

void UCACTeamAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostTeamPattern(TEXT(R"(POST\s+/api/team)"));
    FRegexPattern PatchTeamPattern(TEXT(R"(PATCH\s+/api/team)"));
    FRegexPattern GetTeamByIdPattern(TEXT(R"(GET\s+/api/team/(\d+))"));
    FRegexPattern DeleteTeamByIdPattern(TEXT(R"(DELETE\s+/api/team/(\d+))"));
    FRegexPattern GetTeamByManagerPattern(TEXT(R"(GET\s+/api/team/manager)"));
    FRegexPattern PostTeamByMemberPattern(TEXT(R"(POST\s+/api/team/member)"));
    FRegexPattern DeleteTeamByMemberPattern(TEXT(R"(DELETE\s+/api/team/member)"));
    FRegexPattern GetTeamByMembersSearchPattern(TEXT(R"(GET\s+/api/team/members/search)"));

    // Implementation of routing logic
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(PostTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamPostCallBack();
    }
    else if (FRegexMatcher(PatchTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamPatchCallBack();
    }
    else if (FRegexMatcher(GetTeamByIdPattern, UrlToMatch).FindNext())
    {
        OnFailTeamGetCallBack();
    }
    else if (FRegexMatcher(DeleteTeamByIdPattern, UrlToMatch).FindNext())
    {
        OnFailTeamDeleteCallBack();
    }
    else if (FRegexMatcher(GetTeamByManagerPattern, UrlToMatch).FindNext())
    {
        OnFailTeamManagerGetCallBack();
    }
    else if (FRegexMatcher(PostTeamByMemberPattern, UrlToMatch).FindNext())
    {
        OnFailTeamMemberPostCallBack();
    }
    else if (FRegexMatcher(DeleteTeamByMemberPattern, UrlToMatch).FindNext())
    {
        OnFailTeamMemberDeleteCallBack();
    }
    else if (FRegexMatcher(GetTeamByMembersSearchPattern, UrlToMatch).FindNext())
    {
        OnFailTeamMemberSearchGetCallBack();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching endpoint found for URL: %s"), *UrlToMatch);
        // Handle 404 case
    }
}

void UCACTeamAPI::TeamPostCall(FTeamInfoAPI teamInfo)
{
    this->API = "api/team";

    HttpPostCall<FTeamInfoAPI>(teamInfo);
}

void UCACTeamAPI::TeamPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamPostCallBack(ParseData.data);
}

void UCACTeamAPI::TeamPatchCall(FTeamInfoAPI teamInfo)
{
    this->API = "api/team";

    HttpPatchCall<FTeamInfoAPI>(teamInfo);
}

void UCACTeamAPI::TeamPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamPatchCallBack(ParseData.data);
}

void UCACTeamAPI::TeamGetCall(int32 TeamId)
{
    this->API = "api/team" + TeamId;

    HttpGetCall();
}

void UCACTeamAPI::TeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamGetCallBack(ParseData.data);
}

void UCACTeamAPI::TeamDeleteCall(int32 TeamId)
{
    this->API = "api/team" + TeamId;

    HttpDeleteCall();
}

void UCACTeamAPI::TeamDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnTeamDeleteCallBack();
}

void UCACTeamAPI::TeamManagerGetCall()
{
    this->API = "api/team/manager";

    HttpGetCall();
}

void UCACTeamAPI::TeamManagerGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamInfoDataArrayAPI ParseData;
    ParseData = JsonPerse<FTeamInfoDataArrayAPI>(jsonString);
    OnTeamManagerGetCallBack(ParseData);
}

void UCACTeamAPI::TeamMemberPostCall(FTeamIdAPI TeamId)
{
    this->API = "api/team/member";

    HttpPostCall<FTeamIdAPI>(TeamId);
}

void UCACTeamAPI::TeamMemberPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamMemberPostCallBack(ParseData.data);
}

void UCACTeamAPI::TeamMemberDeleteCall(FTeamIdAPI TeamId)
{
    this->API = "api/team/member";

    HttpDeleteCall<FTeamIdAPI>(TeamId);
}

void UCACTeamAPI::TeamMemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamMemberDeleteCallBack(ParseData.data);
}

void UCACTeamAPI::TeamMemberSearchGetCall()
{
    this->API = "api/team/manager/search";

    HttpGetCall();
}

void UCACTeamAPI::TeamMemberSearchGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamInfoDataArrayAPI ParseData;
    ParseData = JsonPerse<FTeamInfoDataArrayAPI>(jsonString);
    OnTeamMemberSearchGetCallBack(ParseData);
}
