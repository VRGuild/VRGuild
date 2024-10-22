// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACProjectNoticeAPI.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FCommentAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FCommentAPI() {};

	UPROPERTY(BlueprintReadOnly)
	int32 commentId;
	UPROPERTY(BlueprintReadOnly)
	FString content;
	UPROPERTY(BlueprintReadOnly)
	FString accountId;
	UPROPERTY(BlueprintReadOnly)
	FDateTime createdAt;
	UPROPERTY(BlueprintReadOnly)
	FDateTime modifiedAt;
};

USTRUCT(BlueprintType, Atomic)
struct FProjectAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectAPI() {};
	UPROPERTY(BlueprintReadWrite)
	int32 projectId;
	UPROPERTY(BlueprintReadWrite)
	FString		workScope;
	UPROPERTY(BlueprintReadWrite)
	FString		workType;
	UPROPERTY(BlueprintReadWrite)
	FString		progressClassification;
	UPROPERTY(BlueprintReadWrite)
	FString		companyName;
	UPROPERTY(BlueprintReadWrite)
	FString		title;
	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredClient;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredServer;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredDesign;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredPlanner;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredAIEngineer;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	startDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	endDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	estimatedCost;
};


USTRUCT(BlueprintType, Atomic)
struct FProjectInfoAPI
{
	GENERATED_USTRUCT_BODY()
public:
	FProjectInfoAPI() {};

	UPROPERTY(BlueprintReadWrite)
	int32 projectId;
	UPROPERTY(BlueprintReadWrite)
	FString		workScope;
	UPROPERTY(BlueprintReadWrite)
	FString		workType;
	UPROPERTY(BlueprintReadWrite)
	FString		progressClassification;
	UPROPERTY(BlueprintReadWrite)
	FString		companyName;
	UPROPERTY(BlueprintReadWrite)
	FString		title;
	UPROPERTY(BlueprintReadWrite)
	FString		content;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredClient;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredServer;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredDesign;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredPlanner;
	UPROPERTY(BlueprintReadWrite)
	int32		requiredAIEngineer;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	startDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	endDateTime;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	estimatedCost;

	UPROPERTY(BlueprintReadWrite)
	FString		accountId;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	createdAt;
	UPROPERTY(BlueprintReadWrite)
	FDateTime	modifiedAt;
	UPROPERTY(BlueprintReadWrite)
	FVector		projectVector;

	UPROPERTY(BlueprintReadWrite)
	TArray<FCommentAPI>	comments;
};


/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACProjectNoticeAPI : public UCACBaseAPI
{
	GENERATED_BODY()

public:
	UCACProjectNoticeAPI();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void ProjectNewProjectPostCall(FProjectAPI projectInfo);
	void ProjectNewProjectPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectNewProjectPostCallBack(FProjectInfoAPI projectDetail);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectNewProjectPostCallBack();


	UFUNCTION(BlueprintCallable)
	void ProjectPatchCall(FProjectAPI projectInfo);
	void ProjectPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectPatchCallBack(FProjectInfoAPI projectDetail);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectPatchCallBack();


	UFUNCTION(BlueprintCallable)
	void ProjectDetailGetCall(int32 projectId);
	void ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectDetailGetCallBack(FProjectInfoAPI projectDetail);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectDetailGetCallBack();


	UFUNCTION(BlueprintCallable)
	void ProjectDetailDeleteCall(int32 projectId);
	void ProjectDetailDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectDetailDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectDetailDeleteCallBack();

	//UFUNCTION(BlueprintCallable)
	//void ProjectPostisionPatchCall(int32 projectId, FVector position);
	//void ProjectPostisionPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectPostisionPatchCallBack();
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnFailProjectPostisionPatchCallBack();


	//UFUNCTION(BlueprintCallable)
	//void ProjectListOfUserGetCall(TArray<int32> CustomList);
	//void ProjectListOfUserGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectListOfUserGetCallBack(FCharacterCustomGetAPI ParseData);


};