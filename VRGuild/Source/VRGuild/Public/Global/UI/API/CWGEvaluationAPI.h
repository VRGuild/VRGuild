// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGEvaluationAPI.generated.h"

struct FEvaluationResponse;
struct FEvaluationListResponse;
struct FEvaluationCreateRequest;
struct FEvaluation;

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGEvaluationAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
protected:
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Evaluation
    UFUNCTION(BlueprintCallable, Category = "Evaluation API")
    void EvaluationCreateCall(const FEvaluationCreateRequest& Request);
    void EvaluationCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnEvaluationCreateCallBack(const FEvaluation& Evaluation);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnFailEvaluationCreateCallBack(const FString& ErrorMessage);

    // Get User Category Evaluations
    UFUNCTION(BlueprintCallable, Category = "Evaluation API")
    void EvaluationGetCall(const FString& UserId, const FString& categoryEvaluation);
    void EvaluationGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnEvaluationGetCallBack(const TArray<FEvaluation>& Evaluations);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnFailEvaluationGetCallBack(const FString& ErrorMessage);

    // Update Evaluation
    UFUNCTION(BlueprintCallable, Category = "Evaluation API")
    void EvaluationUpdateCall(const FEvaluation& Evaluation);
    void EvaluationUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnEvaluationUpdateCallBack(const FEvaluation& Evaluation);
    UFUNCTION(BlueprintImplementableEvent, Category = "Evaluation API")
    void OnFailEvaluationUpdateCallBack(const FString& ErrorMessage);
};
