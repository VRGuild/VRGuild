// Fill out your copyright notice in the Description page of Project Settings.
#include "Global/API/CACPdfAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACPdfAPI::UCACPdfAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACPdfAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACPdfAPI::InitializeComponent()
{
    Super::InitializeComponent();

    OwnerPlayerController = nullptr;
    if (Owner->IsA<ACPCBasePlayerController>())
    {
        OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
    }
}

void UCACPdfAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetPdfsPattern(TEXT(R"(GET\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern RegisterPdfPattern(TEXT(R"(POST\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern UpdatePdfPattern(TEXT(R"(PATCH\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern DeletePdfPattern(TEXT(R"(DELETE\s+/api/tile/pdf/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetPdfsPattern, UrlToMatch).FindNext())
    {
        GetPdfsByChannelCallBack(req, res);
    }
    else if (FRegexMatcher(RegisterPdfPattern, UrlToMatch).FindNext())
    {
        RegisterPdfCallBack(req, res);
    }
    else if (FRegexMatcher(UpdatePdfPattern, UrlToMatch).FindNext())
    {
        UpdatePdfCallBack(req, res);
    }
    else if (FRegexMatcher(DeletePdfPattern, UrlToMatch).FindNext())
    {
        DeletePdfCallBack(req, res);
    }
}

void UCACPdfAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetPdfsPattern(TEXT(R"(GET\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern RegisterPdfPattern(TEXT(R"(POST\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern UpdatePdfPattern(TEXT(R"(PATCH\s+/api/tile/pdf/([^/]+))"));
    FRegexPattern DeletePdfPattern(TEXT(R"(DELETE\s+/api/tile/pdf/([^/]+))"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetPdfsPattern, UrlToMatch).FindNext())
    {
        OnFailGetPdfsByChannelCallBack();
    }
    else if (FRegexMatcher(RegisterPdfPattern, UrlToMatch).FindNext())
    {
        OnFailRegisterPdfCallBack();
    }
    else if (FRegexMatcher(UpdatePdfPattern, UrlToMatch).FindNext())
    {
        OnFailUpdatePdfCallBack();
    }
    else if (FRegexMatcher(DeletePdfPattern, UrlToMatch).FindNext())
    {
        OnFailDeletePdfCallBack();
    }
}

// Get PDFs Implementation
void UCACPdfAPI::GetPdfsByChannelCall(const FString& channelId)
{
    this->API = FString::Printf(TEXT("api/tile/pdf/%s"), *channelId);
    HttpGetCall();
}

void UCACPdfAPI::GetPdfsByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FPdfListResponse ParseData;
    ParseData = JsonPerse<FPdfListResponse>(jsonString);
    OnGetPdfsByChannelCallBack(ParseData);
}

// Register PDF Implementation
void UCACPdfAPI::RegisterPdfCall(const FString& channelId, const FPdfCreateUpdateRequest& PdfData)
{
    this->API = FString::Printf(TEXT("api/tile/pdf/%s"), *channelId);
    HttpPostCall<FPdfCreateUpdateRequest>(PdfData);
}

void UCACPdfAPI::RegisterPdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FPdfAPIResponse ParseData;
    ParseData = JsonPerse<FPdfAPIResponse>(jsonString);
    OnRegisterPdfCallBack(ParseData);
}

// Update PDF Implementation
void UCACPdfAPI::UpdatePdfCall(const FString& pdfId, const FPdfCreateUpdateRequest& PdfData)
{
    this->API = FString::Printf(TEXT("api/tile/pdf/%s"), *pdfId);
    HttpPatchCall<FPdfCreateUpdateRequest>(PdfData);
}

void UCACPdfAPI::UpdatePdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FPdfAPIResponse ParseData;
    ParseData = JsonPerse<FPdfAPIResponse>(jsonString);
    OnUpdatePdfCallBack(ParseData);
}

// Delete PDF Implementation
void UCACPdfAPI::DeletePdfCall(const FString& pdfId)
{
    this->API = FString::Printf(TEXT("api/tile/pdf/%s"), *pdfId);
    HttpDeleteCall();
}

void UCACPdfAPI::DeletePdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString jsonString = res->GetContentAsString();
    FPdfAPIResponse ParseData;
    ParseData = JsonPerse<FPdfAPIResponse>(jsonString);
    OnDeletePdfCallBack(ParseData);
}