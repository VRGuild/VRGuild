// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACCharacterCustomAPI.h"
#include "Global/CGIGameInstance.h"
#include "Global/API/CBPLJsonParse.h"
UCACCharacterCustomAPI::UCACCharacterCustomAPI()
{
}


void UCACCharacterCustomAPI::CharacterCustomStatusPostCall()
{
	this->URL="http://125.132.216.190:15530/api/character/create";

	UGameInstance* GI = GetWorld()->GetGameInstance();
	UCGIGameInstance* MyGI = Cast<UCGIGameInstance>(GI);
	FCharacterCustomDataAPI ApiSendData = FCharacterCustomDataAPI();

	ApiSendData.status = MyGI->CustomData.Selections;

	HttpPostCall<FCharacterCustomDataAPI>(ApiSendData);
}


void UCACCharacterCustomAPI::CharacterCustomStatusGetCall()
{
	this->URL = "http://125.132.216.190:15530/api/character/info";

	FCharacterInfoGetDataAPI userSendInfo = FCharacterInfoGetDataAPI("userid1132151");
	HttpGetCall<FCharacterInfoGetDataAPI>(userSendInfo);
}


void UCACCharacterCustomAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	if (req->GetURL() == "http://125.132.216.190:15530/api/character/create")
	{
		//OnEpicLoginComple();
	}
	else if (req->GetURL() == "http://125.132.216.190:15530/api/character/info")
	{
		OnGetCustomCharacterData(req,res);
		OnGetCusomCFharacterDataCallBack();
	}

}

void UCACCharacterCustomAPI::OnGetCustomCharacterData(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString resultJsonString = this->HttpResult;

	FCharacterCustomDataAPI ParseData;

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(resultJsonString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	FJsonObjectConverter::JsonObjectToUStruct<FCharacterCustomDataAPI>(JsonObject.ToSharedRef(), &ParseData);


	UGameInstance* GI = GetWorld()->GetGameInstance();
	UCGIGameInstance* MyGI = Cast<UCGIGameInstance>(GI);
	MyGI->CustomData.Selections = ParseData.status;
}

