// Fill out your copyright notice in the Description page of Project Settings.
#include "Global/API/CACMemoAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACMemoAPI::UCACMemoAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACMemoAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACMemoAPI::InitializeComponent()
{
    Super::InitializeComponent();

    OwnerPlayerController = nullptr;
    if (Owner->IsA<ACPCBasePlayerController>())
    {
        OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
    }
}

void UCACMemoAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetMemosPattern(TEXT(R"(GET\s+/api/tile/memo/([^/]+))"));
    FRegexPattern RegisterMemoPattern(TEXT(R"(POST\s+/api/tile/memo/([^/]+))"));
    FRegexPattern UpdateMemoPattern(TEXT(R"(PATCH\s+/api/tile/memo/([^/]+))"));
    FRegexPattern DeleteMemoPattern(TEXT(R"(DELETE\s+/api/tile/memo/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetMemosPattern, UrlToMatch).FindNext())
    {
        GetMemosByChannelCallBack(req, res);
    }
    else if (FRegexMatcher(RegisterMemoPattern, UrlToMatch).FindNext())
    {
        RegisterMemoCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateMemoPattern, UrlToMatch).FindNext())
    {
        UpdateMemoCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteMemoPattern, UrlToMatch).FindNext())
    {
        DeleteMemoCallBack(req, res);
    }
}

void UCACMemoAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetMemosPattern(TEXT(R"(GET\s+/api/tile/memo/([^/]+))"));
    FRegexPattern RegisterMemoPattern(TEXT(R"(POST\s+/api/tile/memo/([^/]+))"));
    FRegexPattern UpdateMemoPattern(TEXT(R"(PATCH\s+/api/tile/memo/([^/]+))"));
    FRegexPattern DeleteMemoPattern(TEXT(R"(DELETE\s+/api/tile/memo/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetMemosPattern, UrlToMatch).FindNext())
    {
        OnFailGetMemosByChannelCallBack();
    }
    else if (FRegexMatcher(RegisterMemoPattern, UrlToMatch).FindNext())
    {
        OnFailRegisterMemoCallBack();
    }
    else if (FRegexMatcher(UpdateMemoPattern, UrlToMatch).FindNext())
    {
        OnFailUpdateMemoCallBack();
    }
    else if (FRegexMatcher(DeleteMemoPattern, UrlToMatch).FindNext())
    {
        OnFailDeleteMemoCallBack();
    }
}

// Get Memos Implementation
void UCACMemoAPI::GetMemosByChannelCall(const FString& channelId)
{
    this->API = FString::Printf(TEXT("api/tile/memo/%s"), *channelId);
    HttpGetCall();
}

void UCACMemoAPI::GetMemosByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FMemoListResponse ParseData;
    ParseData = JsonPerse<FMemoListResponse>(jsonString);
    OnGetMemosByChannelCallBack(ParseData);
}

// Register Memo Implementation
void UCACMemoAPI::RegisterMemoCall(const FString& channelId, const FMemoCreateUpdateRequest& MemoData)
{
    this->API = FString::Printf(TEXT("api/tile/memo/%s"), *channelId);
    HttpPostCall<FMemoCreateUpdateRequest>(MemoData);
}

void UCACMemoAPI::RegisterMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FMemoAPIResponse ParseData;
    ParseData = JsonPerse<FMemoAPIResponse>(jsonString);
    OnRegisterMemoCallBack(ParseData);
}

// Update Memo Implementation
void UCACMemoAPI::UpdateMemoCall(const FString& memoId, const FMemoCreateUpdateRequest& MemoData)
{
    this->API = FString::Printf(TEXT("api/tile/memo/%s"), *memoId);
    HttpPatchCall<FMemoCreateUpdateRequest>(MemoData);
}

void UCACMemoAPI::UpdateMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FMemoAPIResponse ParseData;
    ParseData = JsonPerse<FMemoAPIResponse>(jsonString);
    OnUpdateMemoCallBack(ParseData);
}

// Delete Memo Implementation
void UCACMemoAPI::DeleteMemoCall(const FString& memoId)
{
    this->API = FString::Printf(TEXT("api/tile/memo/%s"), *memoId);
    HttpDeleteCall();
}

void UCACMemoAPI::DeleteMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FMemoAPIResponse ParseData;
    ParseData = JsonPerse<FMemoAPIResponse>(jsonString);
    OnDeleteMemoCallBack(ParseData);
}