// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CATileSpace.generated.h"

UENUM(BlueprintType)
enum class ESpaceType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Floor = 1 UMETA(DisplayName = "Floor"),
	Wall = 2 UMETA(DisplayName = "Wall"),
};

UCLASS()
class VRGUILD_API ACATileSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACATileSpace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* TileSpaceMesh;

	UMaterialInstance* TileBaseColor;
	UMaterialInstance* TileOpacityColor;


	class ACATileZone* ParentZone;
	
	FVector Position;

	ESpaceType SpaceType = ESpaceType::None;

public:
	// 생성자가 불가능 하여 기본 새팅 함수
	void Initialize(ACATileZone* parentZone, FVector position);
	void Initialize(ACATileZone* parentZone, FVector position, ESpaceType spaceType);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AddSpace(FVector relativeVector);

	void DeleteSpace();

	ESpaceType GetSpaceType() { return this->SpaceType; };
	void SetSpaceType(ESpaceType spaceType) { this->SpaceType = spaceType; };
};
