// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGChannelAPI.h"
#include "Global/API/BPL/CBPLChannel.h"

void UCWGChannelAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FRegexPattern RegisterChannelPattern(TEXT(R"(POST\s+/api/channel/([^/]+))"));
	FRegexPattern GetChannelInfoPattern(TEXT(R"(GET\s+/api/channel/([^/]+))"));
	FRegexPattern UpdateChannelPattern(TEXT(R"(PUT\s+/api/channel/([^/]+))"));
	FRegexPattern DeleteChannelPattern(TEXT(R"(DELETE\s+/api/channel/([^/]+))"));

	FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

	if (FRegexMatcher(RegisterChannelPattern, UrlToMatch).FindNext())
	{
		RegisterChannelCallBack(req, res);
	}
	else if (FRegexMatcher(GetChannelInfoPattern, UrlToMatch).FindNext())
	{
		GetChannelInfoCallBack(req, res);
	}
	else if (FRegexMatcher(UpdateChannelPattern, UrlToMatch).FindNext())
	{
		UpdateChannelCallBack(req, res);
	}
	else if (FRegexMatcher(DeleteChannelPattern, UrlToMatch).FindNext())
	{
		DeleteChannelCallBack(req, res);
	}
}

void UCWGChannelAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FRegexPattern RegisterChannelPattern(TEXT(R"(POST\s+/api/channel/([^/]+))"));
	FRegexPattern GetChannelInfoPattern(TEXT(R"(GET\s+/api/channel/([^/]+))"));
	FRegexPattern UpdateChannelPattern(TEXT(R"(PUT\s+/api/channel/([^/]+))"));
	FRegexPattern DeleteChannelPattern(TEXT(R"(DELETE\s+/api/channel/([^/]+))"));

	FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

	if (FRegexMatcher(RegisterChannelPattern, UrlToMatch).FindNext())
	{
		OnFailRegisterChannelCallBack();
	}
	else if (FRegexMatcher(GetChannelInfoPattern, UrlToMatch).FindNext())
	{
		OnFailGetChannelInfoCallBack();
	}
	else if (FRegexMatcher(UpdateChannelPattern, UrlToMatch).FindNext())
	{
		OnFailUpdateChannelCallBack();
	}
	else if (FRegexMatcher(DeleteChannelPattern, UrlToMatch).FindNext())
	{
		OnFailDeleteChannelCallBack();
	}
}

// Register Channel Implementation
void UCWGChannelAPI::RegisterChannelCall(const FString& accountId, const FChannelnfoCreateAPI& ChannelData)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *accountId);
	HttpPostCall<FChannelnfoCreateAPI>(ChannelData);
}

void UCWGChannelAPI::RegisterChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnRegisterChannelCallBack(ParseData.Data);
}

// Get Channel Info Implementation
void UCWGChannelAPI::GetChannelInfoCall(const FString& channelId)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpGetCall();
}

void UCWGChannelAPI::GetChannelInfoCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnGetChannelInfoCallBack(ParseData.Data);
}

// Update Channel Implementation
void UCWGChannelAPI::UpdateChannelCall(const FString& channelId, const FChannelInfoUpdateAPI& ChannelData)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpPutCall<FChannelInfoUpdateAPI>(ChannelData);
}

void UCWGChannelAPI::UpdateChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnUpdateChannelCallBack(ParseData.Data);
}

// Delete Channel Implementation
void UCWGChannelAPI::DeleteChannelCall(const FString& channelId)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpDeleteCall();
}

void UCWGChannelAPI::DeleteChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnDeleteChannelCallBack();
}

TArray<FTileInfo> UCWGChannelAPI::DefaultTile()
{
	TArray<FTileInfo> defaultTileMap;
	return defaultTileMap;
}