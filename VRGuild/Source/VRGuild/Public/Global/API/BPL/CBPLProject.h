#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLProject.generated.h"

// Project User Info Structure
USTRUCT(BlueprintType)
struct FProjectUserInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project|User")
    FBusinessInfo businessInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Project|User")
    FString nickname;
};

// Project Detail Structure
USTRUCT(BlueprintType)
struct FProjectDetailInfo : public FProjectInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project|Detail")
    FProjectUserInfo userInfo;
};

// Project List Response Structure
USTRUCT(BlueprintType)
struct FProjectListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FProjectDetailInfo> data;
};

// Project Detail Response Structure
USTRUCT(BlueprintType)
struct FProjectDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FProjectDetailInfo data;
};

// Project Response Structure
USTRUCT(BlueprintType)
struct FProjectResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FProjectInfo data;
};

// Project Team List Structure
USTRUCT(BlueprintType)
struct FProjectTeamList
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project|Team")
    int64 projectId;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Team")
    TArray<int64> teamIdList;
};

// Project Team List Response Structure
USTRUCT(BlueprintType)
struct FProjectTeamListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FProjectTeamList data;
};

UCLASS()
class VRGUILD_API UCBPLProject : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};