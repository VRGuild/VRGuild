// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACCharacterCustomAPI.h"
#include "Global/CGIGameInstance.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACCharacterCustomAPI::UCACCharacterCustomAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACCharacterCustomAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACCharacterCustomAPI::InitializeComponent()
{
	Super::InitializeComponent();

}

void UCACCharacterCustomAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s \n"), *req->GetURL());
	if (this->CheckCallBackAPI(req, "api/character"))
	{
		if (req->GetVerb() == "GET")
		{
			CharacterCustomGetCallBack(req, res);
		}
		else if (req->GetVerb() == "POST")
		{
			CharacterCustomUpdateCallBack(req, res);
		}
	}
}

void UCACCharacterCustomAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
	if (this->CheckCallBackAPI(req, "api/character"))
	{
		if (req->GetVerb() == "GET")
		{
			CharacterCustomGetCallBack(req, res);
		}
		else if (req->GetVerb() == "POST")
		{
			CharacterCustomUpdateCallBack(req, res);
		}
	}
}

void UCACCharacterCustomAPI::CharacterCustomGetCall()
{
	this->API = "api/character";

	HttpGetCall();
}

void UCACCharacterCustomAPI::CharacterCustomUpdateCall(TArray<int32> CustomList)
{
	this->API = "api/character";

	FCharacterCustomCreateAPI ApiSendData = FCharacterCustomCreateAPI(CustomList);
	HttpPostCall<FCharacterCustomCreateAPI>(ApiSendData);
}

void UCACCharacterCustomAPI::CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("content type %s"), *res->GetContentType());
	//if (res->GetContentType() == "application/json")
	FString jsonString = res->GetContentAsString();

	FCharacterCustomGetAPI ParseData;
	ParseData = JsonPerse<FCharacterCustomGetAPI>(jsonString);

	OnCharacterCustomGetCallBack(ParseData);
}

void UCACCharacterCustomAPI::CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FCharacterCustomGetAPI ParseData;
	ParseData = JsonPerse<FCharacterCustomGetAPI>(jsonString);
	bool hasCustom = false;
	if (ParseData.characterId)
	{
		hasCustom = true;
		OnCharacterCustomUpdateCallBack(hasCustom);
	}
	OnCharacterCustomUpdateCallBack(hasCustom);
}
