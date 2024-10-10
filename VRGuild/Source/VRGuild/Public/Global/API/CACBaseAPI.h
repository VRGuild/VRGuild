// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Json.h"
#include "JsonObjectConverter.h"
#include "Global/API/CBPLJsonParse.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACBaseAPI.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACBaseAPI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACBaseAPI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	bool bHttpWaitResponse = false;

	AActor* Owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "API")
	FString URL = "";

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatus;

	UPROPERTY(BlueprintReadOnly)
	FString HttpResult;

	template<typename T>
	void HttpPostCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpPostLoginCall"));
		if (bHttpWaitResponse)
			return;
		bHttpWaitResponse = true;

		FHttpModule& httpModule = FHttpModule::Get();

		TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

		FString jsonStr = "";
		TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<T>(sendData);
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

		req->SetURL(this->URL);
		req->SetVerb("POST");
		req->SetHeader("content-type", "application/json");
		req->SetContentAsString(jsonStr);

		req->OnProcessRequestComplete().BindUObject(this, &UCACBaseAPI::HttpPostCallBack);

		req->ProcessRequest();
	};

	void HttpPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	virtual void OnSuccessAPI();
};

