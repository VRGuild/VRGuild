// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCarry.generated.h"

class ACharacter;
class AActor;

class UCWScrollBase;

UENUM(Blueprintable)
enum class ECarriedType : uint8
{
	COMMISSION UMETA(DisplayName = "Commission"),
	REGISTRATION UMETA(DisplayName = "Registration"),
	NONE UMETA(DisplayName = "None")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCarry : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCACCarry();

protected:
	virtual void InitializeComponent() override;

public:	
	void StartCarry(ECarriedType Type, TSubclassOf<AActor> ActorToHold, TSubclassOf<UUserWidget> WidgetToDisplay);

	FString GetMessageForNPC();
private:
	TObjectPtr<ACharacter> Owner;
	TObjectPtr<UCWScrollBase> ScrollBaseWidget;

	UPROPERTY(EditDefaultsOnly, Category = Settings, meta = (AllowPrivateAccess))
	TSubclassOf<UCWScrollBase> ScrollBaseWidgetClass;
	
	UPROPERTY(ReplicatedUsing = OnRep_ActorInHand)
	TObjectPtr<AActor> ActorInHand;
	
	ECarriedType CarryType;
	ECarriedType CarryTypeTemp;

	UFUNCTION()
	void OnRep_ActorInHand();
	
	UFUNCTION(Server, Reliable)
	void ServerHoldPoster(TSubclassOf<AActor> ActorToHold);
};
