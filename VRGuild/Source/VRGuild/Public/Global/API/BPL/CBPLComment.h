#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLComment.generated.h"

// Comment User Info Structure
USTRUCT(BlueprintType)
struct FCommentUserInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    int64 userId;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FCharacterInfo characterInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FDevInfo devInfo;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    int32 experienceValue;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    int32 businessId;
    UPROPERTY(BlueprintReadWrite, Category = "Comment|User")
    FString nickName;
};

// Comment Detail Structure
USTRUCT(BlueprintType)
struct FCommentDetailInfo : public FComment
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Comment|Detail")
    FCommentUserInfo userInfo;
};

// Comment Response Structure
USTRUCT(BlueprintType)
struct FCommentResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FComment data;
};

// Comment Detail Response Structure
USTRUCT(BlueprintType)
struct FCommentDetailResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FCommentDetailInfo data;
};

UCLASS()
class VRGUILD_API UCBPLComment : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};