// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileFloor.h"
#include "TileSystem/CATileZone.h"
#include "TileSystem/FL_TileTools.h"
#include "TileSystem/CATileSpace.h"
#include "TileSystem/CWGTileCost.h"
#include "TileSystem/CATileCube.h"
#include "Net/UnrealNetwork.h"

ACATileFloor::ACATileFloor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	this->TileSize = 400;
	this->SpaceType = ESpaceType::Floor;

	this->BasePivotComp = CreateDefaultSubobject< USceneComponent>(FName("BasePivotComp"));
	this->BaseFloorComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("BaseFloorComp"));
	this->NorthWallComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("NorthWallComp"));
	this->SouthWallComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("SouthWallComp"));
	this->EastWallComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("EastWallComp"));
	this->WestWallComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("WestWallComp"));
	this->CeilingComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("CeilingComp"));

	this->BasePivotComp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->BaseFloorComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->NorthWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->SouthWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->EastWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->WestWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->CeilingComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);

	this->BasePivotComp->SetRelativeLocation(FVector(0, 0, -this->TileSize / 2));
	this->BaseFloorComp->SetRelativeLocation(FVector(0, 0, 0));
	this->NorthWallComp->SetRelativeLocation(FVector(+this->TileSize / 2, 0, 0));
	this->SouthWallComp->SetRelativeLocation(FVector(-this->TileSize / 2, 0, 0));
	this->EastWallComp->SetRelativeLocation(FVector(0, +this->TileSize / 2, 0));
	this->WestWallComp->SetRelativeLocation(FVector(0, -this->TileSize / 2, 0));
	this->CeilingComp->SetRelativeLocation(FVector(0, 0, this->TileSize));

	this->NorthWallComp->SetRelativeRotation(FRotator(0, 90, 0));
	this->SouthWallComp->SetRelativeRotation(FRotator(0, -90, 0));

}

void ACATileFloor::BeginPlay()
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

	UE_LOG(LogTemp, Warning, TEXT("Spawned [%s]"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"));
}

void ACATileFloor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (this->BaseFloorMeshList.IsValidIndex(0))
		this->BaseFloorComp->SetStaticMesh(this->BaseFloorMeshList[0]);
	if (this->NorthWallMeshList.IsValidIndex(0))
		this->NorthWallComp->SetStaticMesh(this->NorthWallMeshList[0]);
	if (this->SouthWallMeshList.IsValidIndex(0))
		this->SouthWallComp->SetStaticMesh(this->SouthWallMeshList[0]);
	if (this->EastWallMeshList.IsValidIndex(0))
		this->EastWallComp->SetStaticMesh(this->EastWallMeshList[0]);
	if (this->WestWallMeshList.IsValidIndex(0))
		this->WestWallComp->SetStaticMesh(this->WestWallMeshList[0]);
	if (this->CeilingMeshList.IsValidIndex(0))
		this->CeilingComp->SetStaticMesh(this->CeilingMeshList[0]);
}

void ACATileFloor::CreateDefualtSpace()
{
	// 기본 Floor 타일 생성
		// 3x3 그리드 생성 (-3 ~ 3)
	for (int y = -1; y <= 2; y++)
	{
		for (int x = -1; x <= 2; x++)
		{
			this->ParentZone->SRPCAppendSpace(FVector(x, y, 0), this);
		}
	}
}

void ACATileFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACATileFloor, SurfaceVisibilityFlags);

}

