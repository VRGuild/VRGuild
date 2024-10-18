// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACCharacterCustomAPI.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FCharacterCustomDataAPI() {};
	UPROPERTY(BlueprintReadOnly)
	TArray<int> status;
};

USTRUCT(BlueprintType, Atomic)
struct FCharacterInfoGetDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FCharacterInfoGetDataAPI() : UserID("none") {};

	FCharacterInfoGetDataAPI(FString userId) : UserID(userId) {};

	UPROPERTY(BlueprintReadOnly)
	FString UserID;
};


/**
 * 
 */
UCLASS()
class VRGUILD_API UCACCharacterCustomAPI : public UCACBaseAPI
{
	GENERATED_BODY()
	
public:
	UCACCharacterCustomAPI();


	UFUNCTION(BlueprintCallable)
	void CharacterCustomStatusPostCall();
	void CharacterCustomStatusGetCall();

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	void OnGetCustomCharacterData(FHttpRequestPtr req, FHttpResponsePtr res);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnGetCusomCFharacterDataCallBack();
};
