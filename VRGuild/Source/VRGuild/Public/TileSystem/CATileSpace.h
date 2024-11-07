// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FL_TileTools.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileSpace.generated.h"

UCLASS()
class VRGUILD_API ACATileSpace : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACATileSpace();

	// 복사 생성을 위한 Clone 함수
	UFUNCTION(BlueprintCallable)
	virtual ACATileSpace* Clone();

	int32 TileSize = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void CreateDefualtSpace();

	UPROPERTY(Replicated)
	class ACATileZone* ParentZone;
	UPROPERTY(Replicated)
	FVector Position = FVector(0);
	UPROPERTY(Replicated)
	ESpaceType SpaceType = ESpaceType::None;

public:
	class ACATileZone* GetParentZone() { return this->ParentZone; };
	void SetParentZone(class ACATileZone* parentZone) { this->ParentZone = parentZone; };

	FORCEINLINE FVector GetPosition() { return this->Position; };
	FORCEINLINE void SetPosition(FVector relativePostision) { this->Position = relativePostision; };

	FORCEINLINE ESpaceType GetSpaceType() { return this->SpaceType; };
	FORCEINLINE void SetSpaceType(ESpaceType spaceType) { this->SpaceType = spaceType; };

	virtual void AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace);
	virtual void AttachPostision(FVector position, ACATileSpace* newTileSpace);

	virtual void Delete();

};
