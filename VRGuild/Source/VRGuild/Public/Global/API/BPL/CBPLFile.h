// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLFile.generated.h"



// FFileData 구조체도 업데이트 필요
USTRUCT(BlueprintType)
struct FFileData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "File")
    TArray<uint8> multipartFiles;

    UPROPERTY(BlueprintReadWrite, Category = "File")
    FString fileName;  // 파일 이름 필드 추가
};



USTRUCT(BlueprintType)
struct FFileDatas
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    TArray<FFileData> multipartFiles;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FString filePath;
};

USTRUCT(BlueprintType)
struct FFileInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "File")
    FString filePath;

    UPROPERTY(BlueprintReadWrite, Category = "File")
    FString fileName;  // 파일 이름 필드 추가
};

USTRUCT(BlueprintType)
struct FFileInfoDatas
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    TArray<FFileInfo> multipartFiles;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FString filePath;
};

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
