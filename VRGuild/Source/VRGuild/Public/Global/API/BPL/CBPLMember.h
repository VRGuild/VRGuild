#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLMember.generated.h"

// Member Response Structure
USTRUCT(BlueprintType)
struct FMemberDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FMemberInfo data;
};

UCLASS()
class VRGUILD_API UCBPLMember : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};