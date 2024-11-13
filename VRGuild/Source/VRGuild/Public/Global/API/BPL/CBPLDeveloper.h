#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CBPLDeveloper.generated.h"


UENUM(BlueprintType)
enum class EDeveloperRole : uint8
{
    Server      UMETA(DisplayName = "Server Developer"),
    Client      UMETA(DisplayName = "Client Developer"),
    Design      UMETA(DisplayName = "Game Designer"),
    AI          UMETA(DisplayName = "AI Developer"),
    Planner     UMETA(DisplayName = "Game Planner"),
    Community   UMETA(DisplayName = "Community Of Player")
};



// Developer Create/Update Request Structure
USTRUCT(BlueprintType)
struct FDeveloperRequest
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FString nickname;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FDevInfo devInfo;
};

// Response Structure
USTRUCT(BlueprintType)
struct FDeveloperResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    FDevInfo data;
};

// Response Structure
USTRUCT(BlueprintType)
struct FDeveloperListResponse : public FBaseResponse
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "API Response")
    TArray<FDeveloperRequest> data;
};



// Developer Info Structure
USTRUCT(BlueprintType)
struct FDevInfoCreate
{
    GENERATED_USTRUCT_BODY()
public:

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    int64 devId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    int64 userId = 0;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devName;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devEmail;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devPhone;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString githubLink;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> portfolioList;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString career;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> skillCategoryList;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> tag;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString hope;
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FDateTime createdAt;  // createAt -> createdAt
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FDateTime modifiedAt;
};


// Developer Create/Update Request Structure
USTRUCT(BlueprintType)
struct FDeveloperCreateRequest
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FString nickname;
    UPROPERTY(BlueprintReadWrite, Category = "Developer|Request")
    FDevInfoCreate devInfo;
};


// Dev Create Detail Info Structure
USTRUCT(BlueprintType)
struct FDevCreateDetailInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devName;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devEmail;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString devPhone;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString githubLink;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> portfolioList;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString career;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> categoryNameList;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    TArray<FString> tag;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString hope;
};

// Dev Create Info Structure
USTRUCT(BlueprintType)
struct FDevCreateInfo
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FString nickname;

    UPROPERTY(BlueprintReadWrite, Category = "Developer")
    FDevCreateDetailInfo devInfo;
};



UCLASS()
class VRGUILD_API UCBPLDeveloper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    // 문자열로 변환하는 헬퍼 함수
    UFUNCTION(BlueprintCallable)
    static FString GetDeveloperRoleString(EDeveloperRole Role)
    {
        switch (Role)
        {
        case EDeveloperRole::Server:
            return TEXT("Server");
        case EDeveloperRole::Client:
            return TEXT("Client");
        case EDeveloperRole::Design:
            return TEXT("Designer");
        case EDeveloperRole::AI:
            return TEXT("AI");
        case EDeveloperRole::Planner:
            return TEXT("Planner");
        case EDeveloperRole::Community:
            return TEXT("Community");
        default:
            return TEXT("Unknown");
        }
    }
};