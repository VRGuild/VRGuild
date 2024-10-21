// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGCharacterCustomAPI.h"
#include "Global/CGIGameInstance.h"

void UCWGCharacterCustomAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s \n"), *req->GetURL());
	UE_LOG(LogTemp, Display, TEXT("Token : %s \n"), *this->OAuthToken);
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

void UCWGCharacterCustomAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI : %s \n"), *req->GetURL());
	UE_LOG(LogTemp, Display, TEXT("Token : %s \n"), *this->OAuthToken);
	if (this->CheckCallBackAPI(req, "api/character"))
	{
		if (req->GetVerb() == "GET")
		{
			OnFailCharacterCustomGetCallBack();
		}
		else if (req->GetVerb() == "POST")
		{
			OnFailCharacterCustomUpdateCallBack();
		}
	}
}

void UCWGCharacterCustomAPI::CharacterCustomGetCall()
{
	this->API = "api/character";

	HttpGetCall();
}

void UCWGCharacterCustomAPI::CharacterCustomUpdateCall(TArray<int32> CustomList)
{
	this->API = "api/character";

	FCharacterCustomCreate ApiSendData = FCharacterCustomCreate(CustomList);
	HttpPostCall<FCharacterCustomCreate>(ApiSendData);
}

void UCWGCharacterCustomAPI::CharacterCustomGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("content type %s"), *res->GetContentType());
	//if (res->GetContentType() == "application/json")
	FString jsonString = res->GetContentAsString();

	FCharacterCustomGet ParseData;
	ParseData = JsonPerse<FCharacterCustomGet>(jsonString);

	OnCharacterCustomGetCallBack(ParseData);
}

void UCWGCharacterCustomAPI::CharacterCustomUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FCharacterCustomGet ParseData;
	ParseData = JsonPerse<FCharacterCustomGet>(jsonString);
	bool hasCustom =false;
	if (ParseData.characterId)
	{
		hasCustom = true;
		OnCharacterCustomUpdateCallBack(hasCustom);
	}
	OnCharacterCustomUpdateCallBack(hasCustom);
}

