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

	UFUNCTION(BlueprintCallable)
	void ChannelGetCall();
	void ChannelGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChannelGetCallBack(FChannelInfoDataListAPI ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailChannelGetCallBack();

	UFUNCTION(BlueprintCallable)
	void ChannelPostCall(FChannelnfoCreateAPI ChannelData);
	void ChannelPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChannelPostCallBack(FChannelInfoAPI ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailChannelPostCallBack();

	UFUNCTION(BlueprintCallable)
	void ChannelPatchCall(FChannelInfoUpdateAPI ChannelData);
	void ChannelPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChannelPatchCallBack(FChannelInfoAPI ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailChannelPatchCallBack();

	UFUNCTION(BlueprintCallable)
	void ChannelSearchIdGetCall(FString channeld);
	void ChannelSearchIdGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChannelSearchIdGetCallBack(FChannelInfoAPI ChannelData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailChannelSearchIdGetCallBack();

	UFUNCTION(BlueprintCallable)
	void ChannelSearchIdDeleteCall(FString channeld);
	void ChannelSearchIdDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChannelSearchIdDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailChannelSearchIdDeleteCallBack();


public:
	UFUNCTION(BlueprintCallable)
	TArray<FTileInfo> DefaultTile();
};
