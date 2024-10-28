// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLTeam.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FTeamInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FTeamInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FString teamName;

	UPROPERTY(BlueprintReadWrite)
	FString introduction;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> memberList;
};

USTRUCT(BlueprintType, Atomic)
struct FTeamDetailInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FTeamDetailInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	int32 teamId;

	UPROPERTY(BlueprintReadWrite)
	FString pmId;

	UPROPERTY(BlueprintReadWrite)
	FString teamName;

	UPROPERTY(BlueprintReadWrite)
	FString introduction;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> memberList;

	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;

	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
};

USTRUCT(BlueprintType, Atomic)
struct FTeamDetailInfoDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FTeamDetailInfoDataAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FTeamDetailInfoAPI data;
};

USTRUCT(BlueprintType, Atomic)
struct FTeamInfoDataArrayAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FTeamInfoDataArrayAPI() {};

	UPROPERTY(BlueprintReadWrite)
	TArray<FTeamDetailInfoAPI> data;
};
USTRUCT(BlueprintType, Atomic)
struct FTeamIdAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FTeamIdAPI() {};

	UPROPERTY(BlueprintReadWrite)
	int32 teamId;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> newMemberList;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLTeam : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};
