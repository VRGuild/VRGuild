// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileZone.generated.h"

UCLASS()
class VRGUILD_API ACATileZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACATileZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TMap<FVector, class ACATileSpace*> TileSpaces;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsTileSpaceEmpty(FVector position);
	
	virtual class ACATileSpace* CreateNewTile(FVector position);
	virtual bool DeleteTile(FVector position);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	float TileSize = 36;
};
