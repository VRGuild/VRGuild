// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACResgisterAPI.h"

UCACResgisterAPI::UCACResgisterAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACResgisterAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACResgisterAPI::InitializeComponent()
{
	Super::InitializeComponent();
}


void UCACResgisterAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI req->GetURL() : %s \n"), *req->GetURL());
	if (this->CheckCallBackAPI(req, "api/user/individual"))
	{
		this->ResgisterGetCallBack(req, res);
	}
	else if (this->CheckCallBackAPI(req, "api/auth/epicgames/user-info"))
	{
		
	}
}

void UCACResgisterAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
}

void UCACResgisterAPI::ResgisterGetCall(FString nickName)
{
	this->API = "api/resgister/nickname/" + nickName;
	this->HttpGetCall();
}

void UCACResgisterAPI::ResgisterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OauthToken : %s\n"), *this->OAuthToken);
}
