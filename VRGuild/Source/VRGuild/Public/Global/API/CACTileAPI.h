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
	FJsonTile() : Position(FVector(0)) {};

	FJsonTile(FVector position) :  Position(position) {};

	UPROPERTY(BlueprintReadOnly)
	FVector Position;

	UPROPERTY(BlueprintReadOnly)
	int64  type;
};

USTRUCT(BlueprintType, Atomic)
struct FJsonZone
{
	GENERATED_USTRUCT_BODY()

public:
	FJsonZone() { };

	FJsonZone(FString ownerId) { };

	UPROPERTY(BlueprintReadOnly)
	TArray<FJsonTile> TilesData;
};


USTRUCT(BlueprintType, Atomic)
struct FJsonZoneRespone
{
	GENERATED_USTRUCT_BODY()

public:
	FJsonZoneRespone() : CreateDate(FDateTime::Now()), OnwerID("Defualt") { };

	FJsonZoneRespone(FString token) : OnwerID(token) { };

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

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTileZoneDataUpdateComple();


};


