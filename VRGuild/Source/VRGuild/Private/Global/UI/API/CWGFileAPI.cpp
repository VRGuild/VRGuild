// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGFileAPI.h"
#include "Global/API/BPL/CBPLFile.h"

#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"



// JSON 파싱 및 struct 변환을 위한 함수
FFileUploadResponse ParseJsonToStruct(const FString& JsonString)
{
    FFileUploadResponse Response;

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        // fileURLs 배열 파싱
        const TArray<TSharedPtr<FJsonValue>>* UrlArray;
        if (JsonObject->TryGetArrayField(TEXT("fileURLs"), UrlArray))
        {
            for (const auto& Url : *UrlArray)
            {
                Response.fileURLs.Add(Url->AsString());
            }
        }

        // message 파싱
        Response.message = JsonObject->GetStringField(TEXT("message"));
    }

    return Response;
}


TArray<uint8> FStringToUint8(const FString& InString)
{
    TArray<uint8> OutBytes;

    // Handle empty strings
    if (InString.Len() > 0)
    {
        FTCHARToUTF8 Converted(*InString); // Convert to UTF8
        OutBytes.Append(reinterpret_cast<const uint8*>(Converted.Get()), Converted.Length());
    }

    return OutBytes;
}

FString UCWGFileAPI::AddData(FString Name, FString Value)
{
    return FString(TEXT("\r\n"))
        + BoundaryBegin
        + FString(TEXT("Content-Disposition: form-data; name=\""))
        + Name
        + FString(TEXT("\"\r\n\r\n"))
        + Value;
}


void UCWGFileAPI::UploadFile(const FFileData& FullFilePath)
{
    FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule.CreateRequest();

    // We set the api URL
    HttpRequest->SetURL(this->URL + "api/files/seper");

    HttpRequest->SetVerb(TEXT("POST"));
    
    // Create a boundary label, for the header
    BoundaryLabel = FString(TEXT("---BoundaryString")) + FString::FromInt(FMath::Rand());
    // boundary label for begining of every payload chunk 
    BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
    // boundary label for the end of payload
    BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

    // Set the content-type for server to know what are we going to send
    HttpRequest->SetHeader(TEXT("Content-Type"), FString(TEXT("multipart/form-data; boundary=")) + BoundaryLabel);

    // This is binary content of the request
    TArray<uint8> CombinedContent;

    // First, we add the boundary for the file, which is different from text payload
    FString FileBoundaryString = FString(TEXT("\r\n"))
        + BoundaryBegin
        + FString(TEXT("Content-Disposition: form-data; name=\"multipartFiles\"; filename=\""))
        + "CustomImage" + "\"\r\n"
        + "Content-Type: image/png"
        + FString(TEXT("\r\n\r\n"));
    
    // Notice, we convert all strings into uint8 format using FStringToUint8
    CombinedContent.Append(FStringToUint8(FileBoundaryString));

    // Append the file data
    CombinedContent.Append(FullFilePath.multipartFiles);

    // Let's add couple of text values to the payload
    CombinedContent.Append(FStringToUint8(AddData("pathFiles", "trash")));

    // Finally, add a boundary at the end of the payload
    CombinedContent.Append(FStringToUint8(BoundaryEnd));

    // Set the request content
    HttpRequest->SetContent(CombinedContent);

    // Hook a lambda(anonymous function) to when we receive a response
    HttpRequest->OnProcessRequestComplete().BindLambda(
        [this](
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable {
                UE_LOG(LogTemp, Error, TEXT("Connection."));

                if (connectedSuccessfully) {
                    FString Result = pResponse.Get()->GetContentAsString();
                    OnFileUploadCallBack(Result);
                }
                else {
                    OnFailFileUploadCallBack();
                    switch (pRequest->GetStatus()) {
                    case EHttpRequestStatus::Failed_ConnectionError:
                        UE_LOG(LogTemp, Error, TEXT("Connection failed."));
                    default:
                        UE_LOG(LogTemp, Error, TEXT("Request failed."));
                    }
                }
        });

    // Send the request 
    HttpRequest->ProcessRequest();
}


void UCWGFileAPI::UploadMultyFile(const FFileInfoDatas& FileInfos)
{
    FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule.CreateRequest();

    HttpRequest->SetURL(this->URL + "api/files");
    HttpRequest->SetVerb(TEXT("POST"));

    BoundaryLabel = FString(TEXT("---BoundaryString")) + FString::FromInt(FMath::Rand());
    BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
    BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

    HttpRequest->SetHeader(TEXT("Content-Type"),
        FString::Printf(TEXT("multipart/form-data; boundary=%s"), *BoundaryLabel));

    TArray<uint8> CombinedContent;
    TArray<uint8> OutBinaryData;

    // 각 파일 정보 처리
    for (const FFileInfo& FileInfo : FileInfos.multipartFiles)
    {
        if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileInfo.fileName))
        {
            UE_LOG(LogTemp, Error, TEXT("File does not exist: %s"), *FileInfo.fileName);
            continue;
        }
        // 파일 데이터를 바이너리 배열로 읽어오기
        if (!FFileHelper::LoadFileToArray(OutBinaryData, *FileInfo.fileName))
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FileInfo.fileName);
            continue ;
        }

        // 경로 정리
        FString CleanFileName = FPaths::GetCleanFilename(FileInfo.fileName);  // 파일 이름만 추출
        FString NormalizedPath = FPaths::ConvertRelativePathToFull(FileInfo.filePath);  // 전체 경로로 변환
        FPaths::NormalizeFilename(NormalizedPath);  // 경로 정규화

        // 파일 확장자와 Content-Type 결정
        FString Extension = FPaths::GetExtension(FileInfo.fileName).ToLower();
        FString ContentType = TEXT("application/octet-stream");  // 기본값

        // 파일 타입에 따른 Content-Type 설정
        if (Extension == TEXT("jpg") || Extension == TEXT("jpeg"))
            ContentType = TEXT("image/jpeg");
        else if (Extension == TEXT("png"))
            ContentType = TEXT("image/png");
        else if (Extension == TEXT("pdf"))
            ContentType = TEXT("application/pdf");
        else if (Extension == TEXT("txt"))
            ContentType = TEXT("text/plain");
        // 필요한 다른 파일 타입들 추가...

        // 파일 경계 문자열 생성
        FString FileBoundary = TEXT("\r\n") + BoundaryBegin +
            TEXT("Content-Disposition: form-data; name=\"multipartFiles\"; filename=\"") +
            CleanFileName + TEXT("\"\r\n") +
            TEXT("Content-Type: ") + ContentType + TEXT("\r\n\r\n");

        FTCHARToUTF8 BoundaryConverter(*FileBoundary);
        CombinedContent.Append((uint8*)BoundaryConverter.Get(), BoundaryConverter.Length());
        CombinedContent.Append(OutBinaryData);
    }

    CombinedContent.Append(FStringToUint8(AddData("filePath", FileInfos.filePath + "/")));

    // 마지막 경계 추가
    CombinedContent.Append(FStringToUint8(BoundaryEnd));

    HttpRequest->SetContent(CombinedContent);

    HttpRequest->OnProcessRequestComplete().BindLambda(
        [this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess && Response.IsValid())
            {
                FString Result = Response->GetContentAsString();
                OnFileUploadCallBack(Result);
            }
            else
            {
                OnFailFileUploadCallBack();
                if (!bSuccess)
                {
                    UE_LOG(LogTemp, Error, TEXT("Upload failed: Connection error"));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Upload failed: Invalid response"));
                }
            }
        });

    HttpRequest->ProcessRequest();
}

