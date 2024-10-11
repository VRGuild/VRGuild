// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CABaseAPI.generated.h"

USTRUCT(BlueprintType)
struct FJsonPlayer
{
	GENERATED_USTRUCT_BODY()

	FJsonPlayer() : username("name"), password("UnKnown") {};

	FJsonPlayer(FString name, FString password) : username(name), password(password) { };

	UPROPERTY()
	FString username;

	UPROPERTY()
	FString password;
};

UCLASS()
class VRGUILD_API ACABaseAPI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACABaseAPI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bHttpWaitResponse = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "API")
	FString URL = "";

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatus;

	UPROPERTY(BlueprintReadOnly)
	FString HttpResult;
	
	template <typename T>
	void HttpPostCall(T sendData);

	void HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintImplementableEvent)
	void HttpSuccessLogic();
};
