// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CACCarry.generated.h"

class ACharacter;
class AActor;
class ACACarryInteractable;

class UCWScrollBase;

enum class ECarriedType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCarry : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCACCarry();

protected:
	virtual void InitializeComponent() override;

public:	
	UFUNCTION(BlueprintCallable)
	void StartCarry(ACACarryInteractable* ActorToHold);
	UFUNCTION(BlueprintCallable)
	void StartDrop(bool bDoServerRPC = true);

	UFUNCTION(BlueprintCallable)
	void HideCarryWidget();
	UFUNCTION(BlueprintCallable)
	void UnHideCarryWidget();

	FGameplayTagContainer GetGameplayTagContainer() const;

	FString GetMessageForNPC();

	ECarriedType GetCarryType() const;

	UFUNCTION(BlueprintCallable)
	ACACarryInteractable* GetCarriedActor() const;
private:
	TObjectPtr<ACharacter> Owner;
	UPROPERTY()
	TObjectPtr<UCWScrollBase> ScrollBaseWidget;

	UPROPERTY(EditDefaultsOnly, Category = Settings, meta = (AllowPrivateAccess))
	TSubclassOf<UCWScrollBase> ScrollBaseWidgetClass;
	
	UPROPERTY(ReplicatedUsing = OnRep_ActorInHand)
	TObjectPtr<ACACarryInteractable> ActorInHand;

	UFUNCTION()
	void OnRep_ActorInHand();
	
	UFUNCTION(Server, Reliable)
	void ServerHold(ACACarryInteractable* actorToHold);
	bool bProcessingHold;
	UFUNCTION(Server, Reliable)
	void ServerDrop();
};
