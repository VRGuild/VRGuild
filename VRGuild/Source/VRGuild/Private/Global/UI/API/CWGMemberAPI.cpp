// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGMemberAPI.h"
#include "Global/API/BPL/CBPLMember.h"

void UCWGMemberAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    Super::OnSuccessAPI(req, res);

    FRegexPattern GetMemberPattern(TEXT(R"(GET\s+/api/member/(\d+)$)"));
    FRegexPattern AcceptMemberPattern(TEXT(R"(GET\s+/api/member/apply/(\d+)$)"));
    FRegexPattern RejectMemberPattern(TEXT(R"(GET\s+/api/member/except/(\d+)$)"));
    FRegexPattern DeleteMemberPattern(TEXT(R"(DELETE\s+/api/member/delete/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(GetMemberPattern, UrlToMatch).FindNext())
    {
        MemberGetCallBack(req, res);
    }
    else if (FRegexMatcher(AcceptMemberPattern, UrlToMatch).FindNext())
    {
        MemberAcceptCallBack(req, res);
    }
    else if (FRegexMatcher(RejectMemberPattern, UrlToMatch).FindNext())
    {
        MemberRejectCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteMemberPattern, UrlToMatch).FindNext())
    {
        MemberDeleteCallBack(req, res);
    }
}

void UCWGMemberAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    Super::OnFailAPI(req, res);

    FRegexPattern GetMemberPattern(TEXT(R"(GET\s+/api/member/(\d+)$)"));
    FRegexPattern AcceptMemberPattern(TEXT(R"(GET\s+/api/member/apply/(\d+)$)"));
    FRegexPattern RejectMemberPattern(TEXT(R"(GET\s+/api/member/except/(\d+)$)"));
    FRegexPattern DeleteMemberPattern(TEXT(R"(DELETE\s+/api/member/delete/(\d+)$)"));
    FRegexPattern AcceptNewMemberPattern(TEXT(R"(PATCH\s+/api/member/accept/(\d+)$)"));
    FRegexPattern RejectNewMemberPattern(TEXT(R"(PATCH\s+/api/member/reject/(\d+)$)"));

    if (FRegexMatcher(GetMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberGetCallBack();
    }
    else if (FRegexMatcher(AcceptMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberAcceptCallBack();
    }
    else if (FRegexMatcher(RejectMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberRejectCallBack();
    }
    else if (FRegexMatcher(AcceptNewMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberNewAccpetCallBack("error reject");
    }
    else if (FRegexMatcher(RejectNewMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberNewRejectCallBack("error reject");
    }
    else if (FRegexMatcher(RejectMemberPattern, UrlToMatch).FindNext())
    {
        FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");
        if (res->GetResponseCode() == 400)
        {
            FString JsonString = res->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                ErrorMessage = JsonObject->GetStringField(TEXT("message"));
            }
        }
        OnFailMemberDeleteCallBack(ErrorMessage);
    }
}

void UCWGMemberAPI::MemberGetCall(const int64& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/%d"), MemberId);
    HttpGetCall();
}

void UCWGMemberAPI::MemberGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    OnMemberGetCallBack(ParsedResponse.data);
}

void UCWGMemberAPI::MemberAcceptCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/apply/%s"), *MemberId);
    HttpGetCall();
}

void UCWGMemberAPI::MemberAcceptCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    OnMemberAcceptCallBack(ParsedResponse.data);
}

void UCWGMemberAPI::MemberRejectCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/except/%s"), *MemberId);
    HttpGetCall();
}

void UCWGMemberAPI::MemberRejectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    OnMemberRejectCallBack(ParsedResponse.data);
}

void UCWGMemberAPI::MemberDeleteCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/delete/%s"), *MemberId);
    HttpDeleteCall();
}

void UCWGMemberAPI::MemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnMemberDeleteCallBack();
}


void UCWGMemberAPI::MemberNewAccpetCall(const int64& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/accept/%d"), MemberId);
    HttpPatchCall();
}

void UCWGMemberAPI::MemberNewAccpetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnMemberNewAccpetCallBack();
}

void UCWGMemberAPI::MemberNewRejectCall(const int64& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/reject/%d"), MemberId);
    HttpPatchCall();
}

void UCWGMemberAPI::MemberNewRejectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnMemberNewRejectCallBack();
}


