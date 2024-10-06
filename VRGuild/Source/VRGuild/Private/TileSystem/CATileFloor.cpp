// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileFloor.h"
#include "TileSystem/FL_TileTools.h"
#include "TileSystem/CATileSpace.h"
#include "TileSystem/CWGTileCost.h"

void ACATileFloor::BeginPlay()
{
	this->TileSize = 128;
	Super::BeginPlay();
}

void ACATileFloor::CreateDefualtSpace()
{
	FVector actorPosition = UFL_TileTools::SnapGridVector(this->GetActorLocation(), this->TileSize);
	FVector worldPosition;

	for (int y = -2;  y <= 2 ; y++ )
	{
		for (int x = -2; x <= 2; x++)
		{
			worldPosition = actorPosition + (FVector(x, y, 0) * this->TileSize);
			if ( -1 <= x && x <= 1 && -1 <= y && y <= 1)
				CreateNewTile(UFL_TileTools::SnapGridVector(worldPosition, this->TileSize), ESpaceType::Floor);
			else
				CreateNewTile(UFL_TileTools::SnapGridVector(worldPosition, this->TileSize), ESpaceType::Wall);
		}
	}
}

bool ACATileFloor::InteractionCreate(FVector position, FVector gridRelativeVector)
{
	ACATileSpace** targetSpace = this->TileSpaces.Find(position);

	if (!targetSpace || (*targetSpace)->GetSpaceType() != ESpaceType::Wall)
		return false;
	
	UCWGTileCost* tileCostWidget = CreateWidget<UCWGTileCost>(GetWorld(), TileCostWidgetClass, FName("TileConstWidget"));
	
	if (tileCostWidget)
	{
		tileCostWidget->InitializeSetting(this, ETileCostType::Buy, position, ESpaceType::Floor, 1);
		tileCostWidget->AddToViewport();
		return true;
	}
	return false;
}

void ACATileFloor::OnCreatePass(FVector position, ESpaceType spaceType)
{
	// 벽을 삭제한다
	DeleteTile(position);

	// 바닥을 만든다.
	CreateNewTile(UFL_TileTools::SnapGridVector(position, this->TileSize), ESpaceType::Floor);

	FVector wallPosition;

	// 주변을 벽으로 만든다
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			wallPosition = UFL_TileTools::SnapGridVector(position + (this->TileSize * FVector(x, y, 0)), this->TileSize);
			if (IsTileSpaceEmpty(wallPosition))
			{
				CreateNewTile(UFL_TileTools::SnapGridVector(wallPosition, this->TileSize), ESpaceType::Wall);
			}
		}
	}
}

bool ACATileFloor::InteractionDelete(FVector position)
{
	ACATileSpace** targetSpace = this->TileSpaces.Find(position);

	if (!targetSpace || (*targetSpace)->GetSpaceType() != ESpaceType::Floor)
		return false;

	UCWGTileCost* tileCostWidget = CreateWidget<UCWGTileCost>(GetWorld(), TileCostWidgetClass, FName("TileConstWidget"));

	if (tileCostWidget)
	{
		tileCostWidget->InitializeSetting(this, ETileCostType::Sell, position, ESpaceType::Floor, 10);
		tileCostWidget->AddToViewport();
		return true;
	}
	return false;
}

void ACATileFloor::OnDeletePass(FVector position)
{
	// 바닥을 삭제한다
	DeleteTile(position);

	CreateNewTile(UFL_TileTools::SnapGridVector(position, this->TileSize), ESpaceType::Wall);

	// 나중에 추가 기준 좌표 (0,0,0)으로 오지 못할 경우 길을 삭제할 수 없도록 한다.
	FVector wallPosition;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			wallPosition = UFL_TileTools::SnapGridVector(position + (this->TileSize * FVector(x, y, 0)), this->TileSize);
			if (!IsTileSpaceEmpty(wallPosition) && !HasTypeNearByTile(wallPosition, ESpaceType::Floor))
			{
				DeleteTile(wallPosition);
			}
		}
	}
}