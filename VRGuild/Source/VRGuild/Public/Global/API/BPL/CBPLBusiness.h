#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLBusiness.generated.h"

// Business Response Structure
USTRUCT(BlueprintType)
struct FBusinessInfoResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FBusinessInfo data;
};

UCLASS()
class VRGUILD_API UCBPLBusiness : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};