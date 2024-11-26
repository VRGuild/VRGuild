// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLMemo.generated.h"

// Position 구조체
USTRUCT(BlueprintType)
struct FMemoPosition
{
    GENERATED_USTRUCT_BODY()
public:
    FMemoPosition() : x(0), y(0), z(0) {};

    UPROPERTY(BlueprintReadWrite)
    float x;

    UPROPERTY(BlueprintReadWrite)
    float y;

    UPROPERTY(BlueprintReadWrite)
    float z;
};

// Memo 정보 구조체
USTRUCT(BlueprintType)
struct FMemoInfo
{
    GENERATED_USTRUCT_BODY()
public:
    FMemoInfo() {};

    UPROPERTY(BlueprintReadWrite)
    FString memoId;

    UPROPERTY(BlueprintReadWrite)
    FString channelId;

    UPROPERTY(BlueprintReadWrite)
    FString memoText;

    UPROPERTY(BlueprintReadWrite)
    FMemoPosition position;

    UPROPERTY(BlueprintReadWrite)
    FDateTime createdAt;

    UPROPERTY(BlueprintReadWrite)
    FDateTime modifiedAt;
};

// Memo 목록 응답 구조체
USTRUCT(BlueprintType)
struct FMemoListResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FMemoListResponse() {};

    UPROPERTY(BlueprintReadWrite)
    TArray<FMemoInfo> memoInfoList;
};

// Memo 생성/수정 요청 구조체
USTRUCT(BlueprintType)
struct FMemoCreateUpdateRequest
{
    GENERATED_USTRUCT_BODY()
public:
    FMemoCreateUpdateRequest() {};

    UPROPERTY(BlueprintReadWrite)
    FString memoText;

    UPROPERTY(BlueprintReadWrite)
    FMemoPosition position;
};

// API 응답 구조체
USTRUCT(BlueprintType)
struct FMemoAPIResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FMemoAPIResponse() {};

    UPROPERTY(BlueprintReadWrite)
    FString message;

    UPROPERTY(BlueprintReadWrite)
    bool success;
};

UCLASS()
class VRGUILD_API UCBPLMemo : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};