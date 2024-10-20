// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACLoginAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

UCACLoginAPI::UCACLoginAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	
}

void UCACLoginAPI::BeginPlay()
{
	Super::BeginPlay();

}

void UCACLoginAPI::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerPlayerController = nullptr;
	if (Owner->IsA<ACPCBasePlayerController>())
	{
		OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
	}
}

void UCACLoginAPI::EpicLoginPostCall()
{
	this->API = "api/auth/epicgames/callback";

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	FJsonLogin loginToken = FJsonLogin(Identity->GetAuthToken(0));

	HttpPostCall<FJsonLogin>(loginToken);

}

void UCACLoginAPI::EpicLoginInfoGetCall()
{
	this->API = "api/auth/epicgames/user-info";

	HttpGetCall();
}


void UCACLoginAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("req->GetURL() : %s \n"), *req->GetURL());
	if (this->CheckCallBackAPI(req, "api/auth/epicgames/callback"))
	{
		OnEpicLoginComple();
	}
	else if (this->CheckCallBackAPI(req, "api/auth/epicgames/user-info"))
	{
		OnEpicGetLoginInfoComple();
	}
}

void UCACLoginAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
}
