// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGCharacterCustomAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomCreate {
	GENERATED_USTRUCT_BODY()
public:
	FCharacterCustomCreate() {};
	FCharacterCustomCreate(TArray <int32> status) : Status(status) {};

	TArray <int32> Status;
};

USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomGet {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int32 characterId;
	UPROPERTY(BlueprintReadOnly)
	FString accountId;
	UPROPERTY(BlueprintReadOnly)
	TArray <int32> Status;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCWGCharacterCustomAPI : public UCWGBaseAPI
{
	GENERATED_BODY()

protected:
	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void CharacterCustomGetCall();
	void CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomGetCallBack(FCharacterCustomGet ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomGetCallBack();


	UFUNCTION(BlueprintCallable)
	void CharacterCustomUpdateCall(TArray<int32> CustomList);
	void CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomUpdateCallBack(bool hasData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailCharacterCustomUpdateCallBack();
};
