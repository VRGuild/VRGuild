﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/Project/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACProjectNoticeAPI.generated.h"

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
	void OnProjectDetailGetCallBack(FProjectDetailAPI projectDetail);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectDetailGetCallBack();


	UFUNCTION(BlueprintCallable)
	void ProjectDetailDeleteCall(int32 projectId);
	void ProjectDetailDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectDetailDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectDetailDeleteCallBack();

	UFUNCTION(BlueprintCallable)
	void ProjectAllGetCall();
	void ProjectAllGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectAllGetCallBack(FProjectAllDataAPI allProject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectAllGetCallBack();


	//UFUNCTION(BlueprintCallable)
	//void ProjectListOfUserGetCall(TArray<int32> CustomList);
	//void ProjectListOfUserGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectListOfUserGetCallBack(FCharacterCustomGetAPI ParseData);


};