void UCWGFileAPI::UploadMultyBinary(const FFileDatas& FullFilePath)
{
    FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule.CreateRequest();

    HttpRequest->SetURL(this->URL + "api/files");
    HttpRequest->SetVerb(TEXT("POST"));

    BoundaryLabel = FString(TEXT("---BoundaryString")) + FString::FromInt(FMath::Rand());
    BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
    BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

    HttpRequest->SetHeader(TEXT("Content-Type"),
        FString::Printf(TEXT("multipart/form-data; boundary=%s"), *BoundaryLabel));

    TArray<uint8> CombinedContent;

    for (const FFileData& File : FullFilePath.multipartFiles)
    {
        // 파일 확장자와 Content-Type 결정
        FString Extension = FPaths::GetExtension(File.fileName).ToLower();
        FString ContentType = TEXT("application/octet-stream");  // 기본값

        // 파일 타입에 따른 Content-Type 설정
        if (Extension == TEXT("jpg") || Extension == TEXT("jpeg"))
            ContentType = TEXT("image/jpeg");
        else if (Extension == TEXT("png"))
            ContentType = TEXT("image/png");
        else if (Extension == TEXT("pdf"))
            ContentType = TEXT("application/pdf");
        else if (Extension == TEXT("txt"))
            ContentType = TEXT("text/plain");
        // 필요한 다른 파일 타입들 추가...

        // 파일 경계 문자열 생성 (Content-Type 포함)
        FString FileBoundary = TEXT("\r\n") + BoundaryBegin +
            TEXT("Content-Disposition: form-data; name=\"multipartFiles\"; filename=\"") +
            File.fileName + TEXT("\"\r\n") +
            TEXT("Content-Type: ") + ContentType + TEXT("\r\n\r\n");

        FTCHARToUTF8 BoundaryConverter(*FileBoundary);
        CombinedContent.Append((uint8*)BoundaryConverter.Get(), BoundaryConverter.Length());
        CombinedContent.Append(File.multipartFiles);
    }

    CombinedContent.Append(FStringToUint8(AddData("filePath", FullFilePath.filePath + "/")));
    CombinedContent.Append(FStringToUint8(BoundaryEnd));

    HttpRequest->SetContent(CombinedContent);

    HttpRequest->OnProcessRequestComplete().BindLambda(
        [this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess && Response.IsValid())
            {
                FString Result = Response->GetContentAsString();

                FString JsonString = Result;

                // JSON을 struct로 변환
                FFileUploadResponse Response = ParseJsonToStruct(JsonString);

                // 결과 사용 예시
                for (const FString& Url : Response.fileURLs)
                {
                    UE_LOG(LogTemp, Log, TEXT("File URL: %s"), *Url);
                }
                UE_LOG(LogTemp, Log, TEXT("Message: %s"), *Response.message);

                OnFileUploadCallBack(Response.fileURLs[0]);
            }
            else
            {
                OnFailFileUploadCallBack();
                if (!bSuccess)
                {
                    UE_LOG(LogTemp, Error, TEXT("Upload failed: Connection error"));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Upload failed: Invalid response"));
                }
            }
        });

    HttpRequest->ProcessRequest();
}
