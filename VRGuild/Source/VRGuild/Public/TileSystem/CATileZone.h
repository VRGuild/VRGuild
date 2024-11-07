// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FL_TileTools.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileZone.generated.h"

USTRUCT()
struct FTileSpaceData
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	ACATileSpace* TileSpace;

	FTileSpaceData() : Position(FVector::ZeroVector), TileSpace(nullptr) {}
	FTileSpaceData(FVector InPosition, ACATileSpace* InTileSpace)
		: Position(InPosition), TileSpace(InTileSpace) {}
};

UCLASS()
class VRGUILD_API ACATileZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACATileZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 TileSize = 1;

	int32 MaxTilePostion = TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ESpaceType SpaceType = ESpaceType::None;

	bool bRPCWait = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void CreateDefualtSpace();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	TMap<FVector, class ACATileSpace*> TileSpacesMap;

	virtual void OnRep_Owner() override;

	FVector SendDataPosition;

	class ACATileSpace* SendDataNewTile;

	TSubclassOf<class ACATileSpace> SendDataNewTileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACATileFloor> TileFloorClass;

public:

	UFUNCTION(Server, Reliable, WithValidation)
	void SRPCAppendSpace(FVector relativePosition, class ACATileSpace* tileSpace);
	void SRPCAppendSpace_Implementation(FVector relativePosition, class ACATileSpace* tileSpace);
	bool SRPCAppendSpace_Validate(FVector relativePosition, class ACATileSpace* tileSpace);

	UFUNCTION(NetMulticast, Reliable)
	void MRPCOnAppendSpace(bool successed, class ACATileSpace* tileSpace);
	void MRPCOnAppendSpace_Implementation(bool successed, class ACATileSpace* tileSpace);
	UFUNCTION(Client, Reliable)
	void CRPCOnAppendSpace(bool successed, class ACATileSpace* tileSpace);
	void CRPCOnAppendSpace_Implementation(bool successed, class ACATileSpace* tileSpace);


	UFUNCTION(Server, Reliable)
	void SRPCRemoveSpace(class ACATileSpace* tileSpace);

	UFUNCTION(NetMulticast, Reliable)
	void MRPCOnRemoveSpace(bool successed);
	UFUNCTION(Client, Reliable)
	void CRPCOnRemoveSpace(bool successed);

	UFUNCTION(Server, Reliable)
	void SRPCSpawnSpace(FVector relativePosition, TSubclassOf<class ACATileSpace> tileSpace);
	void SRPCSpawnSpace_Implementation(FVector relativePosition, TSubclassOf<class ACATileSpace> tileSpace);

	void TileToZone(FVector position, class ACATileSpace* tileSpace);
	void CloneTileToZone(FVector position, class ACATileSpace* tileSpace);
	void DeleteTileToZone(FVector position);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAppendSpaceCallBack(bool successed, class ACATileSpace* tileSpace);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveSpaceCallBack(bool successed);


	// Space Funtion
	UFUNCTION()
	bool IsTileSpaceEmpty(FVector position);
	UFUNCTION()
	void AttachTile(FVector position, class ACATileSpace* newTile);
	UFUNCTION()
	void SpawnTile(FVector position, TSubclassOf<class ACATileSpace> newTile);
	UFUNCTION()
	void DeleteTile(class ACATileSpace* targetTile);

	virtual bool HasTypeNearByTile(FVector position, ESpaceType spaceType);

	UFUNCTION(BlueprintCallable, Category = "Tile System")
	ACATileSpace* GetTileAtPosition(const FVector& Position);
};
