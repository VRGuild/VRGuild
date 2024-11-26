// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/API/CACChannelAPI.h"
#include "Global/API/BPL/CBPLChannel.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACChannelAPI::UCACChannelAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACChannelAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACChannelAPI::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerPlayerController = nullptr;
	if (Owner->IsA<ACPCBasePlayerController>())
	{
		OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
	}
}

void UCACChannelAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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

void UCACChannelAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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
void UCACChannelAPI::RegisterChannelCall(const FString& accountId, const FChannelnfoCreateAPI& ChannelData)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *accountId);
	HttpPostCall<FChannelnfoCreateAPI>(ChannelData);
}

void UCACChannelAPI::RegisterChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnRegisterChannelCallBack(ParseData.Data);
}

// Get Channel Info Implementation
void UCACChannelAPI::GetChannelInfoCall(const FString& channelId)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpGetCall();
}

void UCACChannelAPI::GetChannelInfoCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnGetChannelInfoCallBack(ParseData.Data);
}

// Update Channel Implementation
void UCACChannelAPI::UpdateChannelCall(const FString& channelId, const FChannelInfoUpdateAPI& ChannelData)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpPutCall<FChannelInfoUpdateAPI>(ChannelData);
}

void UCACChannelAPI::UpdateChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnUpdateChannelCallBack(ParseData.Data);
}

// Delete Channel Implementation
void UCACChannelAPI::DeleteChannelCall(const FString& channelId)
{
	this->API = FString::Printf(TEXT("api/channel/%s"), *channelId);
	HttpDeleteCall();
}

void UCACChannelAPI::DeleteChannelCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnDeleteChannelCallBack();
}

TArray<FTileInfo> UCACChannelAPI::DefaultTile()
{
	TArray<FTileInfo> defaultTileMap;
	return defaultTileMap;
}

/*

#include "Global/API/CACChannelAPI.h"
#include "Global/API/BPL/CBPLChannel.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACChannelAPI::UCACChannelAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCACChannelAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACChannelAPI::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerPlayerController = nullptr;
	if (Owner->IsA<ACPCBasePlayerController>())
	{
		OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
	}
}


void UCACChannelAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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

void UCACChannelAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
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

void UCACChannelAPI::ChannelGetCall()
{
	this->API = "api/channel";

	HttpGetCall();
}

void UCACChannelAPI::ChannelGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataListAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataListAPI>(jsonString);
	OnChannelGetCallBack(ParseData);
}

void UCACChannelAPI::ChannelPostCall(FChannelnfoCreateAPI TileData)
{
	this->API = "api/channel";

	HttpPostCall<FChannelnfoCreateAPI>(TileData);
}

void UCACChannelAPI::ChannelPostCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelPostCallBack(ParseData.Data);
}

void UCACChannelAPI::ChannelPatchCall(FChannelInfoUpdateAPI TileData)
{
	this->API = "api/channel";

	HttpPatchCall<FChannelInfoUpdateAPI>(TileData);
}

void UCACChannelAPI::ChannelPatchCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelPatchCallBack(ParseData.Data);
}

void UCACChannelAPI::ChannelSearchIdGetCall(FString channeld)
{
	this->API = "api/channel/" + channeld;

	HttpGetCall();
}

void UCACChannelAPI::ChannelSearchIdGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	FString jsonString = res->GetContentAsString();
	FChannelInfoDataAPI ParseData;
	ParseData = JsonPerse<FChannelInfoDataAPI>(jsonString);
	OnChannelSearchIdGetCallBack(ParseData.Data);
}

void UCACChannelAPI::ChannelSearchIdDeleteCall(FString channeld)
{
	this->API = "api/channel/" + channeld;

	HttpDeleteCall();
}

void UCACChannelAPI::ChannelSearchIdDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnChannelSearchIdDeleteCallBack();
}

TArray<FTileInfo> UCACChannelAPI::DefaultTile()
{
	TArray<FTileInfo> defaulTileMap;

	FTileInfo tempTileInfo;

	for (int x = -3; x <= 3; x++)
	{
		for (int y = -3; y <= 3; y++)
		{
		}
	}

	return defaulTileMap;
}
*/