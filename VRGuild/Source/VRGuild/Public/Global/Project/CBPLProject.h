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

	UPROPERTY(BlueprintReadOnly)
	int32 InitiatorId;
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> ProjectNoticeId;
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* CompanyImage;
	UPROPERTY(BlueprintReadOnly)
	FString CompanyName;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectNotice
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectNotice() {};

	UPROPERTY(BlueprintReadOnly)
	int32 ProjectNoticeId;
	UPROPERTY(BlueprintReadOnly)
	int32 ProjectDetailId;
	UPROPERTY(BlueprintReadOnly)
	FProjectInitator InitiatorId;
	UPROPERTY(BlueprintReadOnly)
	FVector Postision;
	UPROPERTY(BlueprintReadOnly)
	FString ProjectTitle;
	UPROPERTY(BlueprintReadOnly)
	FString ProjectEmployee;
	UPROPERTY(BlueprintReadOnly)
	int32 ProjectPrice;
	UPROPERTY(BlueprintReadOnly)
	FDateTime ProjectCreateDate;
	UPROPERTY(BlueprintReadOnly)
	FDateTime ProjectEndDate;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectDetail
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectDetail() {};

	UPROPERTY(BlueprintReadOnly)
	int32 ProjectDetailId;
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> TeamId;
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> CommentID;
	UPROPERTY(BlueprintReadOnly)
	FString ProjectDetailNote;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectComment
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectComment() {};

	UPROPERTY(BlueprintReadOnly)
	int32 CommentID;
	UPROPERTY(BlueprintReadOnly)
	int32 UserID;
	UPROPERTY(BlueprintReadOnly)
	FString Comment;
	UPROPERTY(BlueprintReadOnly)
	FDateTime CreateDate;
	UPROPERTY(BlueprintReadOnly)
	FDateTime UpdateDate;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectTeam
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectTeam() {};

	UPROPERTY(BlueprintReadOnly)
	int32 TeamId;
	UPROPERTY(BlueprintReadOnly)
	int32 CaptainID;
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> CrewID;
	UPROPERTY(BlueprintReadOnly)
	FDateTime CreateDate;
	UPROPERTY(BlueprintReadOnly)
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
