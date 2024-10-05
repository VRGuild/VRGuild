// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* TileSpaceMesh;

	UMaterialInstance* TileBaseColor;
	UMaterialInstance* TileOpacityColor;


	class ACATileZone* ParentZone;
	
	FVector Position;

public:
	// 생성자가 불가능 하여 기본 새팅 함수
	void Initialize(ACATileZone* parentZone, FVector position);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AddSpace(FVector relativeVector);

	void DeleteSpace();
};
