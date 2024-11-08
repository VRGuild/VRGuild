// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGCharacterAPI.h"
#include "Global/API/BPL/CBPLCharacter.h"


void UCWGCharacterAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern GetCharacterPattern(TEXT(R"(GET\s+/api/character$)"));
    FRegexPattern CreateCharacterPattern(TEXT(R"(POST\s+/api/character$)"));
    FRegexPattern UpdateCharacterPattern(TEXT(R"(PATCH\s+/api/character/(\d+)$)"));
    FRegexPattern GetCharacterByUserIdPattern(TEXT(R"(GET\s+/api/character/user/(\d+)$)"));
    FRegexPattern GetCharacterByNicknamePattern(TEXT(R"(GET\s+/api/character/nickname/([^/]+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(GetCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterGetCallBack(req, res);
    }
    else if (FRegexMatcher(CreateCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterCreateCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetCharacterByUserIdPattern, UrlToMatch).FindNext())
    {
        CharacterGetByUserIdCallBack(req, res);
    }
    else if (FRegexMatcher(GetCharacterByNicknamePattern, UrlToMatch).FindNext())
    {
        CharacterGetByNicknameCallBack(req, res);
    }
}

void UCWGCharacterAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern GetCharacterPattern(TEXT(R"(GET\s+/api/character$)"));
    FRegexPattern CreateCharacterPattern(TEXT(R"(POST\s+/api/character$)"));
    FRegexPattern UpdateCharacterPattern(TEXT(R"(PATCH\s+/api/character/(\d+)$)"));
    FRegexPattern GetCharacterByUserIdPattern(TEXT(R"(GET\s+/api/character/user/(\d+)$)"));
    FRegexPattern GetCharacterByNicknamePattern(TEXT(R"(GET\s+/api/character/nickname/([^/]+)$)"));
    if (FRegexMatcher(GetCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetCallBack();
    }
    else if (FRegexMatcher(CreateCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterCreateCallBack();
    }
    else if (FRegexMatcher(UpdateCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterUpdateCallBack();
    }
    else if (FRegexMatcher(GetCharacterByUserIdPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetByUserIdCallBack();
    }
    else if (FRegexMatcher(GetCharacterByNicknamePattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetByNicknameCallBack();
    }
}

void UCWGCharacterAPI::CharacterGetCall()
{
    this->API = FString::Printf(TEXT("api/character"));
    HttpGetCall();
}

void UCWGCharacterAPI::CharacterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    OnCharacterGetCallBack(ParsedResponse.data);
}

void UCWGCharacterAPI::CharacterCreateCall(const FCharacterInfo& CharacterInfo)
{
    this->API = TEXT("api/character");
    HttpPostCall<FCharacterInfo>(CharacterInfo);
}


void UCWGCharacterAPI::CharacterCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    OnCharacterCreateCallBack(ParsedResponse.data);

}

void UCWGCharacterAPI::CharacterUpdateCall(const FString& CharacterId, const FCharacterInfo& CharacterInfo)
{
    this->API = FString::Printf(TEXT("api/character/%s"), *CharacterId);
    HttpPatchCall<FCharacterInfo>(CharacterInfo);
}

void UCWGCharacterAPI::CharacterUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    OnCharacterUpdateCallBack(ParsedResponse.data);
}

void UCWGCharacterAPI::CharacterGetByUserIdCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/character/user/%s"), *UserId);
    HttpGetCall();
}

void UCWGCharacterAPI::CharacterGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    OnCharacterGetByUserIdCallBack(ParsedResponse.data);
}

void UCWGCharacterAPI::CharacterGetByNicknameCall(const FString& Nickname)
{
    this->API = FString::Printf(TEXT("api/character/nickname/%s"), *Nickname);
    HttpGetCall();
}

void UCWGCharacterAPI::CharacterGetByNicknameCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    OnCharacterGetByNicknameCallBack(ParsedResponse.data);
}