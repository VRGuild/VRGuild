// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "CWBaseWorld.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWBaseWorld : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHoverAnim();
};
