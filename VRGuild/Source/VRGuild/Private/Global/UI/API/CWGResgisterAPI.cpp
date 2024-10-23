// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGResgisterAPI.h"

void UCWGResgisterAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{

    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/user/partner)"));
    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/user/partner)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/user/partner)"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/user/partner/delete)"));

    FRegexPattern GetProjectNicknamePattern(TEXT(R"(GET\s+/api/user/partner/nickname/[a-zA-Z0-9_]+)"));

	FString UrlToMatch = req->GetVerb() + TEXT(" ") + req->GetURL();

    if (FRegexMatcher(GetProjectPattern, UrlToMatch).FindNext())
    {
        ResgisterGetCallBack(req,res);
    }
    else if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
    {
        ResgisterPostCallBack(req, res);
    }
    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
    {
        ResgisterPatchCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
    {
        ResgisterDeleteCallBack(req, res);
    }
    else if (FRegexMatcher(GetProjectNicknamePattern, UrlToMatch).FindNext())
    {
        ResgisterNicknameCallBack(req, res);
    }
}

void UCWGResgisterAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetProjectPattern(TEXT(R"(GET\s+/api/user/partner)"));
    FRegexPattern PostProjectPattern(TEXT(R"(POST\s+/api/user/partner)"));
    FRegexPattern PatchProjectPattern(TEXT(R"(PATCH\s+/api/user/partner)"));
    FRegexPattern DeleteProjectPattern(TEXT(R"(DELETE\s+/api/user/partner/delete)"));

    FRegexPattern GetProjectNicknamePattern(TEXT(R"(GET\s+/api/user/partner/nickname/[a-zA-Z0-9_]+)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" ") + req->GetURL();

    if (FRegexMatcher(GetProjectPattern, UrlToMatch).FindNext())
    {
        OnFailResgisterGetCallBack();
    }
    else if (FRegexMatcher(PostProjectPattern, UrlToMatch).FindNext())
    {
        OnFailResgisterPostCallBack();
    }
    else if (FRegexMatcher(PatchProjectPattern, UrlToMatch).FindNext())
    {
        OnFailResgisterPatchCallBack();
    }
    else if (FRegexMatcher(DeleteProjectPattern, UrlToMatch).FindNext())
    {
        OnFailResgisterDeleteCallBack();
    }
    else if (FRegexMatcher(GetProjectNicknamePattern, UrlToMatch).FindNext())
    {
        OnFailResgisterNicknameCallBack();
    }
}

void UCWGResgisterAPI::ResgisterGetCall()
{
    this->API = "api/project";

    HttpGetCall();
}

void UCWGResgisterAPI::ResgisterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FResgisterInfoDataAPI ParseData;
    ParseData = JsonPerse<FResgisterInfoDataAPI>(jsonString);
    OnResgisterGetCallBack(ParseData.data);
}

void UCWGResgisterAPI::ResgisterPostCall(FResgisterCreateAPI data)
{
    this->API = "api/project";

    HttpPostCall<FResgisterCreateAPI>(data);
}

void UCWGResgisterAPI::ResgisterPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FResgisterInfoDataAPI ParseData;
    ParseData = JsonPerse<FResgisterInfoDataAPI>(jsonString);
    OnResgisterPostCallBack(ParseData.data);
}

void UCWGResgisterAPI::ResgisterPatchCall(FResgisterCreateAPI data)
{
    this->API = "api/project";

    HttpPatchCall<FResgisterCreateAPI>(data);
}

void UCWGResgisterAPI::ResgisterPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FResgisterInfoDataAPI ParseData;
    ParseData = JsonPerse<FResgisterInfoDataAPI>(jsonString);
    OnResgisterGetCallBack(ParseData.data);
}

void UCWGResgisterAPI::ResgisterDeleteCall()
{
    this->API = "api/project";

    HttpDeleteCall();
}

void UCWGResgisterAPI::ResgisterDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnResgisterDeleteCallBack();
}

void UCWGResgisterAPI::ResgisterNicknameCall(FString nickname)
{
    this->API = "api/project/nickname/" + nickname;

    HttpGetCall();
}

void UCWGResgisterAPI::ResgisterNicknameCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FResgisterInfoDataAPI ParseData;
    ParseData = JsonPerse<FResgisterInfoDataAPI>(jsonString);
    OnResgisterNicknameCallBack(ParseData.data);
}
