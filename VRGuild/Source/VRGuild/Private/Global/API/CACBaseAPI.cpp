// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACBaseAPI.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

// Sets default values for this component's properties
UCACBaseAPI::UCACBaseAPI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCACBaseAPI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCACBaseAPI::InitializeComponent()
{
	Super::InitializeComponent();

	this->Owner = GetOwner();
}

void UCACBaseAPI::SetOAuthToken()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	if (Subsystem)
	{
		IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
		this->OAuthToken = Identity->GetAuthToken(0);
	}
}

bool UCACBaseAPI::CheckCallBackAPI(FHttpRequestPtr req, FString api)
{
	api = api.TrimChar('/');
	if (!(this->URL + api).Compare(req->GetURL()))
		return true;
	return false;
}

void UCACBaseAPI::HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("HttpCallBack"));
	if (bConnectedSuccessfully && 200 <= res->GetResponseCode() && res->GetResponseCode() < 300)
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

void UCACBaseAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI %s"), *req->GetURL());
}

void UCACBaseAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI %s"), *req->GetURL());
}
