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
public:
    UFUNCTION(BlueprintImplementableEvent)
    void OnFileUploadCallBack(const FString& fileUrl);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailFileUploadCallBack();

private:
    // This is the filename for screenshot, fixed for simplicity
    FString ScreenshotFileName = "C:/Users/kyoulee/Pictures/Screenshots/test.png";

    // These will be used for request body in the code
    FString BoundaryLabel = FString();
    FString BoundaryBegin = FString();
    FString BoundaryEnd = FString();

protected:

    // Main function for upload
    UFUNCTION(BlueprintCallable)
    void UploadFile(const FFileData& FullFilePath);

    UFUNCTION(BlueprintCallable)
    void UploadMultyFile(const FFileInfoDatas& FullFilePath);
    UFUNCTION(BlueprintCallable)
    void UploadMultyBinary(const FFileDatas& FullFilePath);
    // This is a function to add simple text fields to response
    FString AddData(FString Name, FString Value);

};
