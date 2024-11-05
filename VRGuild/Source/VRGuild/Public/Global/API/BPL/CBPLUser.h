#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLUser.generated.h"

// User Member Info Structure (Combined user related info)
USTRUCT(BlueprintType)
struct FUserMemberInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    int32 userId;
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    FCharacterInfo characterInfo;
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    FDevInfo devInfo;
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    int32 experienceValue;
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    int32 businessId;
    UPROPERTY(BlueprintReadWrite, Category = "User|Member")
    FString nickname;
};

// Response Structures
USTRUCT(BlueprintType)
struct FUserInfoResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FUserInfo data;
};

USTRUCT(BlueprintType)
struct FUserMemberInfoResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FUserMemberInfo data;
};

UCLASS()
class VRGUILD_API UCBPLUser : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};