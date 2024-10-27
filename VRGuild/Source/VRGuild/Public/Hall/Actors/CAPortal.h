// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CAPortal.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API ACAPortal : public ACAInteractable
{
	GENERATED_BODY()

public:
	ACAPortal();

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	virtual void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartDisplay();
private:
	bool bOverlapped;
};
