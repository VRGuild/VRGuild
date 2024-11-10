#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLBase.generated.h"

// Base response structure
USTRUCT(BlueprintType)
struct FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Base|Response")
    FString status;
    UPROPERTY(BlueprintReadWrite, Category = "Base|Response")
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

// Evaluation Structure
USTRUCT(BlueprintType)
struct FEvaluation
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Skill|Evaluation")
    int64 evaluationId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Skill|Evaluation")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Skill|Evaluation")
    FString cause;
    UPROPERTY(BlueprintReadWrite, Category = "Skill|Evaluation")
    int32 point;
    UPROPERTY(BlueprintReadWrite, Category = "Skill|Evaluation")
    FDateTime createAt;
};

// Skill Category Info Structure
USTRUCT(BlueprintType)
struct FSkillCategoryInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Skill")
    int64 categoryInfoId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Skill")
    FString categoryName;
    UPROPERTY(BlueprintReadWrite, Category = "Skill")
    bool bIsEvaluated;
    UPROPERTY(BlueprintReadWrite, Category = "Skill")
    int64 pointAvg;
    UPROPERTY(BlueprintReadWrite, Category = "Skill")
    TArray<int64> evaluationIdList;
};

// Developer Info Structure
USTRUCT(BlueprintType)
struct FDevInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    int64 devId = 0;
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

// Business Info Structure
USTRUCT(BlueprintType)
struct FBusinessInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Business")
    int64 businessId = 0;
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

// Guild Info Structure
USTRUCT(BlueprintType)
struct FGuildInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    int64 guildId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    FString guildName;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    FString guildIntroduction;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    int64 masterUserId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Guild")
    TArray<int64> guildMemberList;
};

// Team Structure
USTRUCT(BlueprintType)
struct FTeamInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Team")
    int64 teamId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Team")
    FString teamIntroduction;
    UPROPERTY(BlueprintReadWrite, Category = "Team")
    int64 leaderUserId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Team")
    TArray<int64> teamMemberList;
};

// Member Structure
USTRUCT(BlueprintType)
struct FMemberInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    int64 memberId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    FString type;
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    int64 assigneesId= 0;
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    FString motive;
    UPROPERTY(BlueprintReadWrite, Category = "Member")
    int32 isAccepted;
};

// Character Structure
USTRUCT(BlueprintType)
struct FCharacterInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 characterId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    int64 guildId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    TArray<int64> teamIdList;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    TArray<FCustomInfo> customList;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FString characterPicture;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Character")
    FDateTime modifiedAt;
};

// Occupation Structure
USTRUCT(BlueprintType)
struct FOccupation
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FString occupationName;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    int32 occupationCount;
};

// Comment Structure
USTRUCT(BlueprintType)
struct FComment
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project|Comment")
    int64 commentId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Comment")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Comment")
    FString content;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Comment")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Comment")
    FDateTime modifiedAt;
};

// Project Structure
USTRUCT(BlueprintType)
struct FProjectInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    int64 projectId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FString title;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FString content;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    int32 estimatedCost;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FString progressClassification;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FString workType;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    TArray<FOccupation> requiredOccupationList;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    TArray<int64> commentList;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FDateTime startDate;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FDateTime endDate;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FDateTime createAt;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FDateTime modifiedAt;
};

// Support Structure
USTRUCT(BlueprintType)
struct FSupportInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Support")
    int64 supportId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Support")
    int64 teamId;
    UPROPERTY(BlueprintReadWrite, Category = "Support")
    int64 projectId;
};

// Experience Structure
USTRUCT(BlueprintType)
struct FExperience
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "User|Experience")
    int64 expId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User|Experience")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User|Experience")
    FString cause;
    UPROPERTY(BlueprintReadWrite, Category = "User|Experience")
    int32 amount;
    UPROPERTY(BlueprintReadWrite, Category = "User|Experience")
    FDateTime createTime;
};

// Ether Structure
USTRUCT(BlueprintType)
struct FEther
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    int64 etherId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    FString cause;
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    int32 goldAmount;
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    int32 silverAmount;
    UPROPERTY(BlueprintReadWrite, Category = "User|Ether")
    FDateTime createAt;
};

// User Structure
USTRUCT(BlueprintType)
struct FUserInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int32 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FString epicAccountID;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    FString steamAccountID;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 characterId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 devId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "User")
    int64 businessId = 0;
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

UCLASS()
class VRGUILD_API UCBPLBase : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};