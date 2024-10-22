// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGCharacterCustomAPI.h"
#include "Global/API/BPL/CBPLCharacterCustom.h"


void UCWGCharacterCustomAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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

void UCWGCharacterCustomAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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

void UCWGCharacterCustomAPI::CharacterCustomGetCall()
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomGetCall"));
	this->API = "api/character";

	HttpGetCall();
}

void UCWGCharacterCustomAPI::CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomGetCallBack"));
	FString jsonString = res->GetContentAsString();

	FCharacterCustomInfo ParseData;
	ParseData = JsonPerse<FCharacterCustomInfo>(jsonString);

	OnCharacterCustomGetCallBack(ParseData);
}

void UCWGCharacterCustomAPI::CharacterCustomCreateCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomCreateCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpPostCall<FCharacterCustomCreate>(ApiSendData);
}

void UCWGCharacterCustomAPI::CharacterCustomCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomCreateCallBack"));
	FString jsonString = res->GetContentAsString();
	FCharacterCustomInfo ParseData;
	ParseData = JsonPerse<FCharacterCustomInfo>(jsonString);
	OnCharacterCustomCreateCallBack(ParseData);
}


void UCWGCharacterCustomAPI::CharacterCustomUpdateCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomUpdateCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpPatchCall<FCharacterCustomCreate>(ApiSendData);
}


void UCWGCharacterCustomAPI::CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomUpdateCallBack"));
	FString jsonString = res->GetContentAsString();
	FCharacterCustomInfo ParseData;
	ParseData = JsonPerse<FCharacterCustomInfo>(jsonString);

	OnCharacterCustomUpdateCallBack(ParseData);
}

void UCWGCharacterCustomAPI::CharacterCustomDeleteCall(TArray<int32> CustomList)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomDeleteCall"));
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpDeleteCall();
}

void UCWGCharacterCustomAPI::CharacterCustomDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("CharacterCustomDeleteCallBack"));
	OnCharacterCustomDeleteCallBack();
}

