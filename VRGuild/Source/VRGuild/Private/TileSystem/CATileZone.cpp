// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileZone.h"
#include "TileSystem/CATileSpace.h"
#include <TileSystem/FL_TileTools.h>

// Sets default values
ACATileZone::ACATileZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileSpaces = TMap<FVector, ACATileSpace*>();
}

// Called when the game starts or when spawned
void ACATileZone::BeginPlay()
{
	Super::BeginPlay();

	CreateNewTile(UFL_TileTools::SnapGridVector(this->GetActorLocation(), this->TileSize));
}

// Called every frame
void ACATileZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACATileZone::IsTileSpaceEmpty(FVector position)
{
	if (this->TileSpaces.Find(position))
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

bool ACATileZone::DeleteTile(FVector position)
{
	ACATileSpace** isValied = this->TileSpaces.Find(position);

	if (isValied)
	{
		this->TileSpaces.Remove(position);
		return true;
	}

	return false;
}

