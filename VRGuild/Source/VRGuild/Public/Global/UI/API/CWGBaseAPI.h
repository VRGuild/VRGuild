﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Json.h"
#include "JsonObjectConverter.h"
#include "Global/API/CBPLJsonParse.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWGBaseAPI.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGBaseAPI : public UUserWidget
{
	GENERATED_BODY()


protected:
	bool bHttpWaitResponse = false;

public:
	UPROPERTY(EditDefaultsOnly, Category = "API")
	FString URL = "";

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatus;

	UPROPERTY(BlueprintReadOnly)
	FString HttpResult;

	UPROPERTY(BlueprintReadOnly)
	FString OAuthToken;

	void SetOAuthToken();// { OAuthToken = "Bearer " + token; };

	template<typename T>
	void HttpJsonContentTypeCall(T sendData, FString Verb) {
		UE_LOG(LogTemp, Display, TEXT("HttpJsonContentTypeCall"));
		if (bHttpWaitResponse)
			return;
		bHttpWaitResponse = true;

		FHttpModule& httpModule = FHttpModule::Get();

		TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

		FString jsonStr = "";
		TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<T>(sendData);
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

		SetOAuthToken();

		req->SetURL(this->URL);
		req->SetVerb(Verb);
		req->SetHeader("content-type", "application/json");
		if (!OAuthToken.IsEmpty())
			req->SetHeader("Authorization", "Bearer " + OAuthToken);
		req->SetContentAsString(jsonStr);

		req->OnProcessRequestComplete().BindUObject(this, &UCWGBaseAPI::HttpCallBack);

		req->ProcessRequest();
	};

	template<typename T>
	void HttpGetCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpGetCall"));
		if (bHttpWaitResponse)
			return;
		bHttpWaitResponse = true;

		FHttpModule& httpModule = FHttpModule::Get();

		TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

		SetOAuthToken();

		req->SetURL(this->URL);
		req->SetVerb("GET");
		req->SetHeader("content-type", "application/json");
		if (!OAuthToken.IsEmpty())
			req->SetHeader("Authorization", "Bearer " + OAuthToken);;

		req->OnProcessRequestComplete().BindUObject(this, &UCWGBaseAPI::HttpCallBack);

		req->ProcessRequest();
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

	template<typename T>
	void HttpPatchCall(T sendData) {
		UE_LOG(LogTemp, Display, TEXT("HttpPatchCall"));
		HttpJsonContentTypeCall<T>(sendData, "PATCH");
	};

	void HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully);

	virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res);

};
