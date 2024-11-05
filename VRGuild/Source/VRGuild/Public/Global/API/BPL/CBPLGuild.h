#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLGuild.generated.h"

// Guild Response Structure
USTRUCT(BlueprintType)
struct FGuildDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FGuildInfo data;
};

UCLASS()
class VRGUILD_API UCBPLGuild : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};