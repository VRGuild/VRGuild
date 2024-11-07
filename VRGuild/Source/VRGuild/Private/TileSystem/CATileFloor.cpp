// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileFloor.h"
#include "TileSystem/CATileZone.h"
#include "TileSystem/FL_TileTools.h"
#include "TileSystem/CATileSpace.h"
#include "TileSystem/CWGTileCost.h"
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

	this->BasePivotComp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->BaseFloorComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->NorthWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->SouthWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->EastWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);
	this->WestWallComp->AttachToComponent(this->BasePivotComp, FAttachmentTransformRules::KeepRelativeTransform);


	this->BasePivotComp->SetRelativeLocation(FVector(0, 0, -this->TileSize / 2));
	this->BaseFloorComp->SetRelativeLocation(FVector(0, 0, 0));
	this->NorthWallComp->SetRelativeLocation(FVector(+this->TileSize / 2, 0, 0));
	this->SouthWallComp->SetRelativeLocation(FVector(-this->TileSize / 2, 0, 0));
	this->EastWallComp->SetRelativeLocation(FVector(0, +this->TileSize / 2, 0));
	this->WestWallComp->SetRelativeLocation(FVector(0, -this->TileSize / 2, 0));

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
}

void ACATileFloor::CreateDefualtSpace()
{
	// 기본 Floor 타일 생성
	ACATileFloor* templateFloor = GetWorld()->SpawnActor<ACATileFloor>();
 	if (templateFloor)
	{
		// 3x3 그리드 생성 (-3 ~ 3)
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
			}
		}
		// 템플릿으로 사용한 Floor 제거
		templateFloor->Destroy();
	}
}

void ACATileFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACATileFloor, WallVisibilityFlags);

}

void ACATileFloor::ApplyWallVisibility()
{
	// 비트 플래그에 따라 컴포넌트 visibility 설정
	NorthWallComp->SetVisibility((WallVisibilityFlags & (1 << 0)) != 0);
	SouthWallComp->SetVisibility((WallVisibilityFlags & (1 << 1)) != 0);
	EastWallComp->SetVisibility((WallVisibilityFlags & (1 << 2)) != 0);
	WestWallComp->SetVisibility((WallVisibilityFlags & (1 << 3)) != 0);

	NorthWallComp->SetCollisionEnabled(((WallVisibilityFlags & (1 << 0)) != 0 )? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	SouthWallComp->SetCollisionEnabled(((WallVisibilityFlags & (1 << 1)) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	EastWallComp->SetCollisionEnabled(((WallVisibilityFlags & (1 << 2)) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	WestWallComp->SetCollisionEnabled(((WallVisibilityFlags & (1 << 3)) != 0) ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

void ACATileFloor::MulticastUpdateWallVisibility_Implementation(uint8 NewFlags)
{
	WallVisibilityFlags = NewFlags;
	ApplyWallVisibility();
}

void ACATileFloor::OnRep_WallVisibility()
{
	ApplyWallVisibility();
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

void ACATileFloor::AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace)
{
	FString HitCompName = HitResult.GetComponent()->GetName();
	UE_LOG(LogTemp, Display, TEXT("Hit Comp : %s"), *HitCompName);
	if (HitCompName == "NorthWallComp")
	{
		this->ParentZone->AttachTile(this->Position + FVector(1, 0, 0), newTileSpace);
	}
	else if (HitCompName == "SouthWallComp")
	{
		this->ParentZone->AttachTile(this->Position + FVector(-1, 0, 0), newTileSpace);
	}
	else if (HitCompName == "EastWallComp")
	{
		this->ParentZone->AttachTile(this->Position + FVector(0, 1, 0), newTileSpace);
	}
	else if(HitCompName == "WestWallComp")
	{
		this->ParentZone->AttachTile(this->Position + FVector(0, -1, 0), newTileSpace);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Wrong Attachspace floortile"));
	}
}

void ACATileFloor::AttachPostision(FVector position, ACATileSpace* newTileSpace)
{
	this->ParentZone->AttachTile(this->Position + position, newTileSpace);
}

void ACATileFloor::UpdateWallVisible()
{
	if (!ParentZone) return;

	UE_LOG(LogTemp, Display, TEXT("UpdateWallVisible "));

	// 각 방향 체크
	const TArray<TPair<FString, FVector>> Directions = {
		TPair<FString, FVector>("NorthWallComp", FVector(1, 0, 0)),
		TPair<FString, FVector>("SouthWallComp", FVector(-1, 0, 0)),
		TPair<FString, FVector>("EastWallComp", FVector(0, 1, 0)),
		TPair<FString, FVector>("WestWallComp", FVector(0, -1, 0))
	};

	uint8 NewFlags = WallVisibilityFlags;

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
					NeighborFloor->MulticastUpdateWallVisibility(NeighborFloor->WallVisibilityFlags & ~WALL_SOUTH);
				}
				else if (Dir.Key == "SouthWallComp")
				{
					NewFlags &= ~WALL_SOUTH;
					NeighborFloor->MulticastUpdateWallVisibility(NeighborFloor->WallVisibilityFlags & ~WALL_NORTH);
				}
				else if (Dir.Key == "EastWallComp")
				{
					NewFlags &= ~WALL_EAST;
					NeighborFloor->MulticastUpdateWallVisibility(NeighborFloor->WallVisibilityFlags & ~WALL_WEST);
				}
				else if (Dir.Key == "WestWallComp")
				{
					NewFlags &= ~WALL_WEST;
					NeighborFloor->MulticastUpdateWallVisibility(NeighborFloor->WallVisibilityFlags & ~WALL_EAST);
				}
			}
		}
	}

	// 상태가 변경되었다면 모든 클라이언트에 전파
	if (NewFlags != WallVisibilityFlags)
	{
		MulticastUpdateWallVisibility(NewFlags);
	}
}



void ACATileFloor::Delete()
{
}
