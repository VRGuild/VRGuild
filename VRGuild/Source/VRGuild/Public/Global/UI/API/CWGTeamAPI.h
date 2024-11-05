// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGTeamAPI.generated.h"

struct FTeamDetailResponse;
struct FTeamListResponse;
struct FTeamInfo;

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGTeamAPI : public UCWGBaseAPI
{
	GENERATED_BODY()

public:
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Team
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamCreateCall(const FTeamInfo& TeamInfo);
    void TeamCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamCreateCallBack(const FTeamInfo& TeamInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamCreateCallBack();

    // Get Team
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamGetCall(const FString& TeamId);
    void TeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamGetCallBack(const FTeamInfo& TeamInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamGetCallBack();

    // Update Team
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamUpdateCall(const FString& TeamId, const FTeamInfo& TeamInfo);
    void TeamUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamUpdateCallBack(const FTeamInfo& TeamInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamUpdateCallBack();

    // Get Team List
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamListGetCall();
    void TeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamListGetCallBack(const TArray<FTeamInfo>& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamListGetCallBack();

    // Get User Team List
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamListByUserIdGetCall(const FString& UserId);
    void TeamListByUserIdGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamListByUserIdGetCallBack(const TArray<FTeamInfo>& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamListByUserIdGetCallBack();

    // Apply To Team
    UFUNCTION(BlueprintCallable, Category = "Team API")
    void TeamApplyCall(const FString& TeamId);
    void TeamApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnTeamApplyCallBack(const FTeamInfo& TeamInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Team API")
    void OnFailTeamApplyCallBack(const FString& ErrorMessage);
};
