// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACResgisterAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCACResgisterAPI : public UCACBaseAPI
{
	GENERATED_BODY()
	
public:
	UCACResgisterAPI();

	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void ResgisterGetCall(FString nickName);
	void ResgisterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResgisterGetCallBack();
};
