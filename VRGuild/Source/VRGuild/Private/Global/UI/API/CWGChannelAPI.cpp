// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGChannelAPI.h"
#include "Global/API/BPL/CBPLChannel.h"

void UCWGChannelAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FRegexPattern GetChannelPattern(TEXT(R"(GET\s+/api/channel)"));
	FRegexPattern PostChannelPattern(TEXT(R"(POST\s+/api/channel)"));
	FRegexPattern PatchChannelPattern(TEXT(R"(PATCH\s+/api/channel)"));
	FRegexPattern GetChannelSearchPattern(TEXT(R"(GET\s+/api/channel/([a-zA-Z0-9가-힣-_]+))"));
	FRegexPattern DeleteChannelPattern(TEXT(R"(DELETE\s+/api/channel/([a-zA-Z0-9가-힣-_]+))"));

	// Implementation of routing logic
	FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

	if (FRegexMatcher(GetChannelPattern, UrlToMatch).FindNext())
	{
		ChannelGetCallBack(req, res);
	}
	else if (FRegexMatcher(PostChannelPattern, UrlToMatch).FindNext())
	{
		ChannelPostCallBack(req, res);
	}
	else if (FRegexMatcher(PatchChannelPattern, UrlToMatch).FindNext())
	{
		ChannelPatchCallBack(req, res);
	}
	else if (FRegexMatcher(GetChannelSearchPattern, UrlToMatch).FindNext())
	{
		ChannelSearchIdGetCallBack(req, res);
	}
	else if (FRegexMatcher(DeleteChannelPattern, UrlToMatch).FindNext())
	{
		ChannelSearchIdDeleteCallBack(req, res);
	}
}

void UCWGChannelAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FRegexPattern GetChannelPattern(TEXT(R"(GET\s+/api/channel)"));
	FRegexPattern PostChannelPattern(TEXT(R"(POST\s+/api/channel)"));
	FRegexPattern PatchChannelPattern(TEXT(R"(PATCH\s+/api/channel)"));
	FRegexPattern GetChannelSearchPattern(TEXT(R"(GET\s+/api/channel/([a-zA-Z0-9가-힣-_]+))"));
	FRegexPattern DeleteChannelPattern(TEXT(R"(DELETE\s+/api/channel/([a-zA-Z0-9가-힣-_]+))"));

	// Implementation of routing logic
	FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

	if (FRegexMatcher(GetChannelPattern, UrlToMatch).FindNext())
	{
		OnFailChannelGetCallBack();
	}
	else if (FRegexMatcher(PostChannelPattern, UrlToMatch).FindNext())
	{
		OnFailChannelPostCallBack();
	}
	else if (FRegexMatcher(PatchChannelPattern, UrlToMatch).FindNext())
	{
		OnFailChannelPatchCallBack();
	}
	else if (FRegexMatcher(GetChannelSearchPattern, UrlToMatch).FindNext())
	{
		OnFailChannelSearchIdGetCallBack();
	}
	else if (FRegexMatcher(DeleteChannelPattern, UrlToMatch).FindNext())
	{
		OnFailChannelSearchIdDeleteCallBack();
	}
}

void UCWGChannelAPI::ChannelGetCall()
{
	this->API = "api/channel";

	HttpGetCall();
}

void UCWGChannelAPI::ChannelGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataListAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataListAPI>(jsonString);
	OnChannelGetCallBack(ParseData);
}

void UCWGChannelAPI::ChannelPostCall(FChannelnfoCreateAPI TileData)
{
	this->API = "api/channel";

	HttpPostCall<FChannelnfoCreateAPI>(TileData);
}

void UCWGChannelAPI::ChannelPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelPostCallBack(ParseData.Data);
}

void UCWGChannelAPI::ChannelPatchCall(FChannelInfoUpdateAPI TileData)
{
	this->API = "api/channel";

	HttpPatchCall<FChannelInfoUpdateAPI>(TileData);
}

void UCWGChannelAPI::ChannelPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelPatchCallBack(ParseData.Data);
}

void UCWGChannelAPI::ChannelSearchIdGetCall(FString channeld)
{
	this->API = "api/channel/" + channeld;

	HttpGetCall();
}

void UCWGChannelAPI::ChannelSearchIdGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelSearchIdGetCallBack(ParseData.Data);
}

void UCWGChannelAPI::ChannelSearchIdDeleteCall(FString channeld)
{
	this->API = "api/channel/" + channeld;

	HttpDeleteCall();
}

void UCWGChannelAPI::ChannelSearchIdDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnChannelSearchIdDeleteCallBack();
}

TArray<FTileInfo> UCWGChannelAPI::DefaultTile()
{
	TArray<FTileInfo> defaulTileMap;

	FTileInfo tempTileInfo;

	for (int x = -3; x <= 3; x++)
	{
		for (int y = -3; y <= 3; y++)
		{
			tempTileInfo.TileList = FVector(x, y, 0);
			tempTileInfo.type = 0;
			defaulTileMap.Add(tempTileInfo);
			if (x == 3 || x == -3 || y == 3 || y == -3)
			{
				for (int z = 1; z <= 5; z++)
				{

					tempTileInfo.TileList = FVector(x, y, z);
					tempTileInfo.type = 0;
					defaulTileMap.Add(tempTileInfo);
				}
			}
		}
	}

	return defaulTileMap;
}
