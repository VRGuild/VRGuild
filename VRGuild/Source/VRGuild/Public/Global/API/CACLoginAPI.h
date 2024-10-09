// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACLoginAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FJsonLogin
{
	GENERATED_USTRUCT_BODY()
public:
	FJsonLogin() : Token("Empty"){};

	FJsonLogin(FString token) : Token(token) { };

	UPROPERTY(BlueprintReadOnly)
	FString Token;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACLoginAPI : public UCACBaseAPI
{
	GENERATED_BODY()
public:
	UCACLoginAPI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	class ACPCBasePlayerController* OwnerPlayerController;
public:
	UFUNCTION(BlueprintCallable)
	void LoginPostAPI();

	void LoginPostAPICallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintImplementableEvent)
	void OnLoginAPISuccess(FJsonLogin resultData);

	FString JsonStringfy(FJsonLogin someStruct);
	FJsonLogin JsonPerse(FString someString);
};
