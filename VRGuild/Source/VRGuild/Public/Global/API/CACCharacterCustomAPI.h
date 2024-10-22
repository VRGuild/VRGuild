// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACCharacterCustomAPI.generated.h"

struct FCharacterCustomCreate;
struct FCharacterCustomInfo;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACCharacterCustomAPI : public UCACBaseAPI
{
	GENERATED_BODY()

public:
	UCACCharacterCustomAPI();
protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void CharacterCustomGetCall();
	void CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomGetCallBack(FCharacterCustomInfo ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomGetCallBack();

	UFUNCTION(BlueprintCallable)
	void CharacterCustomCreateCall(TArray<int32> CustomList);
	void CharacterCustomCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomCreateCallBack(FCharacterCustomInfo ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomCreateCallBack();

	UFUNCTION(BlueprintCallable)
	void CharacterCustomUpdateCall(TArray<int32> CustomList);
	void CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomUpdateCallBack(FCharacterCustomInfo ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomUpdateCallBack();

	UFUNCTION(BlueprintCallable)
	void CharacterCustomDeleteCall(TArray<int32> CustomList);
	void CharacterCustomDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomDeleteCallBack();

};
