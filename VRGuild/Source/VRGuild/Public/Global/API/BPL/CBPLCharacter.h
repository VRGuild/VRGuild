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

UCLASS(meta = (ScriptName = "CBPLCharacter"))
class VRGUILD_API UCBPLCharacter : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Character")
    static FCharacterInfo SetCharacterCustom(FCharacterInfo target, TArray<FCustomInfo> CustomInfoList);

    UFUNCTION(BlueprintCallable, Category = "Character")
    static FCharacterInfo SetCharacterPicture(FCharacterInfo target, TArray<FLinearColor> CustomCharacterPicture);

};