// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGEtherAPI.h"
#include "Global/API/BPL/CBPLEther.h"


void UCWGEtherAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateEtherPattern(TEXT(R"(POST\s+/api/ether$)"));
    FRegexPattern GetEtherPattern(TEXT(R"(GET\s+/api/ether/(\d+)$)"));
    FRegexPattern GetEtherListPattern(TEXT(R"(GET\s+/api/ether/list$)"));
    FRegexPattern GetEtherHistoryPattern(TEXT(R"(GET\s+/api/ether/history/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateEtherPattern, UrlToMatch).FindNext())
    {
        EtherCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherPattern, UrlToMatch).FindNext())
    {
        EtherGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherListPattern, UrlToMatch).FindNext())
    {
        EtherListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherHistoryPattern, UrlToMatch).FindNext())
    {
        EtherHistoryGetCallBack(req, res);
    }
}

void UCWGEtherAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");

    // Parse error message from response
    if (res->GetResponseCode() == 400 || res->GetResponseCode() == 401 || res->GetResponseCode() == 404)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }
    }

    FRegexPattern CreateEtherPattern(TEXT(R"(POST\s+/api/ether$)"));
    FRegexPattern GetEtherPattern(TEXT(R"(GET\s+/api/ether/(\d+)$)"));
    FRegexPattern GetEtherListPattern(TEXT(R"(GET\s+/api/ether/list$)"));
    FRegexPattern GetEtherHistoryPattern(TEXT(R"(GET\s+/api/ether/history/(\d+)$)"));

    if (FRegexMatcher(CreateEtherPattern, UrlToMatch).FindNext())
    {
        OnFailEtherCreateCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(GetEtherPattern, UrlToMatch).FindNext())
    {
        OnFailEtherGetCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(GetEtherListPattern, UrlToMatch).FindNext())
    {
        OnFailEtherListGetCallBack();
    }
    else if (FRegexMatcher(GetEtherHistoryPattern, UrlToMatch).FindNext())
    {
        OnFailEtherHistoryGetCallBack();
    }
}

void UCWGEtherAPI::EtherCreateCall(const FEther& Ether)
{
    this->API = TEXT("api/ether");
    HttpPostCall<FEther>(Ether);
}

void UCWGEtherAPI::EtherCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherResponse ParsedResponse = JsonPerse<FEtherResponse>(JsonString);

    OnEtherCreateCallBack(ParsedResponse.data);
}

void UCWGEtherAPI::EtherGetCall(const FString& EtherId)
{
    this->API = FString::Printf(TEXT("api/ether/%s"), *EtherId);
    HttpGetCall();
}

void UCWGEtherAPI::EtherGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherResponse ParsedResponse = JsonPerse<FEtherResponse>(JsonString);

    OnEtherGetCallBack(ParsedResponse.data);
}

void UCWGEtherAPI::EtherListGetCall()
{
    this->API = TEXT("api/ether/list");
    HttpGetCall();
}

void UCWGEtherAPI::EtherListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherListResponse ParsedResponse = JsonPerse<FEtherListResponse>(JsonString);

    OnEtherListGetCallBack(ParsedResponse.data);
}

void UCWGEtherAPI::EtherHistoryGetCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/ether/history/%s"), *UserId);
    HttpGetCall();
}

void UCWGEtherAPI::EtherHistoryGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherBalanceResponse ParsedResponse = JsonPerse<FEtherBalanceResponse>(JsonString);

    OnEtherHistoryGetCallBack(ParsedResponse.data);
}