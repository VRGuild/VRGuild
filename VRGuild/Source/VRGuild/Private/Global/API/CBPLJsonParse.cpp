// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CBPLJsonParse.h"
#include "Json.h"
#include "JsonObjectConverter.h"

template<typename T>
FString UCBPLJsonParse::JsonStringfy(T someStruct)
{
	FString jsonStr = "";
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject<T>(someStruct);
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return jsonStr;
}

template<typename T>
T UCBPLJsonParse::JsonPerse(FString someString)
{
	T ParseData;
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(someString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	FJsonObjectConverter::JsonObjectToUStruct<T>(JsonObject.ToSharedRef(), &ParseData);

	return ParseData;
}
