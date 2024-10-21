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

bool UCWGBaseAPI::CheckCallBackAPI(FHttpRequestPtr req, FString api)
{
	api = api.TrimChar('/');
	if (req->GetURL() == (this->URL + api))
		return true;
	return false;
}

void UCWGBaseAPI::HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("HttpCallBack"));
	if (bConnectedSuccessfully && res->GetResponseCode() == 200)
	{
		OnSuccessAPI(req, res);
	}
	else
	{
		// 실패 했을때
		OnFailAPI(req, res);
	}
	bHttpWaitResponse = false;
}

void UCWGBaseAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI %s"), *req->GetURL());
}

void UCWGBaseAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI %s"), *req->GetURL());
}
