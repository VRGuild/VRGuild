// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/CACTileAPI.h"
#include "Global/Server/CPCBasePlayerController.h"

UCACTileAPI::UCACTileAPI()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	this->URL = "http://localhost:3000/api/tile";
}

void UCACTileAPI::BeginPlay()
{
	Super::BeginPlay();
}

void UCACTileAPI::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerPlayerController = nullptr;
	if (Owner->IsA<ACPCBasePlayerController>())
	{
		OwnerPlayerController = Cast<ACPCBasePlayerController>(this->Owner);
	}
}

void UCACTileAPI::TilePostCall()
{
	FJsonZone tileZoneData;
	tileZoneData.TilesData.Add(FJsonTile(FVector(0)));

	HttpPostCall<FJsonZone>(tileZoneData);
}

void UCACTileAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	OnTileZoneDataUpdateComple();
}
