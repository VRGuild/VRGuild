// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_TileTools.generated.h"


UENUM(BlueprintType)
enum class ESpaceType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Floor = 1 UMETA(DisplayName = "Floor"),
	Wall = 2 UMETA(DisplayName = "Wall"),
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UFL_TileTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FVector SnapGridVector(FVector vector, float gridSize);
};
