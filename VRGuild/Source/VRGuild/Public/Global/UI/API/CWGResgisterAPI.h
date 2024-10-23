// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLRegister.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGResgisterAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FResgisterInfoDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FResgisterInfoAPI data;
};
/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGResgisterAPI : public UCWGBaseAPI
{
	GENERATED_BODY()

protected:
	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void ResgisterGetCall();
	void ResgisterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterGetCallBack(FResgisterInfoAPI parseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailResgisterGetCallBack();

	UFUNCTION(BlueprintCallable)
	void ResgisterPostCall(FResgisterCreateAPI data);
	void ResgisterPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterPostCallBack(FResgisterInfoAPI parseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailResgisterPostCallBack();

	UFUNCTION(BlueprintCallable)
	void ResgisterPatchCall(FResgisterCreateAPI data);
	void ResgisterPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterPatchCallBack(FResgisterInfoAPI parseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailResgisterPatchCallBack();

	UFUNCTION(BlueprintCallable)
	void ResgisterDeleteCall();
	void ResgisterDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailResgisterDeleteCallBack();

	UFUNCTION(BlueprintCallable)
	void ResgisterNicknameCall(FString nickname);
	void ResgisterNicknameCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterNicknameCallBack(FResgisterInfoAPI parseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailResgisterNicknameCallBack();
};
