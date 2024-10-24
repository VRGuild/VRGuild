// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CADisplayer.generated.h"

/**
 * 
 */

class ACACarryInteractable;
class UWidgetComponent;

UCLASS()
class VRGUILD_API ACADisplayer : public ACAInteractable
{
	GENERATED_BODY()
public:
	ACADisplayer();

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;
	virtual bool IsInteracting(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Owner() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Settings)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UFUNCTION(Server, Reliable)
	void ServerDisplayCommission(AActor* commissionPassed);
	
	UFUNCTION(Server, Reliable)
	void ServerPickupCommission(ACharacter* player);

private:
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	FString ErrorMessage;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FString DisplayMessage;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FString PickupMessage;

	UPROPERTY(ReplicatedUsing = OnRep_ActorDisplayed)
	TObjectPtr<ACACarryInteractable> ActorDisplayed;
	UFUNCTION()
	void OnRep_ActorDisplayed();
};
