// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Json.h"
#include "JsonObjectConverter.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLJsonParse.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCBPLJsonParse : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:	
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
