// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACLoginAPI.h"
#include "Global/Server/CPCBasePlayerController.h"
#include "Global/API/CBPLJsonParse.h"
#include "Json.h"
#include "JsonObjectConverter.h"

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

void UCACLoginAPI::LoginPostAPI()
{
	UE_LOG(LogTemp, Display, TEXT("LoginPostAPI"));

	if (bHttpWaitresponse)
		return;
	bHttpWaitresponse = true;

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	FString json = JsonStringfy(Identity->GetAuthToken(0));

	req->SetURL(this->URL);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");
	req->SetContentAsString(json);

	req->OnProcessRequestComplete().BindUObject(this, &UCACLoginAPI::LoginPostAPICallBack);

	req->ProcessRequest();
}

void UCACLoginAPI::LoginPostAPICallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("LoginPostAPICallBack"));
	if (bConnectedSuccessfully)
	{
		FString jsonString = res->GetContentAsString();
		this->HttpResult = jsonString;
		this->HttpStatus = res->GetResponseCode();
		FJsonLogin resultData = JsonPerse(jsonString);

		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			OnLoginAPISuccess(resultData);
		}
	}
	bHttpWaitresponse = false;
}

FString UCACLoginAPI::JsonStringfy(FJsonLogin someStruct)
{
	FString jsonStr = "";
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonLogin>(someStruct);
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return jsonStr;
}

FJsonLogin UCACLoginAPI::JsonPerse(FString someString)
{
	FJsonLogin ParseData;
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(someString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	FJsonObjectConverter::JsonObjectToUStruct<FJsonLogin>(JsonObject.ToSharedRef(), &ParseData);

	return ParseData;
}
