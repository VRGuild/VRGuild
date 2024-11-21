// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLBase.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_TileTools.generated.h"


UENUM(BlueprintType)
enum class ESpaceType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Floor = 1 UMETA(DisplayName = "Floor"),
	Cube = 2 UMETA(DisplayName = "Cube"),
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


    UFUNCTION(BlueprintCallable, Category = "Tile System")
    static AActor* SpawnTileObject(UWorld* World, const FTileObjectInfo& ObjectInfo);

    // 여러 오브젝트 스폰
    UFUNCTION(BlueprintCallable, Category = "Tile System")
    static TArray<AActor*> SpawnTileObjects(UWorld* World, const TArray<FTileObjectInfo>& ObjectInfoList);

    // FTileObjectInfo 생성 헬퍼
    UFUNCTION(BlueprintCallable, Category = "Tile System")
    static FTileObjectInfo CreateTileObjectInfo(AActor* Actor);
};
