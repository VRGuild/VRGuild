// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Global/API/BPL/CBPLMemo.h"
#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACMemoAPI.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACMemoAPI : public UCACBaseAPI
{
    GENERATED_BODY()
public:
    UCACMemoAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    class ACPCBasePlayerController* OwnerPlayerController;

    // Get Memos (GET /api/tile/memo/{channelId})
    UFUNCTION(BlueprintCallable)
    void GetMemosByChannelCall(const FString& channelId);
    void GetMemosByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnGetMemosByChannelCallBack(const FMemoListResponse& MemoList);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailGetMemosByChannelCallBack();

    // Register Memo (POST /api/tile/memo/{channelId})
    UFUNCTION(BlueprintCallable)
    void RegisterMemoCall(const FString& channelId, const FMemoCreateUpdateRequest& MemoData);
    void RegisterMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnRegisterMemoCallBack(const FMemoAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailRegisterMemoCallBack();

    // Update Memo (PATCH /api/tile/memo/{memoId})
    UFUNCTION(BlueprintCallable)
    void UpdateMemoCall(const FString& memoId, const FMemoCreateUpdateRequest& MemoData);
    void UpdateMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnUpdateMemoCallBack(const FMemoAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailUpdateMemoCallBack();

    // Delete Memo (DELETE /api/tile/memo/{memoId})
    UFUNCTION(BlueprintCallable)
    void DeleteMemoCall(const FString& memoId);
    void DeleteMemoCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnDeleteMemoCallBack(const FMemoAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailDeleteMemoCallBack();
};