// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLBase.h"
#include "CBPLTile.generated.h"



// Comment Response Structure
USTRUCT(BlueprintType)
struct FTileInfoList
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FTileObjectInfo> objectInfoList;
};


// Comment Response Structure
USTRUCT(BlueprintType)
struct FTileMemoInfoList
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FTileMemoInfo> memoList;
};

// Comment Response Structure
USTRUCT(BlueprintType)
struct FTilePdfInfoList
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FString> pdfUrlList;
};


/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLTile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
