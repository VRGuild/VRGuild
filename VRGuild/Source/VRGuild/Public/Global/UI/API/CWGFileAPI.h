// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGFileAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGFileAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
protected:

    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Upload File
    UFUNCTION(BlueprintCallable, Category = "File API")
    void FileUploadCall(const FString& FilePath);
    void FileUploadCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "File API")
    void OnFileUploadCallBack(const FString& FileURL);
    UFUNCTION(BlueprintImplementableEvent, Category = "File API")
    void OnFailFileUploadCallBack(const FString& ErrorMessage);

    UFUNCTION(BlueprintCallable, Category = "File API")
    void FileDownloadCall(const FString& FileURL);
    void FileDownloadCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "File API")
    void OnFileDownloadCallBack(const FBaseFile& FileData);
    UFUNCTION(BlueprintImplementableEvent, Category = "File API")
    void OnFailFileDownloadCallBack(const FString& ErrorMessage);

    UFUNCTION(BlueprintCallable, Category = "File API")
    void BinaryPNGUploadCall(const TArray<uint8>& PNGData, const FString& FileName = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "File API")
    void BinaryUploadCall(const TArray<uint8>& PNGData);

protected:
    bool LoadFileToArray(const FString& FilePath, TArray<uint8>& FileContent);
    FString GetFileExtension(const FString& FilePath);

    void HttpBinaryUploadCall(const TArray<uint8>& BinaryData);

protected:
    // HTTP File Upload Helper
    void HttpFileUploadCall(const TArray<uint8>& FileData, const FString& FileName, const FString& FileType)
    {
        if (bHttpWaitResponse)
            return;
        bHttpWaitResponse = true;

        FHttpModule& httpModule = FHttpModule::Get();
        TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
        FString Boundary = "---BoundaryString";
        FString ContentType = FString::Printf(TEXT("multipart/form-data; boundary=%s"), *Boundary);

        TArray<uint8> RequestContent;
        FString BeginBoundary = FString::Printf(TEXT("--%s\r\n"), *Boundary);
        FString EndBoundary = FString::Printf(TEXT("\r\n--%s--\r\n"), *Boundary);

        FString FileHeader = FString::Printf(
            TEXT("Content-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n")
            TEXT("Content-Type: %s\r\n\r\n"),
            *FileName, *FileType);

        FTCHARToUTF8 BeginBoundaryConverter(*BeginBoundary);
        FTCHARToUTF8 FileHeaderConverter(*FileHeader);
        FTCHARToUTF8 EndBoundaryConverter(*EndBoundary);

        RequestContent.Append((uint8*)BeginBoundaryConverter.Get(), BeginBoundaryConverter.Length());
        RequestContent.Append((uint8*)FileHeaderConverter.Get(), FileHeaderConverter.Length());
        RequestContent.Append(FileData);
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
    };

    // HTTP File Download Helper
    void HttpFileDownloadCall()
    {
        if (bHttpWaitResponse)
            return;
        bHttpWaitResponse = true;

        FHttpModule& httpModule = FHttpModule::Get();
        TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

        SetOAuthToken();

        req->SetURL(this->URL + this->API);
        req->SetVerb(TEXT("GET"));
        if (!OAuthToken.IsEmpty())
            req->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + OAuthToken);

        req->OnProcessRequestComplete().BindUObject(this, &UCWGBaseAPI::HttpCallBack);
        req->ProcessRequest();
    };

};
