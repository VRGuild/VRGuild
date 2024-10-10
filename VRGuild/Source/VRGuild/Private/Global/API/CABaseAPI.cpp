// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CABaseAPI.h"
#include "Global/API/CBPLJsonParse.h"
#include "Json.h"
#include "JsonObjectConverter.h"

// Sets default values
ACABaseAPI::ACABaseAPI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACABaseAPI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACABaseAPI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


template<typename T>
void ACABaseAPI::HttpPostCall(T sendData)
{
	UE_LOG(LogTemp, Display, TEXT("HttpPostLoginCall"));
	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	FString json = UCBPLJsonParse::JsonPerse<T>(sendData);

	req->SetURL(this->URL);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");
	req->SetContentAsString(json);

	req->OnProcessRequestComplete().BindUObject(this, &ACABaseAPI::HttpPostCallBack);

	req->ProcessRequest();
}

void ACABaseAPI::HttpPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("OnResHttpPostLoginCallBack"));
	if (bConnectedSuccessfully)
	{
		FString result = res->GetContentAsString();
		this->HttpResult = result;
		this->HttpStatus = res->GetResponseCode();

		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			HttpSuccessLogic();
		}
	}
	bHttpWaitResponse = false;
}
