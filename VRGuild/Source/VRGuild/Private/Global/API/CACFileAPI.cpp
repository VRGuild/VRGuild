// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACFileAPI.h"
#include "Global/API/CACFileAPI.h"
#include "Global/API/BPL/CBPLBase.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

UCACFileAPI::UCACFileAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACFileAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACFileAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACFileAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern UploadFilePattern(TEXT(R"(POST\s+/api/file/upload$)"));
    FRegexPattern DownloadFilePattern(TEXT(R"(GET\s+/api/file/download\?url=([^&]+)$)"));
    FRegexPattern DeleteFilePattern(TEXT(R"(DELETE\s+/api/file\?url=([^&]+)$)"));
    FRegexPattern FileInfoPattern(TEXT(R"(GET\s+/api/file\?url=([^&]+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(UploadFilePattern, UrlToMatch).FindNext())
    {
        FileUploadCallBack(req, res);
    }
    else if (FRegexMatcher(DownloadFilePattern, UrlToMatch).FindNext())
    {
        FileDownloadCallBack(req, res);
    }
}

void UCACFileAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    FString ErrorMessage = TEXT("파일 처리 중 오류가 발생했습니다.");

    if (res->GetResponseCode() == 400 || res->GetResponseCode() == 404)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }
    }

    FRegexPattern UploadFilePattern(TEXT(R"(POST\s+/api/file/upload$)"));
    FRegexPattern DownloadFilePattern(TEXT(R"(GET\s+/api/file/download\?url=([^&]+)$)"));
    FRegexPattern DeleteFilePattern(TEXT(R"(DELETE\s+/api/file\?url=([^&]+)$)"));
    FRegexPattern FileInfoPattern(TEXT(R"(GET\s+/api/file\?url=([^&]+)$)"));

    if (FRegexMatcher(UploadFilePattern, UrlToMatch).FindNext())
    {
        OnFailFileUploadCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(DownloadFilePattern, UrlToMatch).FindNext())
    {
        OnFailFileDownloadCallBack(ErrorMessage);
    }
}

void UCACFileAPI::FileUploadCall(const FString& FilePath)
{
    TArray<uint8> FileContent;
    if (!LoadFileToArray(FilePath, FileContent))
    {
        OnFailFileUploadCallBack(TEXT("파일을 읽을 수 없습니다."));
        return;
    }

    FString ContentType = TEXT("application/octet-stream");
    FString Extension = GetFileExtension(FilePath);

    if (Extension == TEXT("jpg") || Extension == TEXT("jpeg"))
        ContentType = TEXT("image/jpeg");
    else if (Extension == TEXT("png"))
        ContentType = TEXT("image/png");
    else if (Extension == TEXT("pdf"))
        ContentType = TEXT("application/pdf");

    this->API = TEXT("api/file/upload");

    // 파일 이름 추출
    FString FileName = FPaths::GetCleanFilename(FilePath);

    // 새로운 HttpFileUploadCall 사용
    HttpFileUploadCall(FileContent, FileName, ContentType);
}

void UCACFileAPI::FileUploadCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    FString FileURL = JsonObject->GetStringField(TEXT("url"));
    OnFileUploadCallBack(FileURL);
}

void UCACFileAPI::FileDownloadCall(const FString& FileURL)
{
    this->API = FString::Printf(TEXT("%s"), *FPlatformHttp::UrlEncode(FileURL));
    HttpFileDownloadCall();
}

void UCACFileAPI::FileDownloadCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FBaseFile FileData;
    FileData.URL = req->GetURL();
    FileData.binary = res->GetContent();

    OnFileDownloadCallBack(FileData);
}

bool UCACFileAPI::LoadFileToArray(const FString& FilePath, TArray<uint8>& FileContent)
{
    return FFileHelper::LoadFileToArray(FileContent, *FilePath);
}

FString UCACFileAPI::GetFileExtension(const FString& FilePath)
{
    return FPaths::GetExtension(FilePath).ToLower();
}
