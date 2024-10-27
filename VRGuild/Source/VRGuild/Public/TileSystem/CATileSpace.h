// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileSystem/CATileZone.h"
#include "CATileSpace.generated.h"

UENUM(BlueprintType)
enum class ESpaceType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Floor = 1 UMETA(DisplayName = "Floor"),
	Wall = 2 UMETA(DisplayName = "Wall"),
};

UCLASS()
class VRGUILD_API ACATileSpace : public ACATileZone
{
	GENERATED_BODY()

private:


public:	
	// Sets default values for this actor's properties
	ACATileSpace();

	// 복사 생성을 위한 Clone 함수
	UFUNCTION(BlueprintCallable)
	ACATileSpace* Clone();

	FORCEINLINE ACATileZone* GetParentZone() { return this->ParentZone; };
	FORCEINLINE void SetParentZone(ACATileZone* parentZone) { this->ParentZone = parentZone; };

	FORCEINLINE FVector GetPosition() { return this->Position; };
	FORCEINLINE void SetPosition(FVector relativePostision) { this->Position = relativePostision; };

	FORCEINLINE ESpaceType GetSpaceType() { return this->SpaceType; };
	FORCEINLINE void SetSpaceType(ESpaceType spaceType) { this->SpaceType = spaceType; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetTileSpaceMesh() const { return TileSpaceMesh; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UMaterialInstance* GetTileBaseMat() const { return TileBaseMat; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CreateDefualtSpace() override;

	UPROPERTY(Replicated)
	ACATileZone* ParentZone;
	UPROPERTY(Replicated)
	FVector Position = FVector(0);
	UPROPERTY(Replicated)
	ESpaceType SpaceType = ESpaceType::None;

	UStaticMeshComponent* TileSpaceMesh;

	UMaterialInstance* TileBaseMat;
	UMaterialInstance* TileOpacityMat;



public:
	// 생성자가 불가능 하여 기본 새팅 함수
	//void Initialize(ACATileZone* parentZone, FVector position);
	//void Initialize(ACATileZone* parentZone, FVector position, ESpaceType spaceType);

	virtual void AttachSpace(FVector relativeVector, ACATileSpace* newTileSpace);

	virtual void Delete();

};
