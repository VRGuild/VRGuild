#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACProjectAPI.generated.h"

struct FProjectResponse;
struct FProjectDetailResponse;
struct FProjectListResponse;
struct FProjectTeamListResponse;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACProjectAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACProjectAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
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
    void ProjectGetCall(const FString& ProjectId);
    void ProjectGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectGetCallBack(const FProjectInfo& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectGetCallBack();

    // Update Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectUpdateCall(const FString& ProjectId, const FProjectInfo& ProjectInfo);
    void ProjectUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectUpdateCallBack(const FProjectInfo& ProjectInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectUpdateCallBack();

    // Get Project Detail
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectDetailGetCall(const FString& ProjectId);
    void ProjectDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectDetailGetCallBack(const FProjectDetailInfo& ProjectDetail);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectDetailGetCallBack();

    // Get Project List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectListGetCall(const FString& Number);
    void ProjectListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectListGetCallBack(const TArray<FProjectDetailInfo>& ProjectList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectListGetCallBack();

    // Get Project Team List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectTeamListGetCall(const FString& ProjectId);
    void ProjectTeamListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectTeamListGetCallBack(const FProjectTeamList& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectTeamListGetCallBack();

    // Get Project Comment List
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectCommentListGetCall(const FString& ProjectId);
    void ProjectCommentListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectCommentListGetCallBack(const TArray<int64>& CommentList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectCommentListGetCallBack();

    // Apply To Project
    UFUNCTION(BlueprintCallable, Category = "Project API")
    void ProjectApplyCall(const FString& ProjectId);
    void ProjectApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnProjectApplyCallBack(const FProjectTeamList& TeamList);
    UFUNCTION(BlueprintImplementableEvent, Category = "Project API")
    void OnFailProjectApplyCallBack(const FString& ErrorMessage);
};
