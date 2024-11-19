// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACEmailAPI.generated.h"

struct FEmailAPI;

/**
 * 
 */
UCLASS()
class VRGUILD_API UCACEmailAPI : public UCACBaseAPI
{
	GENERATED_BODY()

public:
    UCACEmailAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;

    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Send Email
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperCreateCall(const FEmailAPI& EmailInfo);
    void EmailSendPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnEmailSendPostCallBack(const FEmailAPI& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailEmailSendPostCallBack();
};
