#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACEtherAPI.generated.h"

struct FEtherResponse;
struct FEtherListResponse;
struct FEtherBalanceResponse;
struct FEther;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACEtherAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACEtherAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Ether Record
    UFUNCTION(BlueprintCallable, Category = "Ether API")
    void EtherCreateCall(const FEther& Ether);
    void EtherCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnEtherCreateCallBack(const FEther& Ether);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnFailEtherCreateCallBack(const FString& ErrorMessage);

    // Get Ether Record
    UFUNCTION(BlueprintCallable, Category = "Ether API")
    void EtherGetCall(const FString& EtherId);
    void EtherGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnEtherGetCallBack(const FEther& Ether);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnFailEtherGetCallBack(const FString& ErrorMessage);

    // Get Ether List
    UFUNCTION(BlueprintCallable, Category = "Ether API")
    void EtherListGetCall();
    void EtherListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnEtherListGetCallBack(const TArray<FEther>& EtherList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnFailEtherListGetCallBack();

    // Get User Ether History
    UFUNCTION(BlueprintCallable, Category = "Ether API")
    void EtherHistoryGetCall(const FString& UserId);
    void EtherHistoryGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnEtherHistoryGetCallBack(const FEther& EtherBalance);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ether API")
    void OnFailEtherHistoryGetCallBack();
};