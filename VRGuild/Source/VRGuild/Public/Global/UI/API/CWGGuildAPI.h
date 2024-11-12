// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGCharacterAPI.h"
#include "CWGGuildAPI.generated.h"

struct FGuildDetailResponse;
struct FGuildInfo;
/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGGuildAPI : public UCWGCharacterAPI
{
	GENERATED_BODY()

protected:
	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Guild
    UFUNCTION(BlueprintCallable, Category = "Guild API")
    void GuildCreateCall(const FGuildInfo& GuildInfo);
    void GuildCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnGuildCreateCallBack(const FGuildInfo& GuildInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnFailGuildCreateCallBack();

    // Get Guild
    UFUNCTION(BlueprintCallable, Category = "Guild API")
    void GuildGetCall(const FString& GuildId);
    void GuildGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnGuildGetCallBack(const FGuildInfo& GuildInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnFailGuildGetCallBack();

    // Update Guild
    UFUNCTION(BlueprintCallable, Category = "Guild API")
    void GuildUpdateCall(const FString& GuildId, const FGuildInfo& GuildInfo);
    void GuildUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnGuildUpdateCallBack(const FGuildInfo& GuildInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnFailGuildUpdateCallBack();

    // Apply To Guild
    UFUNCTION(BlueprintCallable, Category = "Guild API")
    void GuildApplyCall(const FString& GuildId);
    void GuildApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnGuildApplyCallBack(const FGuildInfo& GuildInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Guild API")
    void OnFailGuildApplyCallBack(const FString& ErrorMessage);
	
};
