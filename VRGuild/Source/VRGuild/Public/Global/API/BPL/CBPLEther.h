#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLEther.generated.h"

// Single Ether Response Structure
USTRUCT(BlueprintType)
struct FEtherResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FEther data;
};

// Ether List Response Structure
USTRUCT(BlueprintType)
struct FEtherListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FEther> data;
};

// Ether Balance Response Structure (using FEther instead of FEtherBalance)
USTRUCT(BlueprintType)
struct FEtherBalanceResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FEther data;
};

UCLASS()
class VRGUILD_API UCBPLEther : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};