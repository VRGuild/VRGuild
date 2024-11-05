#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLCharacter.generated.h"

// Character Response Structure
USTRUCT(BlueprintType)
struct FCharacterDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FCharacterInfo data;
};

UCLASS()
class VRGUILD_API UCBPLCharacter : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};