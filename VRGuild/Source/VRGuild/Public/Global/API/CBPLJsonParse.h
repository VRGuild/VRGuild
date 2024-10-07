// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLJsonParse.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLJsonParse : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:	
	template <typename T>
	FString JsonStringfy(T someStruct);

	template <typename T>
	T JsonPerse(FString someString);
};
