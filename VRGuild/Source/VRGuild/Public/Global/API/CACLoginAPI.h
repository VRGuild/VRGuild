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
	void LoginPostCall();

	virtual void OnSuccessAPI() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnLoginComple();
};
