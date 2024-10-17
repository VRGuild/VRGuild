// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGBaseAPI.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UCWGBaseAPI::SetOAuthToken()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	if (Subsystem)
	{
		IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
		this->OAuthToken = Identity->GetAuthToken(0);
	}
}

void UCWGBaseAPI::HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("HttpCallBack"));
	if (bConnectedSuccessfully)
	{
		FString jsonString = res->GetContentAsString();
		this->HttpResult = jsonString;
		this->HttpStatus = res->GetResponseCode();

		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			OnSuccessAPI(req, res);
		}
	}
	bHttpWaitResponse = false;
}

void UCWGBaseAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI %s"), *this->HttpResult);
}
