// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGProjectAPI.generated.h"

struct FProjectAPI;
struct FProjectInfoAPI;
struct FProjectDetailAPI;
struct FProjectAllDataAPI;
struct FProjectSupportAPI;
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

    // Create Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectCreateCall(const FProjectInfo& ProjectInfo);
    void ProjectCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectCreateCallBack(const FProjectInfo& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectCreateCallBack();

    // Get Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectGetCall(const int64 ProjectId);
    void ProjectGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectGetCallBack(const FProjectInfo& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectGetCallBack();

    // Update Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectUpdateCall(const int64 ProjectId, const FProjectInfo& ProjectInfo);
    void ProjectUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectUpdateCallBack(const FProjectInfo& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectUpdateCallBack();

    // Get Project Detail
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectDetailGetCall(const int64 ProjectId);
    void ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectDetailGetCallBack(const FProjectWithDetail& ProjectDetail);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectDetailGetCallBack();

    // Get Project List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectListGetCall(const int64 Number);
    void ProjectListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectListGetCallBack(FProjectPagedResponse ParsedResponse);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectListGetCallBack();

    // Get Project Detail List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectDetailListGetCall(const int64 Number);
    void ProjectDetailListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectDetailListGetCallBack(FProjectDetailPagedResponse ParsedResponse);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectDetailListGetCallBack();

    // Get  Project by Account
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectAccountGetCall(int32 page);
    void ProjectAccountGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectAccountGetCallBack(const FProjectPagedResponse& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectAccountGetCallBack();

    // Get Project Team List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectTeamListGetCall(const int64 ProjectId);
    void ProjectTeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectTeamListGetCallBack(const FProjectTeamList& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectTeamListGetCallBack();

    // Get Project Comment List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectCommentListGetCall(const int64 ProjectId);
    void ProjectCommentListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectCommentListGetCallBack(const FProjectInfo& CommentList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectCommentListGetCallBack();

    // Apply To Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectApplyCall(const int64 ProjectId);
    void ProjectApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectApplyCallBack(const FProjectTeamList& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectApplyCallBack(const FString& ErrorMessage);
};
