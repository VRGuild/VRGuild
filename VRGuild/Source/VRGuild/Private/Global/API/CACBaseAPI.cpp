// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACBaseAPI.h"
#include "Global/API/CBPLJsonParse.h"

// Sets default values for this component's properties
UCACBaseAPI::UCACBaseAPI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCACBaseAPI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCACBaseAPI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


template<typename T>
void UCACBaseAPI::HttpPostCall(T sendData)
{
	UE_LOG(LogTemp, Display, TEXT("HttpPostLoginCall"));
	FHttpModule& httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	FString json = UCBPLJsonParse::JsonPerse<T>(sendData);

	req->SetURL(this->URL);
	req->SetVerb("POST");
	req->SetHeader("content-type", "application/json");
	req->SetContentAsString(json);

	req->OnProcessRequestComplete().BindUObject(this, &UCACBaseAPI::HttpPostCallBack);

	req->ProcessRequest();
}

void UCACBaseAPI::HttpPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("OnResHttpPostLoginCallBack"));
	if (bConnectedSuccessfully)
	{
		FString jsonString = res->GetContentAsString();
		this->HttpResult = jsonString;
		this->HttpStatus = res->GetResponseCode();

		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			HttpSuccessLogic();
		}
	}
	bHttpWaitresponse = false;
}
