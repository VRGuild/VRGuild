// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLObject.generated.h"

// Position 구조체
USTRUCT(BlueprintType)
struct FObjectPosition
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectPosition() : x(0), y(0), z(0) {};

    UPROPERTY(BlueprintReadWrite)
    float x;

    UPROPERTY(BlueprintReadWrite)
    float y;

    UPROPERTY(BlueprintReadWrite)
    float z;
};

// Rotator 구조체
USTRUCT(BlueprintType)
struct FObjectRotator
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectRotator() : x(0), y(0), z(0) {};

    UPROPERTY(BlueprintReadWrite)
    float x;

    UPROPERTY(BlueprintReadWrite)
    float y;

    UPROPERTY(BlueprintReadWrite)
    float z;
};

// Object Info 구조체
USTRUCT(BlueprintType)
struct FObjectInfo
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectInfo() {};

    UPROPERTY(BlueprintReadWrite)
    FString objectId;

    UPROPERTY(BlueprintReadWrite)
    FString objectName;

    UPROPERTY(BlueprintReadWrite)
    FString objectClassName;

    UPROPERTY(BlueprintReadWrite)
    FObjectPosition position;

    UPROPERTY(BlueprintReadWrite)
    FObjectRotator rotator;

    UPROPERTY(BlueprintReadWrite)
    FString channelId;
};

// Object List Response 구조체
USTRUCT(BlueprintType)
struct FObjectListResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectListResponse() {};

    UPROPERTY(BlueprintReadWrite)
    TArray<FObjectInfo> Data;
};

// Object 생성/업데이트 요청 구조체
USTRUCT(BlueprintType)
struct FObjectCreateUpdateRequest
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectCreateUpdateRequest() {};

    UPROPERTY(BlueprintReadWrite)
    FString objectName;

    UPROPERTY(BlueprintReadWrite)
    FString objectClassName;

    UPROPERTY(BlueprintReadWrite)
    FObjectPosition position;

    UPROPERTY(BlueprintReadWrite)
    FObjectRotator rotator;
};

// Single Object Response 구조체
USTRUCT(BlueprintType)
struct FObjectResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FObjectResponse() {};

    UPROPERTY(BlueprintReadWrite)
    FObjectInfo Data;
};

UCLASS()
class VRGUILD_API UCBPLObject : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};