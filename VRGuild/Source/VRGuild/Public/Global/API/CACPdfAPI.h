// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Global/API/BPL/CBPLPdf.h"
#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACPdfAPI.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACPdfAPI : public UCACBaseAPI
{
    GENERATED_BODY()
public:
    UCACPdfAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    class ACPCBasePlayerController* OwnerPlayerController;

    // Get PDFs by Channel (GET /api/tile/pdf/{channelId})
    UFUNCTION(BlueprintCallable)
    void GetPdfsByChannelCall(const FString& channelId);
    void GetPdfsByChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnGetPdfsByChannelCallBack(const FPdfListResponse& PdfList);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailGetPdfsByChannelCallBack();

    // Register PDF (POST /api/tile/pdf/{channelId})
    UFUNCTION(BlueprintCallable)
    void RegisterPdfCall(const FString& channelId, const FPdfCreateUpdateRequest& PdfData);
    void RegisterPdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnRegisterPdfCallBack(const FPdfAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailRegisterPdfCallBack();

    // Update PDF (PATCH /api/tile/pdf/{pdfId})
    UFUNCTION(BlueprintCallable)
    void UpdatePdfCall(const FString& pdfId, const FPdfCreateUpdateRequest& PdfData);
    void UpdatePdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnUpdatePdfCallBack(const FPdfAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailUpdatePdfCallBack();

    // Delete PDF (DELETE /api/tile/pdf/{pdfId})
    UFUNCTION(BlueprintCallable)
    void DeletePdfCall(const FString& pdfId);
    void DeletePdfCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent)
    void OnDeletePdfCallBack(const FPdfAPIResponse& Response);
    UFUNCTION(BlueprintImplementableEvent)
    void OnFailDeletePdfCallBack();
};