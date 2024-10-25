// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/Project/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGProjectAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGProjectAPI : public UCWGBaseAPI
{
	GENERATED_BODY()

public:
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

	UFUNCTION(BlueprintCallable)
	void ProjectSupportPostCall(FProjectSupportAPI supportInfo);
	void ProjectSupportPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectSupportPostCallBack(FProjectAllDataAPI allProject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectSupportPostCallBack();

	UFUNCTION(BlueprintCallable)
	void ProjectSupportDeleteCall(int32 supportId);
	void ProjectSupportDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectSupportDeleteCallBack(FProjectAllDataAPI allProject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectSupportDeleteCallBack();

	UFUNCTION(BlueprintCallable)
	void ProjectSupportGetCall(int32 supportId);
	void ProjectSupportGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectSupportGetCallBack(FProjectAllDataAPI allProject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectSupportGetCallBack();

	UFUNCTION(BlueprintCallable)
	void ProjectSupportTeamGetCall(int32 teamId);
	void ProjectSupportTeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectSupportTeamGetCallBack(FProjectAllDataAPI allProject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailProjectSupportTeamGetCallBack();
};
