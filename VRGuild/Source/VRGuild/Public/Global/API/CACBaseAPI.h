// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CACBaseAPI.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACBaseAPI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACBaseAPI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bHttpWaitresponse = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "API")
	FString URL = "";

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatus;

	UPROPERTY(BlueprintReadOnly)
	FString HttpResult;


	template<typename T>
	void HttpPostCall(T sendData);

	void HttpPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintImplementableEvent)
	void HttpSuccessLogic();
};

