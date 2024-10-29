// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "CWCDisplayScroll.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWCDisplayScroll : public UWidgetComponent, public ICIInteractionInterface
{
	GENERATED_BODY()
protected:
	UCWCDisplayScroll();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;


public:
	void Set(AActor* actorTest);

	UFUNCTION(Server, Reliable)
	void ServerTest();
	UPROPERTY(ReplicatedUsing = OnRep_TestVar)
	TObjectPtr<AActor> TestVar;
	UFUNCTION()
	void OnRep_TestVar();
};
