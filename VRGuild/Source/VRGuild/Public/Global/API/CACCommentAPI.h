#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACCommentAPI.generated.h"

struct FCommentResponse;
struct FCommentDetailResponse;
struct FComment;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACCommentAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACCommentAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Comment
    UFUNCTION(BlueprintCallable, Category = "Comment API")
    void CommentCreateCall(const FComment& Comment);
    void CommentCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnCommentCreateCallBack(const FComment& Comment);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnFailCommentCreateCallBack();

    // Get Comment
    UFUNCTION(BlueprintCallable, Category = "Comment API")
    void CommentGetCall(const FString& CommentId);
    void CommentGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnCommentGetCallBack(const FComment& Comment);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnFailCommentGetCallBack();

    // Update Comment
    UFUNCTION(BlueprintCallable, Category = "Comment API")
    void CommentUpdateCall(const FString& CommentId, const FComment& Comment);
    void CommentUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnCommentUpdateCallBack(const FComment& Comment);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnFailCommentUpdateCallBack();

    // Get Comment Detail
    UFUNCTION(BlueprintCallable, Category = "Comment API")
    void CommentDetailGetCall(const FString& CommentId);
    void CommentDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnCommentDetailGetCallBack(const FCommentDetailInfo& CommentDetail);
    UFUNCTION(BlueprintImplementableEvent, Category = "Comment API")
    void OnFailCommentDetailGetCallBack();
};