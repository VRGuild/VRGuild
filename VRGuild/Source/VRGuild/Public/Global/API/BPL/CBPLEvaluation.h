#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLEvaluation.generated.h"

// Evaluation Create Request Structure
USTRUCT(BlueprintType)
struct FEvaluationCreateRequest
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Evaluation|Request")
    int64 categoryId;
    UPROPERTY(BlueprintReadWrite, Category = "Evaluation|Request")
    FEvaluation evaluationInfo;
};

// Single Evaluation Response Structure
USTRUCT(BlueprintType)
struct FEvaluationResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FEvaluation data;
};

// Evaluation List Response Structure
USTRUCT(BlueprintType)
struct FEvaluationListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FEvaluation> data;
};

UCLASS()
class VRGUILD_API UCBPLEvaluation : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};