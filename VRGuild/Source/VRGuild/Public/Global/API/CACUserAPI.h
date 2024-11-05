// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLUser.h"

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACUserAPI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACUserAPI : public UCACBaseAPI
{
	GENERATED_BODY()

public:
    UCACUserAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

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
