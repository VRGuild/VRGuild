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

private:
	FString URL = "http://125.132.216.190:15530/"; // Base URL

public:	
	// Sets default values for this component's properties
	UCACBaseAPI();

	UPROPERTY(EditDefaultsOnly, Category = "API")
	FString API = "";

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	bool bHttpWaitResponse = false;

	AActor* Owner;

public:	
	UPROPERTY(BlueprintReadOnly)
	FString OAuthToken;

	void SetOAuthToken();// { OAuthToken = "Bearer " + token; };

	bool CheckCallBackAPI(FHttpRequestPtr req, FString api);

	template<typename T>
	void HttpJsonContentTypeCall(T sendData, FString Verb) {
		UE_LOG(LogTemp, Display, TEXT("HttpJsonContentTypeCall"));
		if (bHttpWaitResponse)
			return;
		bHttpWaitResponse = true;

		FHttpModule& httpModule = FHttpModule::Get();

		TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

		FString jsonStr = JsonStringfy<T>(sendData);

		SetOAuthToken();

		req->SetURL(this->URL + this->API);
		req->SetVerb(Verb);
		req->SetHeader("content-type", "application/json");
		if (!OAuthToken.IsEmpty())
			req->SetHeader("Authorization", "Bearer " + OAuthToken);
		req->SetContentAsString(jsonStr);

		req->OnProcessRequestComplete().BindUObject(this, &UCACBaseAPI::HttpCallBack);

		req->ProcessRequest();
	};

	void HttpJsonContentTypeCall(FString Verb) {
		UE_LOG(LogTemp, Display, TEXT("HttpJsonContentTypeCall"));
		if (bHttpWaitResponse)
			return;
		bHttpWaitResponse = true;

		FHttpModule& httpModule = FHttpModule::Get();

		TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

		SetOAuthToken();

		req->SetURL(this->URL + this->API);
		req->SetVerb(Verb);
		req->SetHeader("content-type", "application/json");
		if (!OAuthToken.IsEmpty())
			req->SetHeader("Authorization", "Bearer " + OAuthToken);;

		req->OnProcessRequestComplete().BindUObject(this, &UCACBaseAPI::HttpCallBack);

		req->ProcessRequest();
	};

	void HttpGetCall() {
		UE_LOG(LogTemp, Display, TEXT("HttpGetCall"));
		HttpJsonContentTypeCall("GET");
	};

	template<typename T>
	void HttpPostCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpPostCall"));
		HttpJsonContentTypeCall<T>(sendData, "POST");
	};

	template<typename T>
	void HttpDeleteCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpDeleteCall"));
		HttpJsonContentTypeCall<T>(sendData, "DELETE");
	};

	void HttpDeleteCall() {
		UE_LOG(LogTemp, Display, TEXT("HttpDeleteCall"));
		HttpJsonContentTypeCall("DELETE");
	};

	template<typename T>
	void HttpPatchCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpPatchCall"));
		HttpJsonContentTypeCall<T>(sendData, "PATCH");
	};

	void HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res);
	virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res);

	template <typename T>
	FString JsonStringfy(T someStruct)
	{
		FString jsonStr = "";
		TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<T>(someStruct);
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

		return jsonStr;
	};

	template <typename T>
	T JsonPerse(FString someString) {
		T ParseData;
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(someString);

		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		FJsonObjectConverter::JsonObjectToUStruct<T>(JsonObject.ToSharedRef(), &ParseData);

		return ParseData;
	};
};

