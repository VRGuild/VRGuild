// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACCharacterCustomAPI.h"
#include "Global/API/BPL/CBPLCharacterCustom.h"

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
	UE_LOG(LogTemp, Display, TEXT("Token : %s \n"), *this->OAuthToken);
	if (this->CheckCallBackAPI(req, "api/character"))
	{
		FString Verb = req->GetVerb();
		if (Verb == "GET")
		{
			CharacterCustomGetCallBack(req, res);
		}
		else if (Verb == "POST")
		{
			CharacterCustomCreateCallBack(req, res);
		}
		else if (Verb == "FETCH")
		{
			CharacterCustomUpdateCallBack(req, res);
		}
		else if (Verb == "DELETE")
		{
			CharacterCustomDeleteCallBack(req, res);
		}
	}
}

void UCACCharacterCustomAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
	UE_LOG(LogTemp, Display, TEXT("Token : %s \n"), *this->OAuthToken);
	if (this->CheckCallBackAPI(req, "api/character"))
	{
		FString Verb = req->GetVerb();
		if (Verb == "GET")
		{
			OnFailCharacterCustomGetCallBack();
		}
		else if (Verb == "POST")
		{
			OnFailCharacterCustomCreateCallBack();
		}
		else if (Verb == "FETCH")
		{
			OnFailCharacterCustomUpdateCallBack();
		}
		else if (Verb == "DELETE")
		{
			OnFailCharacterCustomDeleteCallBack();
		}
	}
}

void UCACCharacterCustomAPI::CharacterCustomGetCall()
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomGetCall"));
	this->API = "api/character";

	HttpGetCall();
}

void UCACCharacterCustomAPI::CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomGetCallBack"));
	FString jsonString = res->GetContentAsString();

	FCharacterCustomInfoData ParseData;
	ParseData = JsonPerse<FCharacterCustomInfoData>(jsonString);

	OnCharacterCustomGetCallBack(ParseData.data);
}

void UCACCharacterCustomAPI::CharacterCustomCreateCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomCreateCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpPostCall<FCharacterCustomCreate>(ApiSendData);
}

void UCACCharacterCustomAPI::CharacterCustomCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomCreateCallBack"));
	FString jsonString = res->GetContentAsString();
	FCharacterCustomInfo ParseData;
	ParseData = JsonPerse<FCharacterCustomInfo>(jsonString);
	OnCharacterCustomCreateCallBack(ParseData);
}

void UCACCharacterCustomAPI::CharacterCustomUpdateCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomUpdateCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpPatchCall<FCharacterCustomCreate>(ApiSendData);
}

void UCACCharacterCustomAPI::CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomUpdateCallBack"));
	FString jsonString = res->GetContentAsString();
	FCharacterCustomInfo ParseData;
	ParseData = JsonPerse<FCharacterCustomInfo>(jsonString);

	OnCharacterCustomUpdateCallBack(ParseData);
}

void UCACCharacterCustomAPI::CharacterCustomDeleteCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomDeleteCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpDeleteCall();
}

void UCACCharacterCustomAPI::CharacterCustomDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomDeleteCallBack"));
	OnCharacterCustomDeleteCallBack();
}
