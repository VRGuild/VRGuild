// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLRegister.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FProficiency
{
	GENERATED_USTRUCT_BODY()
public:
	FProficiency() {};

	UPROPERTY(BlueprintReadWrite)
	FString Catagoly;

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	int32 Index;
};

USTRUCT(BlueprintType, Atomic)
struct FResgisterCreateAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FResgisterCreateAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FString purpose;

	UPROPERTY(BlueprintReadWrite)
	FString nickname;

	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	FString email;

	UPROPERTY(BlueprintReadWrite)
	FString phone;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> portfolioList;

	UPROPERTY(BlueprintReadWrite)
	FString experience;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProficiency> skillSet;

	UPROPERTY(BlueprintReadWrite)
	FString message;
};


USTRUCT(BlueprintType, Atomic)
struct FResgisterInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FResgisterInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	int userId;

	UPROPERTY(BlueprintReadWrite)
	FString accountId;

	UPROPERTY(BlueprintReadWrite)
	FString purpose;

	UPROPERTY(BlueprintReadWrite)
	int characterId;

	UPROPERTY(BlueprintReadWrite)
	FDateTime createdAt;

	UPROPERTY(BlueprintReadWrite)
	FDateTime modifiedAt;

	UPROPERTY(BlueprintReadWrite)
	FString nickname;

	UPROPERTY(BlueprintReadWrite)
	FString name;

	UPROPERTY(BlueprintReadWrite)
	FString email;

	UPROPERTY(BlueprintReadWrite)
	FString phone;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> portfolioList;

	UPROPERTY(BlueprintReadWrite)
	FString experience;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProficiency> skillSet;

	UPROPERTY(BlueprintReadWrite)
	FString message;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLRegister : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
