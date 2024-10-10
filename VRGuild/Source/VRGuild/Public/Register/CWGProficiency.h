// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWGProficiency.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FProficiency
{
	GENERATED_USTRUCT_BODY()
public:
	FProficiency() : Name("Empty"), Index(0) {};

	FProficiency(FString name, int32 index) : Name(name), Index(index) { };

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	int32 Index;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGProficiency : public UUserWidget
{
	GENERATED_BODY()
	
};
