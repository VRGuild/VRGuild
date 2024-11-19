// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGEmailAPI.generated.h"

struct FEmailAPI;
/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGEmailAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
protected:

    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Send Email
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void EmailSendPostCall(const FEmailAPI& EmailInfo);
    void EmailSendPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnEmailSendPostCallBack(const FEmailAPI& EmailInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailEmailSendPostCallBack();

};
