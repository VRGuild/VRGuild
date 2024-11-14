// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGUserAPI.h"
#include "CWGMemberAPI.generated.h"

struct FMemberDetailResponse;
struct FMemberInfo;

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGMemberAPI : public UCWGUserAPI
{
	GENERATED_BODY()
protected:

    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Get Member Info
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberGetCall(const int64& MemberId);
    void MemberGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberGetCallBack(const FMemberInfo& MemberInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberGetCallBack();

    // Accept Member
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberAcceptCall(const FString& MemberId);
    void MemberAcceptCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberAcceptCallBack(const FMemberInfo& MemberInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberAcceptCallBack();

    // Reject Member
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberRejectCall(const FString& MemberId);
    void MemberRejectCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberRejectCallBack(const FMemberInfo& MemberInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberRejectCallBack();

    // Delete Member
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberDeleteCall(const FString& MemberId);
    void MemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberDeleteCallBack();
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberDeleteCallBack(const FString& ErrorMessage);


    // accept Member
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberNewAccpetCall(const int64& MemberId);
    void MemberNewAccpetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberNewAccpetCallBack();
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberNewAccpetCallBack(const FString& ErrorMessage);
    // Reject Member
    UFUNCTION(BlueprintCallable, Category = "Member API")
    void MemberNewRejectCall(const int64& MemberId);
    void MemberNewRejectCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnMemberNewRejectCallBack();
    UFUNCTION(BlueprintImplementableEvent, Category = "Member API")
    void OnFailMemberNewRejectCallBack(const FString& ErrorMessage);


};
