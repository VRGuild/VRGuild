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
    int64 userId;
    UPROPERTY(BlueprintReadWrite, Category = "Project|User")
    FBusinessInfo businessInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Project|User")
    FString nickname;
};

// Project with Support Teams Structure
USTRUCT(BlueprintType)
struct FProjectWithSupport
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FProjectInfo projectInfo;

    UPROPERTY(BlueprintReadWrite, Category = "Project")
    TArray<int64> supportTeamIdList;
};

// Paged Project List Response Structure
USTRUCT(BlueprintType)
struct FProjectPagedResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FProjectWithSupport> data;
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    int32 totalPages;
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    int32 totalProjectCnt;
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

USTRUCT(BlueprintType)
struct FProjectWithDetail
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FProjectInfo projectInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FProjectUserInfo userInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    TArray<int64> supportTeamIdList;
};

USTRUCT(BlueprintType)
struct FProjectWithDetailData
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project")
    FProjectWithDetail data;
};

USTRUCT(BlueprintType)
struct FProjectDetailPagedResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FProjectWithDetail> data;
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    int32 totalPages;
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    int32 totalProjectCnt;
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
struct FProjectTeamApply
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Project|Team")
    FString teamIntroduction;
    UPROPERTY(BlueprintReadWrite, Category = "Project|Team")
    int64 leaderUserId;
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