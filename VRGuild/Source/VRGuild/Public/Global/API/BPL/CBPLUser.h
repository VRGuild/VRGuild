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
    UPROPERTY(BlueprintReadWrite, Category = "API")
    int32 UserId;

    UPROPERTY(BlueprintReadWrite, Category = "API")
    FCharacterInfo CharacterInfo;

    UPROPERTY(BlueprintReadWrite, Category = "API")
    FDevInfo DevInfoDTO;

    UPROPERTY(BlueprintReadWrite, Category = "API")
    int32 ExperienceValue;

    UPROPERTY(BlueprintReadWrite, Category = "API")
    int32 BusinessId;

    UPROPERTY(BlueprintReadWrite, Category = "API")
    FString Nickname;
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