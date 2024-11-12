// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGFileAPI.h"
#include "Global/API/BPL/CBPLFile.h"


void UCWGFileAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern UploadFilePattern(TEXT(R"(POST\s+/api/file/upload$)"));
    FRegexPattern DownloadFilePattern(TEXT(R"(GET\s+/api/file/download\?url=([^&]+)$)"));
    FRegexPattern UploadPNGPattern(TEXT(R"(POST\s+/api/file/png/upload$)"));
    FRegexPattern UploadBinaryPattern(TEXT(R"(POST\s+/api/file/binary/upload$)"));

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
    else if (FRegexMatcher(UploadPNGPattern, UrlToMatch).FindNext())
    {
        FileUploadCallBack(req, res);
    }
    else if (FRegexMatcher(UploadBinaryPattern, UrlToMatch).FindNext())
    {
        FileUploadCallBack(req, res);
    }
}

void UCWGFileAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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
    FRegexPattern UploadPNGPattern(TEXT(R"(POST\s+/api/file/png/upload$)"));
    FRegexPattern UploadBinaryPattern(TEXT(R"(POST\s+/api/file/binary/upload$)"));

    if (FRegexMatcher(UploadFilePattern, UrlToMatch).FindNext() ||
        FRegexMatcher(UploadPNGPattern, UrlToMatch).FindNext() ||
        FRegexMatcher(UploadBinaryPattern, UrlToMatch).FindNext())
    {
        OnFailFileUploadCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(DownloadFilePattern, UrlToMatch).FindNext())
    {
        OnFailFileDownloadCallBack(ErrorMessage);
    }
}


/// 파일자체 업로드

void UCWGFileAPI::FileUploadCall(const FString& FilePath)
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

void UCWGFileAPI::FileUploadCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    FString FileURL = JsonObject->GetStringField(TEXT("url"));
    OnFileUploadCallBack(FileURL);
}


// 다운로드 URL로
void UCWGFileAPI::FileDownloadCall(const FString& FileURL)
{
    this->API = FString::Printf(TEXT("%s"), *FPlatformHttp::UrlEncode(FileURL));
    HttpFileDownloadCall();
}

void UCWGFileAPI::FileDownloadCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FBaseFile FileData;
    FileData.URL = req->GetURL();
    FileData.binary = res->GetContent();

    OnFileDownloadCallBack(FileData);
}


bool UCWGFileAPI::LoadFileToArray(const FString& FilePath, TArray<uint8>& FileContent)
{
    return FFileHelper::LoadFileToArray(FileContent, *FilePath);
}

// 파일 확장자 추출하는 거
FString UCWGFileAPI::GetFileExtension(const FString& FilePath)
{
    return FPaths::GetExtension(FilePath).ToLower();
}


// png 만
void UCWGFileAPI::BinaryPNGUploadCall(const TArray<uint8>& PNGData, const FString& FileName)
{
    if (PNGData.Num() == 0)
    {
        OnFailFileUploadCallBack(TEXT("유효하지 않은 PNG 데이터입니다."));
        return;
    }
    this->API = TEXT("api/file/png/upload");
    HttpFileUploadCall(PNGData, FileName, TEXT("image/png"));
}


// 바이너리만



void UCWGFileAPI::BinaryUploadCall(const TArray<uint8>& PNGData)
{
    if (PNGData.Num() == 0)
    {
        OnFailFileUploadCallBack(TEXT("유효하지 않은 PNG 데이터입니다."));
        return;
    }
    this->API = TEXT("api/file/binary/upload");
    HttpBinaryUploadCall(PNGData);
}

void UCWGFileAPI::HttpBinaryUploadCall(const TArray<uint8>& BinaryData)
{
    if (bHttpWaitResponse)
        return;
    bHttpWaitResponse = true;

    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
    FString Boundary = TEXT("---BoundaryString");
    FString ContentType = FString::Printf(TEXT("multipart/form-data; boundary=%s"), *Boundary);

    // 멀티파트 폼 데이터 구성
    TArray<uint8> RequestContent;
    FString BeginBoundary = FString::Printf(TEXT("--%s\r\n"), *Boundary);
    FString EndBoundary = FString::Printf(TEXT("\r\n--%s--\r\n"), *Boundary);

    // 파일 데이터 헤더
    FString FileHeader = TEXT("Content-Disposition: form-data; name=\"file\"\r\n")
        TEXT("Content-Type: application/octet-stream\r\n\r\n");

    // 요청 본문 조립
    FTCHARToUTF8 BeginBoundaryConverter(*BeginBoundary);
    FTCHARToUTF8 FileHeaderConverter(*FileHeader);
    FTCHARToUTF8 EndBoundaryConverter(*EndBoundary);

    RequestContent.Append((uint8*)BeginBoundaryConverter.Get(), BeginBoundaryConverter.Length());
    RequestContent.Append((uint8*)FileHeaderConverter.Get(), FileHeaderConverter.Length());
    RequestContent.Append(BinaryData);
    RequestContent.Append((uint8*)EndBoundaryConverter.Get(), EndBoundaryConverter.Length());

    SetOAuthToken();

    req->SetURL(this->URL + this->API);
    req->SetVerb(TEXT("POST"));
    req->SetHeader(TEXT("Content-Type"), *ContentType);
    if (!OAuthToken.IsEmpty())
        req->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + OAuthToken);

    req->SetContent(RequestContent);
    req->OnProcessRequestComplete().BindUObject(this, &UCWGBaseAPI::HttpCallBack);
    req->ProcessRequest();
}