// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGDeveloperAPI.generated.h"

struct FDeveloperResponse;
struct FDeveloperRequest;

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGDeveloperAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
protected:
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperCreateCall(const FDevCreateInfo& Request);
    void DeveloperCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperCreateCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperCreateCallBack();

    // Get Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperGetCall();
    void DeveloperGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperGetCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperGetCallBack();

    // Update Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperUpdateCall(const FDeveloperRequest& Request);
    void DeveloperUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperUpdateCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperUpdateCallBack();

    // Get Developer By UserId
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperGetByUserIdCall(const FString& UserId);
    void DeveloperGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperGetByUserIdCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperGetByUserIdCallBack();
};
