// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLCharacterCustom.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomCreate {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	TArray <int32> Status;
};

USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomInfo {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int32 characterId;
	UPROPERTY(BlueprintReadWrite)
	FString accountId;
	UPROPERTY(BlueprintReadWrite)
	TArray <int32> Status;
};


USTRUCT(BlueprintType, Atomic)
struct FCharacterCustomInfoData {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FCharacterCustomInfo data;
};
/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLCharacterCustom : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
