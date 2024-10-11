// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACBaseAPI.h"

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

// Called every frame
void UCACBaseAPI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCACBaseAPI::HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("HttpPostCallBack"));
	if (bConnectedSuccessfully)
	{
		FString jsonString = res->GetContentAsString();
		this->HttpResult = jsonString;
		this->HttpStatus = res->GetResponseCode();

		if (res->GetResponseCode() == 200)
		{
			//성공 했을때 동작 추가
			OnSuccessAPI();
		}
	}
	bHttpWaitResponse = false;
};

void UCACBaseAPI::OnSuccessAPI()
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI %s"), *this->HttpResult);
}
