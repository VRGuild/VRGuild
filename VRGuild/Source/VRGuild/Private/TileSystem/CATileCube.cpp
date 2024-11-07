// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileCube.h"

ACATileCube::ACATileCube()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;

    this->TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TileMesh"));
    this->SetRootComponent(this->TileMesh);
}

void ACATileCube::BeginPlay()
{
	Super::BeginPlay();
}

void ACATileCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ACATileCube::CreateDefualtSpace()
{

}

ACATileSpace* ACATileCube::Clone()
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    ACATileCube* NewSpace = GetWorld()->SpawnActor<ACATileCube>(GetClass(),
        GetActorLocation(), GetActorRotation(), SpawnParams);

    // 리플리케이션 설정
    NewSpace->SetReplicates(true);
    NewSpace->SetReplicateMovement(true);
    NewSpace->SetOwner(this->GetOwner());

    // SpaceType 복사
    NewSpace->SetSpaceType(this->GetSpaceType());

    NewSpace->TileMesh = this->TileMesh;

	return nullptr;
}

void ACATileCube::AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace)
{
}

void ACATileCube::AttachPostision(FVector position, ACATileSpace* newTileSpace)
{
}

void ACATileCube::Delete()
{
}
