// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
class VRGUILD_API UCWGTileCost : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly);
	class ACATileZone* TargetTileZone;

	UPROPERTY(BlueprintReadOnly);
	ETileCostType TileConstType;

	UPROPERTY(BlueprintReadOnly);
	FVector Position;

	UPROPERTY(BlueprintReadOnly);
	ESpaceType SpaceType;

	UPROPERTY(BlueprintReadOnly);
	int32 Cost;


	void InitializeSetting(ACATileZone* targetZone, ETileCostType tileConstType, FVector position, ESpaceType spaceType, int32 cost);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInit();
};
