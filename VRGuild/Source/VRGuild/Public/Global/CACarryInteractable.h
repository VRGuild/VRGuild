﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CACarryInteractable.generated.h"

/**
 * 
 */

UCLASS()
class VRGUILD_API ACACarryInteractable : public ACAInteractable
{
	GENERATED_BODY()
	
public:
	ACACarryInteractable();

	void Init(bool bEnabled_In);

	virtual bool IsActive() const override;
	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<UUserWidget> PosterWidgetToDisplayClass;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<ACACarryInteractable> SelfActor;

private:
	UPROPERTY(Replicated)
	bool bEnabled;
};
