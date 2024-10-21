// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACCharacterCustomAPI.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomCreateAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FCharacterCustomCreateAPI() {};
	FCharacterCustomCreateAPI(TArray <int32> status) : Status(status) {};

	TArray <int32> Status;
};

USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomGetAPI
{
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
class VRGUILD_API UCACCharacterCustomAPI : public UCACBaseAPI
{
	GENERATED_BODY()
	
public:
	UCACCharacterCustomAPI();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void CharacterCustomGetCall();

	UFUNCTION(BlueprintCallable)
	void CharacterCustomUpdateCall(TArray<int32> CustomList);

	void CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);

	void CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomGetCallBack(FCharacterCustomGetAPI ParseData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterCustomUpdateCallBack(bool hasData);
};
