// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACProjectNoticeAPI.h"

UCACProjectNoticeAPI::UCACProjectNoticeAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACProjectNoticeAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACProjectNoticeAPI::InitializeComponent()
{
	Super::InitializeComponent();
}

void UCACProjectNoticeAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s \n"), *req->GetURL());
	if (this->CheckCallBackAPI(req, "api/character"))
	{

	}
}

void UCACProjectNoticeAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
}

void UCACProjectNoticeAPI::ProjectNoticeListGetCall()
{
	this->API = "api/character";

	HttpGetCall();
}

void UCACProjectNoticeAPI::ProjectNoticeListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{

}
