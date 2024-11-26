// Fill out your copyright notice in the Description page of Project Settings.
#include "Global/API/CACObjectAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACObjectAPI::UCACObjectAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACObjectAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACObjectAPI::InitializeComponent()
{
    Super::InitializeComponent();

    OwnerPlayerController = nullptr;
    if (Owner->IsA<ACPCBasePlayerController>())
    {
        OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
    }
}

void UCACObjectAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetObjectsPattern(TEXT(R"(GET\s+/api/tile/object/([^/]+))"));
    FRegexPattern CreateObjectPattern(TEXT(R"(POST\s+/api/tile/object/([^/]+))"));
    FRegexPattern UpdateObjectPattern(TEXT(R"(PUT\s+/api/tile/object/([^/]+)/([^/]+))"));
    FRegexPattern DeleteObjectPattern(TEXT(R"(DELETE\s+/api/tile/object/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetObjectsPattern, UrlToMatch).FindNext())
    {
        GetObjectsByChannelCallBack(req, res);
    }
    else if (FRegexMatcher(CreateObjectPattern, UrlToMatch).FindNext())
    {
        CreateObjectCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateObjectPattern, UrlToMatch).FindNext())
    {
        UpdateObjectCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteObjectPattern, UrlToMatch).FindNext())
    {
        DeleteObjectCallBack(req, res);
    }
}

void UCACObjectAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetObjectsPattern(TEXT(R"(GET\s+/api/tile/object/([^/]+))"));
    FRegexPattern CreateObjectPattern(TEXT(R"(POST\s+/api/tile/object/([^/]+))"));
    FRegexPattern UpdateObjectPattern(TEXT(R"(PUT\s+/api/tile/object/([^/]+)/([^/]+))"));
    FRegexPattern DeleteObjectPattern(TEXT(R"(DELETE\s+/api/tile/object/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetObjectsPattern, UrlToMatch).FindNext())
    {
        OnFailGetObjectsByChannelCallBack();
    }
    else if (FRegexMatcher(CreateObjectPattern, UrlToMatch).FindNext())
    {
        OnFailCreateObjectCallBack();
    }
    else if (FRegexMatcher(UpdateObjectPattern, UrlToMatch).FindNext())
    {
        OnFailUpdateObjectCallBack();
    }
    else if (FRegexMatcher(DeleteObjectPattern, UrlToMatch).FindNext())
    {
        OnFailDeleteObjectCallBack();
    }
}

// Get Objects Implementation
void UCACObjectAPI::GetObjectsByChannelCall(const FString& channelId)
{
    this->API = FString::Printf(TEXT("api/tile/object/%s"), *channelId);
    HttpGetCall();
}

void UCACObjectAPI::GetObjectsByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FObjectListResponse ParseData;
    ParseData = JsonPerse<FObjectListResponse>(jsonString);
    OnGetObjectsByChannelCallBack(ParseData);
}

// Create Object Implementation
void UCACObjectAPI::CreateObjectCall(const FString& channelId, const FObjectCreateUpdateRequest& ObjectData)
{
    this->API = FString::Printf(TEXT("api/tile/object/%s"), *channelId);
    HttpPostCall<FObjectCreateUpdateRequest>(ObjectData);
}

void UCACObjectAPI::CreateObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FObjectResponse ParseData;
    ParseData = JsonPerse<FObjectResponse>(jsonString);
    OnCreateObjectCallBack(ParseData);
}

// Update Object Implementation
void UCACObjectAPI::UpdateObjectCall(const FString& channelId, const FString& objectId, const FObjectCreateUpdateRequest& ObjectData)
{
    this->API = FString::Printf(TEXT("api/tile/object/%s/%s"), *channelId, *objectId);
    HttpPutCall<FObjectCreateUpdateRequest>(ObjectData);
}

void UCACObjectAPI::UpdateObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FObjectResponse ParseData;
    ParseData = JsonPerse<FObjectResponse>(jsonString);
    OnUpdateObjectCallBack(ParseData);
}

// Delete Object Implementation
void UCACObjectAPI::DeleteObjectCall(const FString& objectId)
{
    this->API = FString::Printf(TEXT("api/tile/object/%s"), *objectId);
    HttpDeleteCall();
}

void UCACObjectAPI::DeleteObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    OnDeleteObjectCallBack();
}