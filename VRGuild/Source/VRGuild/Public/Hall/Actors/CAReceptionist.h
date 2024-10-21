// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CAReceptionist.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API ACAReceptionist : public ACAInteractable
{
	GENERATED_BODY()

public:
	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;
};
