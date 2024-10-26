// Fill out your copyright notice in the Description page of Project Settings.

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

	friend class ACAInteractable;

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
	void Enable();
	UFUNCTION(BlueprintCallable)
	void Disable();

	UFUNCTION(BlueprintCallable)
	bool IsEnabled();

	UFUNCTION(BlueprintCallable)
	void Interact();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractRadius;
	
	UFUNCTION(BlueprintCallable)
	void BeginInteract();
	UFUNCTION(BlueprintCallable)
	void EndInteract();

private:
	void UpdateActorsOverlapped(AActor* actoroverlapped, bool bAdd);

	void BeginTrace();
	void EndTrace();

	void UpdateTrace(AActor*& actorTraced);

	ICIInteractionInterface* GetInterface(AActor* actor) const;
	TObjectPtr<ACharacter> Owner;
	
	AActor* ActorOnFocus;

	bool bIsTracing;
	bool bEnabled;
	bool bFullEnable;
	UPROPERTY()
	TSet<AActor*> ActorsOverlapped;
};
