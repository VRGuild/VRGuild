// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileSpace.h"
#include "TileSystem/CATileZone.h"
#include "TileSystem/FL_TileTools.h"

// Sets default values
ACATileSpace::ACATileSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->TileSpaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TileSpaceMesh"));
	SetRootComponent(TileSpaceMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/s_cube_1cm.s_cube_1cm'"));

	if (tempMesh.Succeeded())
		this->TileSpaceMesh->SetStaticMesh(tempMesh.Object);

	// material 가져오기
	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempBaseColor(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/TileSystem/Matrials/Instances/M_BaseColor_Inst.M_BaseColor_Inst'"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempOpacityColor(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/TileSystem/Matrials/Instances/M_OpacityColor_Inst.M_OpacityColor_Inst'"));
	
	if (tempBaseColor.Succeeded())
		this->TileBaseColor = tempBaseColor.Object;
	if (tempOpacityColor.Succeeded())
		this->TileOpacityColor = tempOpacityColor.Object;

	// 색상 적용
	if (this->TileSpaceMesh && TileBaseColor)
		TileSpaceMesh->SetMaterial(0, TileBaseColor);
}


// Called when the game starts or when spawned
void ACATileSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACATileSpace::Initialize(ACATileZone* parentZone, FVector position)
{
	this->ParentZone = parentZone;
	this->Position = UFL_TileTools::SnapGridVector(position, this->ParentZone->TileSize);
	this->SetActorLocation(this->Position);
	this->SetActorScale3D(FVector(this->ParentZone->TileSize));
}

// Called every frame
void ACATileSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACATileSpace::AddSpace(FVector relativeVector)
{
	if (!this->ParentZone) {
		UE_LOG(LogTemp, Display, TEXT("Parent Zone is Not Found"));
		return false;
	}

	FVector normal = relativeVector* this->ParentZone->TileSize;
	FVector gridVector = UFL_TileTools::SnapGridVector(normal, this->ParentZone->TileSize);

	FVector position = gridVector + this->Position;

	if (this->ParentZone->CreateNewTile(position))
	{
		UE_LOG(LogTemp, Display, TEXT("Create New Tile %s"), *gridVector.ToString());
		return true;
	}
	return false;
}

void ACATileSpace::DeleteSpace()
{
	if (this->ParentZone->DeleteTile(this->Position)) {
		this->Destroy();
	}
}


