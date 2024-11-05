#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACBusinessAPI.generated.h"

struct FBusinessInfoResponse;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACBusinessAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACBusinessAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Business Info
    UFUNCTION(BlueprintCallable, Category = "Business API")
    void BusinessInfoGetCall(const FString& BusinessId);
    void BusinessInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Business API")
    void OnBusinessInfoGetCallBack(const FBusinessInfo& BusinessInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Business API")
    void OnFailBusinessInfoGetCallBack();
};