// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLTile.h"
#include "CBPLChannel.generated.h"

// 채널 생성 요청 구조체
USTRUCT(BlueprintType, Atomic)
struct FChannelnfoCreateAPI
{
    GENERATED_USTRUCT_BODY()
public:
    FChannelnfoCreateAPI() {};

    UPROPERTY(BlueprintReadWrite)
    FString channelName;
};

// 채널 업데이트 요청 구조체
USTRUCT(BlueprintType, Atomic)
struct FChannelInfoUpdateAPI
{
    GENERATED_USTRUCT_BODY()
public:
    FChannelInfoUpdateAPI() {};

    UPROPERTY(BlueprintReadWrite)
    FString channelName;
};

// 채널 정보 구조체
USTRUCT(BlueprintType, Atomic)
struct FChannelInfoAPI
{
    GENERATED_USTRUCT_BODY()
public:
    FChannelInfoAPI() {};

    UPROPERTY(BlueprintReadWrite)
    FString channelId;

    UPROPERTY(BlueprintReadWrite)
    FString channelName;

    UPROPERTY(BlueprintReadWrite)
    FDateTime createdAt;

    UPROPERTY(BlueprintReadWrite)
    FDateTime modifiedAt;
};

// 단일 채널 응답 데이터 구조체
USTRUCT(BlueprintType, Atomic)
struct FChannelInfoDataAPI
{
    GENERATED_USTRUCT_BODY()
public:
    FChannelInfoDataAPI() {};

    UPROPERTY(BlueprintReadWrite)
    FChannelInfoAPI Data;
};

// 채널 목록 응답 데이터 구조체
USTRUCT(BlueprintType, Atomic)
struct FChannelInfoDataListAPI
{
    GENERATED_USTRUCT_BODY()
public:
    FChannelInfoDataListAPI() {};

    UPROPERTY(BlueprintReadWrite)
    TArray<FChannelInfoAPI> Data;
};

UCLASS()
class VRGUILD_API UCBPLChannel : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};