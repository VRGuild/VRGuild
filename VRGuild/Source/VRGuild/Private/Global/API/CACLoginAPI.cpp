// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACLoginAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

UCACLoginAPI::UCACLoginAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	
	this->URL = "http://localhost:3000/api";
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

void UCACLoginAPI::LoginPostCall()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	FJsonLogin loginToken = FJsonLogin(Identity->GetAuthToken(0));

	HttpPostCall<FJsonLogin>(loginToken);
}

void UCACLoginAPI::OnSuccessAPI()
{
	OnLoginComple();
}
