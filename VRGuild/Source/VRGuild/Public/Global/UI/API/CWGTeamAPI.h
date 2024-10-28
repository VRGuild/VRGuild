// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Global/Project/CBPLProject.h"
#include "Global/API/BPL/CBPLTeam.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGTeamAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGTeamAPI : public UCWGBaseAPI
{
	GENERATED_BODY()

public:
	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

	UFUNCTION(BlueprintCallable)
	void TeamPostCall(FTeamInfoAPI teamInfo);
	void TeamPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamPostCallBack(FTeamDetailInfoAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamPostCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamPatchCall(FTeamInfoAPI ss);
	void TeamPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamPatchCallBack(FTeamDetailInfoAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamPatchCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamGetCall(int32 TeamId);
	void TeamGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamGetCallBack(FTeamDetailInfoAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamGetCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamDeleteCall(int32 TeamId);
	void TeamDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamDeleteCallBack();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamDeleteCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamManagerGetCall();
	void TeamManagerGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamManagerGetCallBack(FTeamInfoDataArrayAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamManagerGetCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamMemberPostCall(FTeamIdAPI TeamId);
	void TeamMemberPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamMemberPostCallBack(FTeamDetailInfoAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamMemberPostCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamMemberDeleteCall(FTeamIdAPI TeamId);
	void TeamMemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamMemberDeleteCallBack(FTeamDetailInfoAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamMemberDeleteCallBack();

	UFUNCTION(BlueprintCallable)
	void TeamMemberSearchGetCall();
	void TeamMemberSearchGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamMemberSearchGetCallBack(FTeamInfoDataArrayAPI ParseData);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFailTeamMemberSearchGetCallBack();




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
