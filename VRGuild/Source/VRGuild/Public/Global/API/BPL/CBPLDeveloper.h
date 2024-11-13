#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLDeveloper.generated.h"

// Developer Create/Update Request Structure
USTRUCT(BlueprintType)
struct FDeveloperRequest
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FString nickname;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FDevInfo devInfo;
};

// Response Structure
USTRUCT(BlueprintType)
struct FDeveloperResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FDevInfo data;
};

// Response Structure
USTRUCT(BlueprintType)
struct FDeveloperListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FDevInfo> data;
};

UCLASS()
class VRGUILD_API UCBPLDeveloper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};