// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileSystem/CATileZone.h"
#include "CATileFloor.generated.h"

enum class ESpaceType : uint8;

/**
 * 
 */
UCLASS()
class VRGUILD_API ACATileFloor : public ACATileZone
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CreateDefualtSpace() override;

public:

	// interaction with widget
	virtual bool InteractionCreate(FVector position, FVector gridRelativeVector) override;

	virtual void OnCreatePass(FVector position, ESpaceType spaceType) override;

	virtual bool InteractionDelete(FVector position) override;
	
	virtual void OnDeletePass(FVector position) override;
};
