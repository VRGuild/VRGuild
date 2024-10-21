// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	void ProjectNoticeListGetCall();
	void ProjectNoticeListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectNoticeListGetCallBack();

	//UFUNCTION(BlueprintCallable)
	//void ProjectNoticeUpdatePatchCall(TArray<int32> CustomList);
	//void ProjectNoticeUpdatePatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectNoticeUpdatePatchCallBack(FCharacterCustomGetAPI ParseData);

	//UFUNCTION(BlueprintCallable)
	//void ProjectNoticeDeleteCall(TArray<int32> CustomList);
	//void ProjectNoticeDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectNoticeDeleteCallBack(FCharacterCustomGetAPI ParseData);

	//UFUNCTION(BlueprintCallable)
	//void ProjectDetailGetCall(TArray<int32> CustomList);
	//void ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectDetailGetCallBack(FCharacterCustomGetAPI ParseData);

	//UFUNCTION(BlueprintCallable)
	//void ProjectListOfUserGetCall(TArray<int32> CustomList);
	//void ProjectListOfUserGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnProjectListOfUserGetCallBack(FCharacterCustomGetAPI ParseData);


};