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
	void BeginInteract();
	UFUNCTION(BlueprintCallable)
	void EndInteract();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float InteractRadius;
	
private:
	void BeginTrace();
	void EndTrace();

	void UpdateTrace(AActor*& actorTraced);
	
	bool CanInteract(AActor* actor) const;

	ICIInteractionInterface* GetInterface(AActor* actor) const;
	TObjectPtr<ACharacter> Owner;
	
	AActor* InteractingActor;
	
	AActor* ActorOnFocus;

	bool bCanInteract;
	bool bIsTracing;
	bool bEnabled;
};
