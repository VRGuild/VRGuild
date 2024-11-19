// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGEmailAPI.h"
#include "Global/API/BPL/CBPLEmail.h"


void UCWGEmailAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{

    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern PostEmailPattern(TEXT(R"(POST\s+/api/email$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(PostEmailPattern, UrlToMatch).FindNext())
    {
        EmailSendPostCallBack(req, res);
    }
}

void UCWGEmailAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern PostEmailPattern(TEXT(R"(POST\s+/api/email$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(PostEmailPattern, UrlToMatch).FindNext())
    {
        OnFailEmailSendPostCallBack();
    }
}

void UCWGEmailAPI::EmailSendPostCall(const FEmailAPI& EmailInfo)
{
    this->API = TEXT("api/email");
    HttpPostCall<FEmailAPI>(EmailInfo);
}

void UCWGEmailAPI::EmailSendPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEmailAPI ParsedResponse = JsonPerse<FEmailAPI>(JsonString);

    OnEmailSendPostCallBack(ParsedResponse);
}
