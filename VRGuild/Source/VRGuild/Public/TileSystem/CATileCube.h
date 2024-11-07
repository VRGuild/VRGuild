// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileSystem/CATileSpace.h"
#include "CATileCube.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API ACATileCube : public ACATileSpace
{
	GENERATED_BODY()

public:
	ACATileCube();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* TileMesh;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CreateDefualtSpace() override;

public:
	virtual ACATileSpace* Clone() override;

	virtual void AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace) override;
	virtual void AttachPostision(FVector position, ACATileSpace* newTileSpace) override;

	virtual void Delete() override;

};
