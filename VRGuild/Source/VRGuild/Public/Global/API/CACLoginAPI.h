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
	FJsonLogin() : Code("Empty"){};

	FJsonLogin(FString code) : Code(code) { };

	UPROPERTY(BlueprintReadOnly)
	FString Code;
};

USTRUCT(BlueprintType, Atomic)
struct FJsonGetLoginInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FJsonGetLoginInfo() {};
};


UENUM()
enum class ELoginApiTypes
{
	EpicLogin,
	EpicUserInfo,
	LocalUserInfo
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

	UFUNCTION(BlueprintCallable)
	void EpicLoginPostCall();

	UFUNCTION(BlueprintCallable)
	void EpicLoginInfoGetCall();

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnEpicLoginComple();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEpicGetLoginInfoComple();
};
