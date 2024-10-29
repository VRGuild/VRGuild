// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CWCDisplayScroll.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWCDisplayScroll : public UWidgetComponent
{
	GENERATED_BODY()
protected:
	UCWCDisplayScroll();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
public:
	UFUNCTION(Server, Reliable)
	void ServerTest();
	UPROPERTY(ReplicatedUsing = OnRep_TestVar)
	TObjectPtr<AActor> TestVar;
	UFUNCTION()
	void OnRep_TestVar();
};
