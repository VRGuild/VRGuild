// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLChannel.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGChannelAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGChannelAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
public:
	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	class ACPCBasePlayerController* OwnerPlayerController;

	// Register Channel (POST /api/channel/{accountId})
	UFUNCTION(BlueprintCallable)
	void RegisterChannelCall(const FChannelnfoCreateAPI& ChannelData);
	void RegisterChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnRegisterChannelCallBack(const FChannelInfoAPI& ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailRegisterChannelCallBack();

	// Get Channel Info (GET /api/channel/{channelId})
	UFUNCTION(BlueprintCallable)
	void GetChannelInfoCall(const FString& channelId);
	void GetChannelInfoCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnGetChannelInfoCallBack(const FChannelInfoAPI& ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailGetChannelInfoCallBack();

	// Get Channel Info (GET /api/channel/{channelId})
	UFUNCTION(BlueprintCallable)
	void GetAllChannelInfoCall(const int32& page);
	void GetAllChannelInfoCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnGetAllChannelInfoCallBack(const FChannelInfoDataListAPI& ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailGetAllChannelInfoCallBack();

	// Update Channel (PUT /api/channel/{channelId})
	UFUNCTION(BlueprintCallable)
	void UpdateChannelCall(const FString& channelId, const FChannelInfoUpdateAPI& ChannelData);
	void UpdateChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateChannelCallBack(const FChannelInfoAPI& ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailUpdateChannelCallBack();

	// Delete Channel (DELETE /api/channel/{channelId})
	UFUNCTION(BlueprintCallable)
	void DeleteChannelCall(const FString& channelId);
	void DeleteChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeleteChannelCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailDeleteChannelCallBack();

public:
	UFUNCTION(BlueprintCallable)
	TArray<FTileInfo> DefaultTile();
};
