// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGTeamAPI.h"

void UCWGTeamAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostTeamPattern(TEXT(R"(POST\s+/api/team$)"));
    FRegexPattern PatchTeamPattern(TEXT(R"(PATCH\s+/api/team$)"));
    FRegexPattern GetTeamByIdPattern(TEXT(R"(GET\s+/api/team/(\d+)$)"));
    FRegexPattern DeleteTeamByIdPattern(TEXT(R"(DELETE\s+/api/team/(\d+)$)"));
    FRegexPattern GetTeamByManagerPattern(TEXT(R"(GET\s+/api/team/manager$)"));
    FRegexPattern PostTeamByMemberPattern(TEXT(R"(POST\s+/api/team/member$)"));
    FRegexPattern DeleteTeamByMemberPattern(TEXT(R"(DELETE\s+/api/team/member$)"));
    FRegexPattern GetTeamByMembersSearchPattern(TEXT(R"(GET\s+/api/team/members/search$)"));

    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support$)"));
    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support$)"));
    FRegexPattern GetProjectSupportPattern(TEXT(R"(GET\s+/api/support/project/(\d+)$)"));
    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+)$)"));

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
    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
    {
        ProjectSupportPostCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
    {
        ProjectSupportDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectSupportPattern, UrlToMatch).FindNext())
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

void UCWGTeamAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern PostTeamPattern(TEXT(R"(POST\s+/api/team$)"));
    FRegexPattern PatchTeamPattern(TEXT(R"(PATCH\s+/api/team$)"));
    FRegexPattern GetTeamByIdPattern(TEXT(R"(GET\s+/api/team/(\d+)$)"));
    FRegexPattern DeleteTeamByIdPattern(TEXT(R"(DELETE\s+/api/team/(\d+)$)"));
    FRegexPattern GetTeamByManagerPattern(TEXT(R"(GET\s+/api/team/manager$)"));
    FRegexPattern PostTeamByMemberPattern(TEXT(R"(POST\s+/api/team/member$)"));
    FRegexPattern DeleteTeamByMemberPattern(TEXT(R"(DELETE\s+/api/team/member$)"));
    FRegexPattern GetTeamByMembersSearchPattern(TEXT(R"(GET\s+/api/team/members/search$)"));

    FRegexPattern PostProjectSupportPattern(TEXT(R"(POST\s+/api/support$)"));
    FRegexPattern DeleteProjectSupportPattern(TEXT(R"(DELETE\s+/api/support$)"));
    FRegexPattern GetProjectSupportPattern(TEXT(R"(GET\s+/api/support/project/(\d+)$)"));
    FRegexPattern GetProjectSupportTeamPattern(TEXT(R"(GET\s+/api/support/team/(\d+)$)"));

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
    else if (FRegexMatcher(PostProjectSupportPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportPostCallBack();
    }
    else if (FRegexMatcher(DeleteProjectSupportPattern, UrlToMatch).FindNext())
    {
        OnFailProjectSupportDeleteCallBack();
    }
    else if (FRegexMatcher(GetProjectSupportPattern, UrlToMatch).FindNext())
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

void UCWGTeamAPI::TeamPostCall(FTeamInfoAPI teamInfo)
{
    this->API = "api/team";

    HttpPostCall<FTeamInfoAPI>(teamInfo);
}

void UCWGTeamAPI::TeamPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamPostCallBack(ParseData.data);
}

void UCWGTeamAPI::TeamPatchCall(FTeamInfoAPI teamInfo)
{
    this->API = "api/team";

    HttpPatchCall<FTeamInfoAPI>(teamInfo);
}

void UCWGTeamAPI::TeamPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamPatchCallBack(ParseData.data);
}

void UCWGTeamAPI::TeamGetCall(int32 TeamId)
{
    this->API = "api/team/" + FString::FromInt( TeamId);

    HttpGetCall();
}

void UCWGTeamAPI::TeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamGetCallBack(ParseData.data);
}

void UCWGTeamAPI::TeamDeleteCall(int32 TeamId)
{
    this->API = "api/team/" + FString::FromInt(TeamId);

    HttpDeleteCall();
}

void UCWGTeamAPI::TeamDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnTeamDeleteCallBack();
}

void UCWGTeamAPI::TeamManagerGetCall()
{
    this->API = "api/team/manager";

    HttpGetCall();
}

void UCWGTeamAPI::TeamManagerGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamInfoDataArrayAPI ParseData;
    ParseData = JsonPerse<FTeamInfoDataArrayAPI>(jsonString);
    OnTeamManagerGetCallBack(ParseData);
}

void UCWGTeamAPI::TeamMemberPostCall(FTeamIdAPI TeamId)
{
    this->API = "api/team/member";

    HttpPostCall<FTeamIdAPI>(TeamId);
}

void UCWGTeamAPI::TeamMemberPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamMemberPostCallBack(ParseData.data);
}

void UCWGTeamAPI::TeamMemberDeleteCall(FTeamIdAPI TeamId)
{
    this->API = "api/team/member";

    HttpDeleteCall<FTeamIdAPI>(TeamId);
}

void UCWGTeamAPI::TeamMemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamDetailInfoDataAPI ParseData;
    ParseData = JsonPerse<FTeamDetailInfoDataAPI>(jsonString);
    OnTeamMemberDeleteCallBack(ParseData.data);
}

void UCWGTeamAPI::TeamMemberSearchGetCall()
{
    this->API = "api/team/manager/search";

    HttpGetCall();
}

void UCWGTeamAPI::TeamMemberSearchGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FTeamInfoDataArrayAPI ParseData;
    ParseData = JsonPerse<FTeamInfoDataArrayAPI>(jsonString);
    OnTeamMemberSearchGetCallBack(ParseData);
}


void UCWGTeamAPI::ProjectSupportPostCall(FProjectSupportAPI supportInfo)
{
    this->API = "api/support";

    HttpPostCall<FProjectSupportAPI>(supportInfo);
}

void UCWGTeamAPI::ProjectSupportPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportPostCallBack(ParseData);
}
void UCWGTeamAPI::ProjectSupportDeleteCall(int32 supportId)
{
    this->API = "api/support" + FString::FromInt(supportId);

    HttpDeleteCall();
}

void UCWGTeamAPI::ProjectSupportDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportDeleteCallBack(ParseData);
}

void UCWGTeamAPI::ProjectSupportGetCall(int32 supportId)
{
    this->API = "api/support/project/" + FString::FromInt(supportId);

    HttpGetCall();
}

void UCWGTeamAPI::ProjectSupportGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportGetCallBack(ParseData);
}
void UCWGTeamAPI::ProjectSupportTeamGetCall(int32 teamId)
{
    this->API = "api/support/team/" + FString::FromInt(teamId);

    HttpGetCall();
}

void UCWGTeamAPI::ProjectSupportTeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FProjectAllDataAPI ParseData;
    ParseData = JsonPerse<FProjectAllDataAPI>(jsonString);
    OnProjectSupportTeamGetCallBack(ParseData);
}
