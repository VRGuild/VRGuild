// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileZone.generated.h"

enum class ESpaceType : uint8;

UCLASS()
class VRGUILD_API ACATileZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACATileZone();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> TileCostWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	float TileSize = 36;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CreateDefualtSpace();

	TMap<FVector, class ACATileSpace*> TileSpaces;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsTileSpaceEmpty(FVector position);

	virtual class ACATileSpace* CreateNewTile(FVector position);
	virtual class ACATileSpace* CreateNewTile(FVector position, ESpaceType spaceType);

	virtual bool DeleteTile(FVector position);
	virtual bool HasTypeNearByTile(FVector position, ESpaceType spaceType);


	// interaction with widget
	virtual bool InteractionCreate(FVector position, FVector gridRelativeVector);
	UFUNCTION(BlueprintCallable)
	virtual void OnCreatePass(FVector position, ESpaceType spaceType);

	virtual bool InteractionDelete(FVector position);
	UFUNCTION(BlueprintCallable)
	virtual void OnDeletePass(FVector position);
};
