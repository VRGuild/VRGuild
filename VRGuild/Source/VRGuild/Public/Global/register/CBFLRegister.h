// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBFLRegister.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FSkillInfo() {};

	UPROPERTY(BlueprintReadOnly)
	FString SkillName;
	UPROPERTY(BlueprintReadOnly)
	int32 SkillLevel;
};


USTRUCT(BlueprintType, Atomic)
struct FSendFile
{
	GENERATED_USTRUCT_BODY()

public:
	FSendFile() {};

	UPROPERTY(BlueprintReadOnly)
	FString FileName;
	UPROPERTY(BlueprintReadOnly)
	FString FilePath;
	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> FileData;
};

USTRUCT(BlueprintType, Atomic)
struct FRegister
{
	GENERATED_USTRUCT_BODY()

public:
	FRegister() {};

	UPROPERTY(BlueprintReadOnly)
	int32 NickName;
	UPROPERTY(BlueprintReadOnly)
	FString Email;
	UPROPERTY(BlueprintReadOnly)
	FString PhoneNumber;
	UPROPERTY(BlueprintReadOnly)
	FString Github;
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Links;
	UPROPERTY(BlueprintReadOnly)
	TArray<FSkillInfo> Skills;
	UPROPERTY(BlueprintReadOnly)
	TArray<FSendFile> FileName;
	UPROPERTY(BlueprintReadOnly)
	FString SelfIntro;
	UPROPERTY(BlueprintReadOnly)
	FString IntroProject;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBFLRegister : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
