#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLUser.generated.h"

// Common response structure
USTRUCT(BlueprintType)
struct FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FString status;
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FString message;
};

// Custom Info Structure
USTRUCT(BlueprintType)
struct FCustomInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Character|Custom")
    int32 customType;
    UPROPERTY(BlueprintReadWrite, Category = "Character|Custom")
    FString customName;
    UPROPERTY(BlueprintReadWrite, Category = "Character|Custom")
    FString customTexture;
    UPROPERTY(BlueprintReadWrite, Category = "Character|Custom")
    int32 customIndex;
};

// Guild Structure
USTRUCT(BlueprintType)
struct FGuildInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    int64 guildId;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    FString guildName;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    FString guildIntroduction;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    int64 masterUserId;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    TArray<int64> guildMemberList;
};

// Character Structure
USTRUCT(BlueprintType)
struct FCharacterInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 characterId;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 userId;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 guildId;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    TArray<int64> teamIdList;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    TArray<FCustomInfo> customList;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FString characterPicture;  // base64 string
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FDateTime modifiedAt;
};

// Skill Category Structure
USTRUCT(BlueprintType)
struct FSkillCategoryInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Skills")
    int64 categoryInfoId;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Skills")
    FString categoryName;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Skills")
    bool bIsEvaluated;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Skills")
    int64 pointAvg;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Skills")
    TArray<int64> evaluationIdList;
};

// Developer Info Structure
USTRUCT(BlueprintType)
struct FDevInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    int64 devId;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devName;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devEmail;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devPhone;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString githubLink;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> portfolioUrlList;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString career;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FSkillCategoryInfo> skillCategoryList;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> tag;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString hope;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FDateTime modifiedAt;
};

// Business Structure
USTRUCT(BlueprintType)
struct FBusinessInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    int64 businessId;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FString businessName;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FString businessLogoURL;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FString managerName;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FString managerPhone;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    FDateTime modifiedAt;
};

// Basic User Info Structure
USTRUCT(BlueprintType)
struct FUserInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int32 userId;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FString epicAccountID;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FString steamAccountID;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 characterId;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 devId;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 businessId;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    TArray<int64> channelList;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int32 experienceValue;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    TArray<int64> experienceList;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FString nickname;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FDateTime modifiedAt;
};

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