void ACATileFloor::ApplySurfaceVisibility()
{
	// 비트 플래그에 따라 컴포넌트 visibility 설정
	NorthWallComp->SetVisibility((SurfaceVisibilityFlags & WALL_NORTH) != 0);
	SouthWallComp->SetVisibility((SurfaceVisibilityFlags & WALL_SOUTH) != 0);
	EastWallComp->SetVisibility((SurfaceVisibilityFlags & WALL_EAST) != 0);
	WestWallComp->SetVisibility((SurfaceVisibilityFlags & WALL_WEST) != 0);

	// Apply visibility to floor and ceiling
	BaseFloorComp->SetVisibility((SurfaceVisibilityFlags & SURFACE_FLOOR) != 0);
	CeilingComp->SetVisibility((SurfaceVisibilityFlags & SURFACE_CEILING) != 0);

	// Apply collision settings
	NorthWallComp->SetCollisionEnabled(((SurfaceVisibilityFlags & WALL_NORTH) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	SouthWallComp->SetCollisionEnabled(((SurfaceVisibilityFlags & WALL_SOUTH) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	EastWallComp->SetCollisionEnabled(((SurfaceVisibilityFlags & WALL_EAST) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	WestWallComp->SetCollisionEnabled(((SurfaceVisibilityFlags & WALL_WEST) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	BaseFloorComp->SetCollisionEnabled(((SurfaceVisibilityFlags & SURFACE_FLOOR) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	CeilingComp->SetCollisionEnabled(((SurfaceVisibilityFlags & SURFACE_CEILING) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

void ACATileFloor::MulticastUpdateSurfaceVisibility_Implementation(uint8 NewFlags)
{
	SurfaceVisibilityFlags = NewFlags;
	ApplySurfaceVisibility();
}

void ACATileFloor::OnRep_WallVisibility()
{
	ApplySurfaceVisibility();
}

ACATileSpace* ACATileFloor::Clone()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	// 명시적으로 ACATileFloor로 캐스팅
	ACATileFloor* NewFloor = GetWorld()->SpawnActor<ACATileFloor>(GetClass(),
		GetActorLocation(), GetActorRotation(), SpawnParams);

	if (NewFloor)
	{
		// 기본 설정
		NewFloor->SetReplicates(true);
		NewFloor->SetReplicateMovement(true);
		NewFloor->SetSpaceType(ESpaceType::Floor);

		return NewFloor;
	}
	return nullptr;
}

void ACATileFloor::AttachSpace(FHitResult hitResult, ACATileSpace* newTileSpace)
{
	if (!ParentZone || !newTileSpace) return;

	FString HitCompName = hitResult.GetComponent()->GetName();
	FVector AttachOffset = FVector::ZeroVector;

	if (HitCompName == "NorthWallComp")
	{
		AttachOffset = FVector(1, 0, 0);
	}
	else if (HitCompName == "SouthWallComp")
	{
		AttachOffset = FVector(-1, 0, 0);
	}
	else if (HitCompName == "EastWallComp")
	{
		AttachOffset = FVector(0, 1, 0);
	}
	else if (HitCompName == "WestWallComp")
	{
		AttachOffset = FVector(0, -1, 0);
	}
	else if (HitCompName == "BaseFloorComp")
	{
		AttachOffset = FVector(0, 0, -1);
	}
	else if (HitCompName == "CeilingComp")
	{
		AttachOffset = FVector(0, 0, 1);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit invalid component: %s"), *HitCompName);
		return;
	}

	// 새 타일 부착 및 가시성 업데이트
	FVector NewPosition = this->Position + AttachOffset;
	ParentZone->AttachTile(NewPosition, newTileSpace);

}

void ACATileFloor::AttachPostision(FVector position, ACATileSpace* newTileSpace)
{
	this->ParentZone->AttachTile(this->Position + position, newTileSpace);
}

void ACATileFloor::UpdateSurfaceVisible()
{
	if (!ParentZone) return;
#if WITH_EDITOR
	UE_LOG(LogTemp, Display, TEXT("UpdateSurfaceVisible "));
#endif
	// 각 방향 체크
	const TArray<TPair<FString, FVector>> Directions = {
		TPair<FString, FVector>("NorthWallComp", FVector(1, 0, 0)),
		TPair<FString, FVector>("SouthWallComp", FVector(-1, 0, 0)),
		TPair<FString, FVector>("EastWallComp", FVector(0, 1, 0)),
		TPair<FString, FVector>("WestWallComp", FVector(0, -1, 0)),
		TPair<FString, FVector>("BaseFloorComp", FVector(0, 0, -1)),
		TPair<FString, FVector>("CeilingComp", FVector(0, 0, 1))
	};

	uint8 NewFlags = SurfaceVisibilityFlags;

	for (const auto& Dir : Directions)
	{
		ACATileSpace* NeighborSpace = ParentZone->GetTileAtPosition(Position + Dir.Value);

		if (NeighborSpace && NeighborSpace->GetSpaceType() == ESpaceType::Floor)
		{
			if (ACATileFloor* NeighborFloor = Cast<ACATileFloor>(NeighborSpace))
			{
				if (Dir.Key == "NorthWallComp")
				{
					NewFlags &= ~WALL_NORTH;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~WALL_SOUTH);
				}
				else if (Dir.Key == "SouthWallComp")
				{
					NewFlags &= ~WALL_SOUTH;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~WALL_NORTH);
				}
				else if (Dir.Key == "EastWallComp")
				{
					NewFlags &= ~WALL_EAST;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~WALL_WEST);
				}
				else if (Dir.Key == "WestWallComp")
				{
					NewFlags &= ~WALL_WEST;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~WALL_EAST);
				}
				else if (Dir.Key == "BaseFloorComp")
				{
					NewFlags &= ~SURFACE_FLOOR;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~SURFACE_CEILING);
				}
				else if (Dir.Key == "CeilingComp")
				{
					NewFlags &= ~SURFACE_CEILING;
					NeighborFloor->MulticastUpdateSurfaceVisibility(NeighborFloor->SurfaceVisibilityFlags & ~SURFACE_FLOOR);
				}
			}
		}
	}
	// 상태가 변경되었다면 모든 클라이언트에 전파
	if (NewFlags != SurfaceVisibilityFlags)
	{
		MulticastUpdateSurfaceVisibility(NewFlags);
	}
}



void ACATileFloor::Delete()
{
}
