// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACTileAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FJsonTile
{
	GENERATED_USTRUCT_BODY()

public:
	FJsonTile() : CreateDate(FDateTime::Now()), Position(FVector(0)) {};

	FJsonTile(FVector position) : CreateDate(FDateTime::Now()), Position(position) {};

	UPROPERTY(BlueprintReadOnly)
	FDateTime CreateDate;

	UPROPERTY(BlueprintReadOnly)
	FVector Position;

};

USTRUCT(BlueprintType, Atomic)
struct FJsonZone
{
	GENERATED_USTRUCT_BODY()

public:
	FJsonZone() : CreateDate(FDateTime::Now()), OnwerID("Defualt") { };

	FJsonZone(FString token) : OnwerID(token) { };

	UPROPERTY(BlueprintReadOnly)
	FDateTime CreateDate;

	UPROPERTY(BlueprintReadOnly)
	FString OnwerID;

	UPROPERTY(BlueprintReadOnly)
	TArray<FJsonTile> TilesData;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACTileAPI : public UCACBaseAPI
{
	GENERATED_BODY()
public:
	UCACTileAPI();

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	class ACPCBasePlayerController* OwnerPlayerController;

	UFUNCTION(BlueprintCallable)
	void TilePostCall();

	virtual void OnSuccessAPI() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTileZoneDataUpdateComple();


};
