// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileZone.h"
#include "TileSystem/CATileSpace.h"
#include <TileSystem/FL_TileTools.h>
#include "Blueprint/UserWidget.h"

// Sets default values
ACATileZone::ACATileZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileSpaces = TMap<FVector, ACATileSpace*>();

	static ConstructorHelpers::FClassFinder<UUserWidget> tempWidget(TEXT("/Game/TileSystem/UI/BPW_TileCost.BPW_TileCost"));
	if (tempWidget.Succeeded())
	{
		this->TileCostWidgetClass = tempWidget.Class;
	}

}

// Called when the game starts or when spawned
void ACATileZone::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDefualtSpace();
}

void ACATileZone::CreateDefualtSpace()
{
	CreateNewTile(UFL_TileTools::SnapGridVector(this->GetActorLocation(), this->TileSize));
}

// Called every frame
void ACATileZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACATileZone::IsTileSpaceEmpty(FVector position)
{
	ACATileSpace** isValied = this->TileSpaces.Find(position);
	if (isValied)
		return false;
	return true;
}

ACATileSpace* ACATileZone::CreateNewTile(FVector position)
{
	ACATileSpace** isValied = this->TileSpaces.Find(position);

	if (isValied)
	{
		UE_LOG(LogTemp, Display, TEXT("Some Block in there"));
		return nullptr;
	}
	this->TileSpaces.Add(position, GetWorld()->SpawnActor<ACATileSpace>(ACATileSpace::StaticClass()));
	this->TileSpaces[position]->Initialize(this, position);
	return this->TileSpaces[position];
}

ACATileSpace* ACATileZone::CreateNewTile(FVector position, ESpaceType spacetype)
{
	ACATileSpace* newSpaceTile = CreateNewTile(position);
	if (spacetype == ESpaceType::Wall)
		newSpaceTile->SetActorScale3D(newSpaceTile->GetActorScale() + (FVector(0, 0, 1) * 1.5 * this->TileSize));
	if (newSpaceTile)
		newSpaceTile->SetSpaceType(spacetype);
	UE_LOG(LogTemp, Display, TEXT("Create Tile %s") , *position.ToString());
	return newSpaceTile;
}

bool ACATileZone::DeleteTile(FVector position)
{
	ACATileSpace** isValied = this->TileSpaces.Find(position);

	if (isValied)
	{
		ACATileSpace* targetTile = this->TileSpaces[position];
		this->TileSpaces.Remove(position);
		targetTile->Destroy(); // 로직이 다돌고 사라지기 때문에 괜찮은듯?
		return true;
	}
	return false;
}

bool ACATileZone::HasTypeNearByTile(FVector position, ESpaceType spaceType)
{
	FVector nearPosition;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			nearPosition = UFL_TileTools::SnapGridVector(position + (this->TileSize * FVector(x, y, 0)), this->TileSize);
			if (!IsTileSpaceEmpty(nearPosition) && this->TileSpaces[nearPosition]->GetSpaceType() == spaceType)
			{
				return true;
			}
		}
	}
	return false;
}

bool ACATileZone::InteractionCreate(FVector position, FVector gridRelativeVector)
{
	if (!IsTileSpaceEmpty(position + gridRelativeVector))
		return false;

	OnCreatePass(position + gridRelativeVector, ESpaceType::None);
	return true;
}

void ACATileZone::OnCreatePass(FVector position, ESpaceType spaceType)
{
	CreateNewTile(position, spaceType);
}

bool ACATileZone::InteractionDelete(FVector position)
{
	if (IsTileSpaceEmpty(position))
		return false;

	OnDeletePass(position);
	return true;
}


void ACATileZone::OnDeletePass(FVector position)
{
	DeleteTile(position);
}
