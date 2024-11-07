// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileSpace.h"
#include "TileSystem/CATileZone.h"
#include "TileSystem/CATileFloor.h"
#include "TileSystem/FL_TileTools.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACATileSpace::ACATileSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;

	if (GetWorld() && GetWorld()->GetFirstPlayerController())
	{
		SetOwner(GetWorld()->GetFirstPlayerController());
	}

}


ACATileSpace* ACATileSpace::Clone()
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    ACATileSpace* NewSpace = GetWorld()->SpawnActor<ACATileSpace>(GetClass(),
        GetActorLocation(), GetActorRotation(), SpawnParams);

    // 리플리케이션 설정
    NewSpace->SetReplicates(true);
    NewSpace->SetReplicateMovement(true);
    NewSpace->SetOwner(this->GetOwner());

    // SpaceType 복사
    NewSpace->SetSpaceType(this->GetSpaceType());

    return NewSpace;
}




// Called when the game starts or when spawned
void ACATileSpace::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && GetWorld()->GetFirstPlayerController())
	{
		SetOwner(GetWorld()->GetFirstPlayerController());
	}
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}


void ACATileSpace::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACATileSpace, Position);
	DOREPLIFETIME(ACATileSpace, ParentZone);
	DOREPLIFETIME(ACATileSpace, SpaceType);
}

void ACATileSpace::CreateDefualtSpace()
{
    if (this->HasAuthority())
    {

    }
}

void ACATileSpace::AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace)
{
	if (!ParentZone->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("ParentZone is not valid"));
		return;
	}
	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());
	if (target->SpaceType == ESpaceType::Floor)
	{
		ACATileFloor* floorTarget = Cast<ACATileFloor>(HitResult.GetActor());
		floorTarget->AttachSpace(HitResult, newTileSpace);
	}
	else
	{
		this->ParentZone->AttachTile(this->Position + HitResult.Normal, newTileSpace);
	}
}

void ACATileSpace::AttachPostision(FVector position, ACATileSpace* newTileSpace)
{
	this->ParentZone->AttachTile(this->Position + position, newTileSpace);
}

void ACATileSpace::Delete()
{
	this->ParentZone->DeleteTile(this);
}


