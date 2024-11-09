// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/UI/API/CWGDeveloperAPI.h"
#include "Global/API/BPL/CBPLDeveloper.h"

void UCWGDeveloperAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern CreateDeveloperPattern(TEXT(R"(POST\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperPattern(TEXT(R"(GET\s+/api/epic/developer$)"));
    FRegexPattern UpdateDeveloperPattern(TEXT(R"(PATCH\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperByUserIdPattern(TEXT(R"(GET\s+/api/epic/developer/users/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetDeveloperByUserIdPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetDeveloperByUserIdPattern, UrlToMatch);
        Matcher.FindNext();
        FString UserId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET Developer By User ID: %s"), *UserId);
        DeveloperGetByUserIdCallBack(req, res);
    }
}

void UCWGDeveloperAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern CreateDeveloperPattern(TEXT(R"(POST\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperPattern(TEXT(R"(GET\s+/api/epic/developer$)"));
    FRegexPattern UpdateDeveloperPattern(TEXT(R"(PATCH\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperByUserIdPattern(TEXT(R"(GET\s+/api/epic/developer/users/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(CreateDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperCreateCallBack();
    }
    else if (FRegexMatcher(GetDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperGetCallBack();
    }
    else if (FRegexMatcher(UpdateDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperUpdateCallBack();
    }
    else if (FRegexMatcher(GetDeveloperByUserIdPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperGetByUserIdCallBack();
    }
}

void UCWGDeveloperAPI::DeveloperCreateCall(const FDeveloperRequest& Request)
{
    this->API = TEXT("api/epic/developer");
    HttpPostCall<FDeveloperRequest>(Request);
}

void UCWGDeveloperAPI::DeveloperCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    OnDeveloperCreateCallBack(ParsedResponse.data);
}

void UCWGDeveloperAPI::DeveloperGetCall()
{
    this->API = TEXT("api/epic/developer");
    HttpGetCall();
}

void UCWGDeveloperAPI::DeveloperGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    OnDeveloperGetCallBack(ParsedResponse.data);
}

void UCWGDeveloperAPI::DeveloperUpdateCall(const FDeveloperRequest& Request)
{
    this->API = TEXT("api/epic/developer");
    HttpPatchCall<FDeveloperRequest>(Request);
}

void UCWGDeveloperAPI::DeveloperUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    OnDeveloperUpdateCallBack(ParsedResponse.data);
}

void UCWGDeveloperAPI::DeveloperGetByUserIdCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/epic/developer/users/%s"), *UserId);
    HttpGetCall();
}

void UCWGDeveloperAPI::DeveloperGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    OnDeveloperGetByUserIdCallBack(ParsedResponse.data);
}