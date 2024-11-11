// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGTeamAPI.h"
#include "Global/API/BPL/CBPLTeam.h"

void UCWGTeamAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateTeamPattern(TEXT(R"(POST\s+/api/team$)"));
    FRegexPattern GetTeamPattern(TEXT(R"(GET\s+/api/team/(\d+)$)"));
    FRegexPattern UpdateTeamPattern(TEXT(R"(PATCH\s+/api/team/(\d+)$)"));
    FRegexPattern GetTeamListPattern(TEXT(R"(GET\s+/api/team/teamlist$)"));
    FRegexPattern GetUserTeamListPattern(TEXT(R"(GET\s+/api/team/teamlist/user/(\d+)$)"));
    FRegexPattern ApplyTeamPattern(TEXT(R"(GET\s+/api/team/apply/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateTeamPattern, UrlToMatch).FindNext())
    {
        TeamCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetTeamPattern, UrlToMatch).FindNext())
    {
        TeamGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateTeamPattern, UrlToMatch).FindNext())
    {
        TeamUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetTeamListPattern, UrlToMatch).FindNext())
    {
        TeamListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetUserTeamListPattern, UrlToMatch).FindNext())
    {
        TeamListByUserIdGetCallBack(req, res);
    }
    else if (FRegexMatcher(ApplyTeamPattern, UrlToMatch).FindNext())
    {
        TeamApplyCallBack(req, res);
    }
}

void UCWGTeamAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern CreateTeamPattern(TEXT(R"(POST\s+/api/team$)"));
    FRegexPattern GetTeamPattern(TEXT(R"(GET\s+/api/team/(\d+)$)"));
    FRegexPattern UpdateTeamPattern(TEXT(R"(PATCH\s+/api/team/(\d+)$)"));
    FRegexPattern GetTeamListPattern(TEXT(R"(GET\s+/api/team/teamlist$)"));
    FRegexPattern GetUserTeamListPattern(TEXT(R"(GET\s+/api/team/teamlist/user/(\d+)$)"));
    FRegexPattern ApplyTeamPattern(TEXT(R"(GET\s+/api/team/apply/(\d+)$)"));

    FString ErrorMessage;
    if (res && res->GetResponseCode() == 400)
    {
        // Parse error message from response
        FString JsonString = res->GetContentAsString();
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }
    }

    if (FRegexMatcher(CreateTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamCreateCallBack();
    }
    else if (FRegexMatcher(GetTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamGetCallBack();
    }
    else if (FRegexMatcher(UpdateTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamUpdateCallBack();
    }
    else if (FRegexMatcher(GetTeamListPattern, UrlToMatch).FindNext())
    {
        OnFailTeamListGetCallBack();
    }
    else if (FRegexMatcher(GetUserTeamListPattern, UrlToMatch).FindNext())
    {
        OnFailTeamListByUserIdGetCallBack();
    }
    else if (FRegexMatcher(ApplyTeamPattern, UrlToMatch).FindNext())
    {
        OnFailTeamApplyCallBack(ErrorMessage);
    }
}

// Implementation of all the Call and Callback functions...
void UCWGTeamAPI::TeamCreateCall(const FTeamInfo& TeamInfo)
{
    this->API = TEXT("api/team");
    HttpPostCall<FTeamInfo>(TeamInfo);
}

void UCWGTeamAPI::TeamCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamDetailResponse ParsedResponse = JsonPerse<FTeamDetailResponse>(JsonString);

    OnTeamCreateCallBack(ParsedResponse.data);
}

void UCWGTeamAPI::TeamGetCall(const int64& TeamId)
{
    this->API = FString::Printf(TEXT("api/team/%d"), TeamId);
    HttpGetCall();
}

void UCWGTeamAPI::TeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamDetailResponse ParsedResponse = JsonPerse<FTeamDetailResponse>(JsonString);

    OnTeamGetCallBack(ParsedResponse.data);
}

void UCWGTeamAPI::TeamUpdateCall(const int64& TeamId, const FTeamInfo& TeamInfo)
{
    this->API = FString::Printf(TEXT("api/team/%d"), TeamId);
    HttpPatchCall<FTeamInfo>(TeamInfo);
}

void UCWGTeamAPI::TeamUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamDetailResponse ParsedResponse = JsonPerse<FTeamDetailResponse>(JsonString);

    OnTeamUpdateCallBack(ParsedResponse.data);
}

void UCWGTeamAPI::TeamListGetCall()
{
    this->API = TEXT("api/team/teamlist");
    HttpGetCall();
}

void UCWGTeamAPI::TeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamListResponse ParsedResponse = JsonPerse<FTeamListResponse>(JsonString);

    OnTeamListGetCallBack(ParsedResponse.data);
}

void UCWGTeamAPI::TeamListByUserIdGetCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/team/teamlist/user/%s"), *UserId);
    HttpGetCall();
}

void UCWGTeamAPI::TeamListByUserIdGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamListResponse ParsedResponse = JsonPerse<FTeamListResponse>(JsonString);

    OnTeamListByUserIdGetCallBack(ParsedResponse.data);
}

void UCWGTeamAPI::TeamApplyCall(const FString& TeamId)
{
    this->API = FString::Printf(TEXT("api/team/apply/%s"), *TeamId);
    HttpGetCall();
}

void UCWGTeamAPI::TeamApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FTeamDetailResponse ParsedResponse = JsonPerse<FTeamDetailResponse>(JsonString);

    OnTeamApplyCallBack(ParsedResponse.data);
}