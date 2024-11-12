// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLFile.generated.h"



USTRUCT(BlueprintType)
struct FFileData
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    TArray<uint8> multipartFiles;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FString PathFile;
};


/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
