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
    if (res->GetResponseCode() == 400)
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

    if (ParsedResponse.status == "success")
    {
        OnTeamCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamCreateCallBack();
    }
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

    if (ParsedResponse.status == "success")
    {
        OnTeamGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamGetCallBack();
    }
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

    if (ParsedResponse.status == "success")
    {
        OnTeamUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamUpdateCallBack();
    }
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

    if (ParsedResponse.status == "success")
    {
        OnTeamListGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamListGetCallBack();
    }
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

    if (ParsedResponse.status == "success")
    {
        OnTeamListByUserIdGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamListByUserIdGetCallBack();
    }
}

void UCWGTeamAPI::TeamApplyCall(const FString& TeamId)
{
    this->API = FString::Printf(TEXT("api/team/apply/%s"), *TeamId);
    HttpGetCall();
}

void UCWGTeamAPI::TeamApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    // 특별한 에러 처리 (400 에러의 경우 중복 지원 등)
    if (res->GetResponseCode() == 400)
    {
        FString JsonString = res->GetContentAsString();
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

        FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }

        OnFailTeamApplyCallBack(ErrorMessage);
        return;
    }

    FString JsonString = res->GetContentAsString();
    FTeamDetailResponse ParsedResponse = JsonPerse<FTeamDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnTeamApplyCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailTeamApplyCallBack(TEXT("API 호출에 실패했습니다."));
    }
}