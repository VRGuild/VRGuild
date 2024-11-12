// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGFileAPI.h"
#include "Global/API/BPL/CBPLFile.h"

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