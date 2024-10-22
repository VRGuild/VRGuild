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

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLCBPLProject : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
