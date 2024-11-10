// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLUser.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGBaseAPI.h"
#include "CWGUserAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGUserAPI : public UCWGBaseAPI
{
	GENERATED_BODY()
protected:

    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // User Basic Info
    UFUNCTION(BlueprintCallable, Category = "User API")
    void UserOwnInfoGetCall();
    void UserOwnInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnUserOwnInfoGetCallBack(const FUserInfo& UserInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnFailUserOwnInfoGetCallBack();

    // User Basic Info
    UFUNCTION(BlueprintCallable, Category = "User API")
    void UserInfoGetCall(const FString& UserId);
    void UserInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnUserInfoGetCallBack(const FUserInfo& UserInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnFailUserInfoGetCallBack();

    // User Member Detail Info
    UFUNCTION(BlueprintCallable, Category = "User API")
    void UserMemberInfoGetCall(const FString& UserId);
    void UserMemberInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnUserMemberInfoGetCallBack(const FUserMemberInfo& MemberInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "User API")
    void OnFailUserMemberInfoGetCallBack();


};
