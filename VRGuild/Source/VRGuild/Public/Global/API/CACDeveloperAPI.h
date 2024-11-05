#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACDeveloperAPI.generated.h"

struct FDeveloperResponse;
struct FDeveloperRequest;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACDeveloperAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACDeveloperAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperCreateCall(const FDeveloperRequest& Request);
    void DeveloperCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperCreateCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperCreateCallBack();

    // Get Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperGetCall();
    void DeveloperGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperGetCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperGetCallBack();

    // Update Developer
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperUpdateCall(const FDeveloperRequest& Request);
    void DeveloperUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperUpdateCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperUpdateCallBack();

    // Get Developer By UserId
    UFUNCTION(BlueprintCallable, Category = "Developer API")
    void DeveloperGetByUserIdCall(const FString& UserId);
    void DeveloperGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnDeveloperGetByUserIdCallBack(const FDevInfo& DeveloperInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Developer API")
    void OnFailDeveloperGetByUserIdCallBack();
};