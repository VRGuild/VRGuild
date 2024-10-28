// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileZone.generated.h"

enum class ESpaceType : uint8;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	int32 TileSize = 1;

	int32 MaxTilePostion = TileSize;
	
	bool bRPCWait = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CreateDefualtZone();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	TMap<FVector, class ACATileSpace*> TileSpacesMap;

	UPROPERTY(ReplicatedUsing = OnRep_TileSpaces)
	TArray<FTileSpaceData> TileSpacesArray;

	UFUNCTION()
	void OnRep_TileSpaces();

	virtual void OnRep_Owner() override;

	FVector SendDataPosition;
	FString SendDataType;

	class ACATileSpace* SendDataNewTile;
public:

	int32 OnRepIndex;

	UFUNCTION(Server, Reliable, WithValidation)
	void SRPCAppendSpace(FVector relativePosition, class ACATileSpace* tileSpace);
	void SRPCAppendSpace_Implementation(FVector relativePosition, class ACATileSpace* tileSpace);
	bool SRPCAppendSpace_Validate(FVector relativePosition, class ACATileSpace* tileSpace);

	UFUNCTION(NetMulticast, Reliable)
	void MRPCOnAppendSpace(bool successed, class ACATileSpace* tileSpace);
	void MRPCOnAppendSpace_Implementation(bool successed, class ACATileSpace* tileSpace);
	UFUNCTION(Client, Reliable)
	void CRPCOnAppendSpace(bool successed, class ACATileSpace* tileSpace);


	UFUNCTION(Server, Reliable)
	void SRPCRemoveSpace(class ACATileSpace* tileSpace);

	UFUNCTION(NetMulticast, Reliable)
	void MRPCOnRemoveSpace(bool successed);
	UFUNCTION(Client, Reliable)
	void CRPCOnRemoveSpace(bool successed);

	ACATileSpace* CreateTileToZone(FVector relativePosition, FString type);
	ACATileSpace* CloneTileToZone(FVector position, class ACATileSpace* tileSpace);
	void DeleteTileToZone(FVector position);


	UFUNCTION(Server, Reliable)
	void SRPCCreateSpace(FVector relativePosition, const FString &type );
	void SRPCCreateSpace_Implementation(FVector relativePosition, const FString &type);

	UFUNCTION(Client, Reliable)
	void CRPCOnCreateSpace(bool successed, class ACATileSpace* tileSpace);
	void CRPCOnCreateSpace_Implementation(bool successed, class ACATileSpace* tileSpace);


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
	void DeleteTile(class ACATileSpace* targetTile);


	virtual bool HasTypeNearByTile(FVector position, ESpaceType spaceType);

};
