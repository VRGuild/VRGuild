// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLChannel.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FTileInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FTileInfo() {};

	UPROPERTY(BlueprintReadWrite)
	FVector position;

	UPROPERTY(BlueprintReadWrite)
	FString type;
};


USTRUCT(BlueprintType, Atomic)
struct FChannelnfoCreateAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FChannelnfoCreateAPI() {};

	UPROPERTY(BlueprintReadWrite)
	TArray<FTileInfo> positionTypes;
};

USTRUCT(BlueprintType, Atomic)
struct FChannelInfoUpdateAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FChannelInfoUpdateAPI() {};

	FString ChannelID;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTileInfo> positionTypes;
};

USTRUCT(BlueprintType, Atomic)
struct FChannelInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FChannelInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FString ChannelId;

	UPROPERTY(BlueprintReadWrite)
	FString OwnerId;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTileInfo> positionTypes;

	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;

	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
};

USTRUCT(BlueprintType, Atomic)
struct FChannelInfoDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FChannelInfoDataAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FChannelInfoAPI Data;
};

USTRUCT(BlueprintType, Atomic)
struct FChannelInfoDataListAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FChannelInfoDataListAPI() {};

	UPROPERTY(BlueprintReadWrite)
	TArray<FChannelInfoAPI> Data;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLChannel : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
