// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "GameplayTagContainer.h"
#include "CAInteractable.generated.h"

class UCGIGameInstance;

UCLASS()
class VRGUILD_API ACAInteractable : public AActor, public ICIInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTraceMessage(FString newMsg);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings | Tags")
	FGameplayTagContainer InteractionTag;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FString TraceMessage;
	TObjectPtr<UCGIGameInstance> GameInstance;
};
