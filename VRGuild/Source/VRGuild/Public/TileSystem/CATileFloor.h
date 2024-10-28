// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLChannel.h"

#include "CoreMinimal.h"
#include "TileSystem/CATileSpace.h"
#include "CATileFloor.generated.h"

enum class ESpaceType : uint8;

/**
 * 
 */
UCLASS()
class VRGUILD_API ACATileFloor : public ACATileSpace
{
	GENERATED_BODY()

public:
	ACATileFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CreateDefualtZone() override;

public:
	virtual void AttachSpace(FVector relativeVector, ACATileSpace* newTileSpace) override;

	virtual void Delete() override;

	void SetTiledata(FChannelnfoCreateAPI* TileInfo);

	// interaction with widget
	//virtual bool InteractionCreate(FVector position, FVector gridRelativeVector) override;

	//virtual void OnCreatePass(FVector position, ESpaceType spaceType) override;

	//virtual bool InteractionDelete(FVector position) override;
	//
	//virtual void OnDeletePass(FVector position) override;
};
