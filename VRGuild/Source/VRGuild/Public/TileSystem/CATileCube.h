// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileSystem/CATileSpace.h"
#include "CATileCube.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API ACATileCube : public AActor
{
	GENERATED_BODY()



protected:
	/*UStaticMeshComponent* TileSpaceMesh;

	UMaterialInstance* TileBaseMat;
	UMaterialInstance* TileOpacityMat;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CreateDefualtSpace() override;

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetTileSpaceMesh() const { return TileSpaceMesh; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UMaterialInstance* GetTileBaseMat() const { return TileBaseMat; }

	virtual ACATileSpace* Clone() override;

	virtual void AttachSpace(FVector relativeVector, ACATileSpace* newTileSpace) override;

	virtual void Delete() override*/


};
