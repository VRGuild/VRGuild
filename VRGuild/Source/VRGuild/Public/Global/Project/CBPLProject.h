// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLProject.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FProjectInitator
{
	GENERATED_USTRUCT_BODY()

public:
	FProjectInitator() {};

	UPROPERTY(BlueprintReadWrite)
	int32 InitiatorId;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> ProjectNoticeId;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* CompanyImage;
	UPROPERTY(BlueprintReadWrite)
	FString CompanyName;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectEmplyee
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectEmplyee() {};

	UPROPERTY(BlueprintReadWrite)
	FString EmployeeName;

	UPROPERTY(BlueprintReadWrite)
	int32 Number;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectNotice
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectNotice() {};

	UPROPERTY(BlueprintReadWrite)
	int32 ProjectNoticeId;
	UPROPERTY(BlueprintReadWrite)
	int32 ProjectDetailId;
	UPROPERTY(BlueprintReadWrite)
	FProjectInitator InitiatorId;
	UPROPERTY(BlueprintReadWrite)
	FVector Postision;
	UPROPERTY(BlueprintReadWrite)
	FString ProjectTitle;
	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectEmplyee> ProjectEmployees;
	UPROPERTY(BlueprintReadWrite)
	int32 ProjectPrice;
	UPROPERTY(BlueprintReadWrite)
	FDateTime ProjectCreateDate;
	UPROPERTY(BlueprintReadWrite)
	FDateTime ProjectEndDate;
};



USTRUCT(BlueprintType, Atomic)
struct FProjectDetail
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectDetail() {};

	UPROPERTY(BlueprintReadWrite)
	int32 ProjectDetailId;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> TeamId;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> CommentID;
	UPROPERTY(BlueprintReadWrite)
	FString ProjectDetailNote;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectComment
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectComment() {};

	UPROPERTY(BlueprintReadWrite)
	int32 CommentID;
	UPROPERTY(BlueprintReadWrite)
	FString UserID;
	UPROPERTY(BlueprintReadWrite)
	FString Comment;
	UPROPERTY(BlueprintReadWrite)
	FDateTime CreateDate;
	UPROPERTY(BlueprintReadWrite)
	FDateTime UpdateDate;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectTeam
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectTeam() {};

	UPROPERTY(BlueprintReadWrite)
	int32 TeamId;
	UPROPERTY(BlueprintReadWrite)
	int32 CaptainID;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> CrewID;
	UPROPERTY(BlueprintReadWrite)
	FDateTime CreateDate;
	UPROPERTY(BlueprintReadWrite)
	FDateTime UpdateDate;
};
//////
// 임시
//////


USTRUCT(BlueprintType, Atomic)
struct FCommentAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FCommentAPI() {};

	UPROPERTY(BlueprintReadOnly)
	int32 commentId;
	UPROPERTY(BlueprintReadOnly)
	FString content;
	UPROPERTY(BlueprintReadOnly)
	FString accountId;
	UPROPERTY(BlueprintReadOnly)
	FDateTime createdAt;
	UPROPERTY(BlueprintReadOnly)
	FDateTime modifiedAt;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectAPI() {};
	UPROPERTY(BlueprintReadWrite)
	int32		projectId;
	UPROPERTY(BlueprintReadWrite)
	FString		workScope;
	UPROPERTY(BlueprintReadWrite)
	FString		workType;
	UPROPERTY(BlueprintReadWrite)
	FString		progressClassification;
	UPROPERTY(BlueprintReadWrite)
	FString		companyName;
	UPROPERTY(BlueprintReadWrite)
	FString		title;
	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredClient;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredServer;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredDesign;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredPlanner;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredAIEngineer;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	startDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	endDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	estimatedCost;
};


USTRUCT(BlueprintType, Atomic)
struct FProjectInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	int32 projectId;
	UPROPERTY(BlueprintReadWrite)
	FString		workScope;
	UPROPERTY(BlueprintReadWrite)
	FString		workType;
	UPROPERTY(BlueprintReadWrite)
	FString		progressClassification;
	UPROPERTY(BlueprintReadWrite)
	FString		companyName;
	UPROPERTY(BlueprintReadWrite)
	FString		title;
	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredClient;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredServer;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredDesign;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredPlanner;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredAIEngineer;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	startDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	endDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	estimatedCost;

	UPROPERTY(BlueprintReadWrite)
	FString		accountId;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
	UPROPERTY(BlueprintReadWrite)
	FVector		projectVector;

	UPROPERTY(BlueprintReadWrite)
	TArray<FCommentAPI>	comments;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectAllAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectAllAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FString		Title;
	UPROPERTY(BlueprintReadWrite)
	FString		accountId;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredClient;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredServer;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredDesign;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredPlanner;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredAIEngineer;
	UPROPERTY(BlueprintReadWrite)
	FString		progressClassification;
	UPROPERTY(BlueprintReadWrite)
	FString		workScope;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	startDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	endDateTime;
	UPROPERTY(BlueprintReadWrite)
	FString		companyName;
	UPROPERTY(BlueprintReadWrite)
	int32		estimatedCost;
	UPROPERTY(BlueprintReadWrite)
	FString		workType;
	UPROPERTY(BlueprintReadWrite)
	FVector		projectVector;
	UPROPERTY(BlueprintReadWrite)
	int32		projectId;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
};



USTRUCT(BlueprintType, Atomic)
struct FProjectContent
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectContent() {};

	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	int32		projectId;
};

USTRUCT(BlueprintType, Atomic)
struct FComment
{
	GENERATED_USTRUCT_BODY()
public:
	FComment() {};

	UPROPERTY(BlueprintReadWrite)
	int32		commentId;
	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	FString		accountId;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
};


USTRUCT(BlueprintType, Atomic)
struct FProjectDetailAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectDetailAPI() {};

	UPROPERTY(BlueprintReadWrite)
	FProjectContent		projectIdAndContent;
	UPROPERTY(BlueprintReadWrite)
	TArray<FComment>	commentIdList;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32>		supportedTeamIdList;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectAllDataAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectAllDataAPI() {};

	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectAllAPI>	data;
};


/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLCBPLProject : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};




