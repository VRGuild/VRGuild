// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "CAInteractable.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool CanInteract() const override;
	virtual void BeginTrace() override;
	virtual void EndTrace() override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

private:
	bool bCanInteract;
};
