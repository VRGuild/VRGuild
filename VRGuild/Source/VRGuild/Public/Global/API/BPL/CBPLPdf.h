// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLPdf.generated.h"

// PDF 정보 구조체
USTRUCT(BlueprintType)
struct FPdfInfo
{
    GENERATED_USTRUCT_BODY()
public:
    FPdfInfo() {};

    UPROPERTY(BlueprintReadWrite)
    FString pdfId;

    UPROPERTY(BlueprintReadWrite)
    FString channelId;

    UPROPERTY(BlueprintReadWrite)
    FString pdfUrl;

    UPROPERTY(BlueprintReadWrite)
    FDateTime createdAt;

    UPROPERTY(BlueprintReadWrite)
    FDateTime modifiedAt;
};

// PDF 목록 응답 구조체
USTRUCT(BlueprintType)
struct FPdfListResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FPdfListResponse() {};

    UPROPERTY(BlueprintReadWrite)
    TArray<FPdfInfo> pdfUrlList;
};

// PDF 생성/수정 요청 구조체
USTRUCT(BlueprintType)
struct FPdfCreateUpdateRequest
{
    GENERATED_USTRUCT_BODY()
public:
    FPdfCreateUpdateRequest() {};

    UPROPERTY(BlueprintReadWrite)
    FString pdfUrl;
};

// API 응답 구조체
USTRUCT(BlueprintType)
struct FPdfAPIResponse
{
    GENERATED_USTRUCT_BODY()
public:
    FPdfAPIResponse() {};

    UPROPERTY(BlueprintReadWrite)
    FString message;

    UPROPERTY(BlueprintReadWrite)
    bool success;
};

UCLASS()
class VRGUILD_API UCBPLPdf : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};