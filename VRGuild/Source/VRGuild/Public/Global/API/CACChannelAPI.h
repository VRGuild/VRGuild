// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLChannel.h"

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACChannelAPI.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACChannelAPI : public UCACBaseAPI
{
	GENERATED_BODY()
public:
	UCACChannelAPI();

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

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


