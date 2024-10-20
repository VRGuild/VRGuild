// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACEtherAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FJsonEther
{
	GENERATED_USTRUCT_BODY()

public:
	FJsonEther() : Amount(0), Reason("") {};

	FJsonEther(int32 amount ,FString reason) : Amount(amount), Reason(reason) { };

	UPROPERTY(BlueprintReadOnly)
	int32 Amount;

	UPROPERTY(BlueprintReadOnly)
	FString Reason;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACEtherAPI : public UCACBaseAPI
{
	GENERATED_BODY()
public:
	UCACEtherAPI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	class ACPCBasePlayerController* OwnerPlayerController;

	UFUNCTION(BlueprintCallable)
	void EtherPostCall();

	UFUNCTION(BlueprintImplementableEvent)

	void OnEtherComple();

};
