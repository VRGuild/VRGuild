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
	ACAInteractable();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetTraceMessage(FString newMsg);
	FString GetTraceMessage() const;

public:
	FGameplayTagContainer GetGameplayTagContainer() const;

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;
	virtual bool IsInteracting(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

	virtual void OnRep_Owner() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings|Tags")
	FGameplayTagContainer InteractionTag;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FString TraceMessage;
	TObjectPtr<UCGIGameInstance> GameInstance;
	bool bIsInteracting;
};
