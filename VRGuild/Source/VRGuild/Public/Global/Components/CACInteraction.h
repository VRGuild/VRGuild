﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACInteraction.generated.h"


class APlayerController;
class ACharacter;
class ICIInteractionInterface;
class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool CanInteract() const;
	UFUNCTION(BlueprintCallable)
	void Enable();
	UFUNCTION(BlueprintCallable)
	void Disable();
	UFUNCTION(BlueprintCallable)
	void BeginInteract();
	UFUNCTION(BlueprintCallable)
	void EndInteract();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractRadius;
	const AActor* GetActorOnFocus() const;

private:
	void BeginTrace();
	void EndTrace();
	void UpdateTrace();
	ICIInteractionInterface* GetInterface() const;
	TObjectPtr<ACharacter> Owner;
	AActor* InteractingActor;
	AActor* ActorOnFocus;

	bool bCanInteract;
	bool bIsTracing;
	bool bEnabled;
};
