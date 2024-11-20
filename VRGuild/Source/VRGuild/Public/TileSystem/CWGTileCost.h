// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGEtherAPI.h"
#include "CWGTileCost.generated.h"

enum class ESpaceType : uint8;

UENUM(BlueprintType)
enum class ETileCostType : uint8
{
	Buy = 0 UMETA(DisplayName = "Buy"),
	Sell = 1 UMETA(DisplayName = "Sell"),
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGTileCost : public UCWGEtherAPI
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInit();
};
