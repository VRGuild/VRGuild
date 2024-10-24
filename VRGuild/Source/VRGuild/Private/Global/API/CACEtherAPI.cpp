﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACEtherAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACEtherAPI::UCACEtherAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACEtherAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACEtherAPI::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerPlayerController = nullptr;
	if (Owner->IsA<ACPCBasePlayerController>())
	{
		OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
	}
}

void UCACEtherAPI::EtherPostCall()
{
	FJsonEther ether = FJsonEther();

	HttpPostCall<FJsonEther>(ether);

}

void UCACEtherAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnEtherComple();
}

void UCACEtherAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
}
