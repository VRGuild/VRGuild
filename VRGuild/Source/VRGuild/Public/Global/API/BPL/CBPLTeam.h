#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLTeam.generated.h"

// Team Response Structure for Single Team
USTRUCT(BlueprintType)
struct FTeamDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FTeamInfo data;
};

// Team Response Structure for Team List
USTRUCT(BlueprintType)
struct FTeamListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FTeamInfo> data;
};

UCLASS()
class VRGUILD_API UCBPLTeam : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};