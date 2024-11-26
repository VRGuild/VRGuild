// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Global/API/BPL/CBPLObject.h"
#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACObjectAPI.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACObjectAPI : public UCACBaseAPI
{
    GENERATED_BODY()
public:
    UCACObjectAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    class ACPCBasePlayerController* OwnerPlayerController;

    // Get Objects by Channel (GET /api/tile/object/{channelId})
    UFUNCTION(BlueprintCallable)
    void GetObjectsByChannelCall(const FString& channelId);
    void GetObjectsByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnGetObjectsByChannelCallBack(const FObjectListResponse& ObjectList);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailGetObjectsByChannelCallBack();

    // Create Object (POST /api/tile/object/{channelId})
    UFUNCTION(BlueprintCallable)
    void CreateObjectCall(const FString& channelId, const FObjectCreateUpdateRequest& ObjectData);
    void CreateObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnCreateObjectCallBack(const FObjectResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailCreateObjectCallBack();

    // Update Object (PUT /api/tile/object/{channelId}/{objectId})
    UFUNCTION(BlueprintCallable)
    void UpdateObjectCall(const FString& channelId, const FString& objectId, const FObjectCreateUpdateRequest& ObjectData);
    void UpdateObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnUpdateObjectCallBack(const FObjectResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailUpdateObjectCallBack();

    // Delete Object (DELETE /api/tile/object/{objectId})
    UFUNCTION(BlueprintCallable)
    void DeleteObjectCall(const FString& objectId);
    void DeleteObjectCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnDeleteObjectCallBack();
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailDeleteObjectCallBack();
};