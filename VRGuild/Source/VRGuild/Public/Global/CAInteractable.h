// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "GameplayTagContainer.h"
#include "CAInteractable.generated.h"

class UCGIGameInstance;
class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class VRGUILD_API ACAInteractable : public AActor, public ICIInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ACAInteractable();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual FString GetTraceMessage(ACharacter* Initiator) const;
	
public:
	FGameplayTagContainer GetGameplayTagContainer() const;

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

	virtual void OnRep_Owner() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings|Tags")
	FGameplayTagContainer InteractionTag;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Components")
	TObjectPtr<UBoxComponent> BoxOverlap;
	UPROPERTY(EditDefaultsOnly, Category = "Settings|Components")
	TObjectPtr<USceneComponent> RootComp; 
	UPROPERTY(EditDefaultsOnly, Category = "Settings|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UFUNCTION()
	virtual void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetHideMesh(bool bHide);
	
	UFUNCTION(BlueprintImplementableEvent)
	void TraceBegin();
	UFUNCTION(BlueprintImplementableEvent)
	void TraceEnd();

private:

	TObjectPtr<UCGIGameInstance> GameInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	bool bHideMesh;
};
