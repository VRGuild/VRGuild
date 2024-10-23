// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CAReceptionist.generated.h"

/**
 * 
 */

class UInputMappingContext;

UCLASS()
class VRGUILD_API ACAReceptionist : public ACAInteractable
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayCommossionPopup(bool bDisplay);
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayDefaultPopup(bool bDisplay);
private:
	UPROPERTY(EditDefaultsOnly, Category = Settings, meta=(AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> DefaultInputContext;
	UPROPERTY(EditDefaultsOnly, Category = Settings, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> ScrollInputContext;
};
