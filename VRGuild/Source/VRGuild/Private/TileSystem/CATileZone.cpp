// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileZone.h"
#include "TileSystem/CATileSpace.h"
#include "TileSystem/CATileFloor.h"
#include "TileSystem/CATileCube.h"
#include "TileSystem/FL_TileTools.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACATileZone::ACATileZone()
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

// Called when the game starts or when spawned
void ACATileZone::BeginPlay()
{
	Super::BeginPlay();

	bReplicates = true;
	bAlwaysRelevant = true;
}

void ACATileZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

//void ACATileZone::OnRep_TileSpaces()
//{
//	UE_LOG(LogTemp, Display, TEXT("OnRep_TileSpaces"));
//	// TArray가 업데이트될 때마다 TMap 재구성
//	TileSpacesMap.Empty();
//	for (const FTileSpaceData& TileData : TileSpacesArray)
//	{
//		if (TileData.TileSpace)
//		{
//			TileSpacesMap.Add(TileData.Position, TileData.TileSpace);
//		}
//	}
//}

void ACATileZone::OnRep_Owner()
{
	Super::OnRep_Owner();
	if (this->SendDataNewTile)
		SRPCAppendSpace(this->SendDataPosition, this->SendDataNewTile);
	else if (this->SendDataNewTileClass)
		SRPCSpawnSpace(this->SendDataPosition, this->SendDataNewTileClass);
}


void ACATileZone::CreateDefualtSpace()
{
	UE_LOG(LogTemp, Display, TEXT("netmode : %d"), GetWorld()->GetNetMode());
	if (!this->HasAuthority())
		return;

	ACATileSpace* tempTile;
	if (this->SpaceType == ESpaceType::Floor)
	{
		if (!TileFloorClass)
			return;
		tempTile = GetWorld()->SpawnActor<ACATileFloor>(TileFloorClass);
		SRPCAppendSpace(FVector(0, 0, 0), tempTile);
		// 3x3 그리드 생성 (-3 ~ 3)
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				SRPCAppendSpace(FVector(x,y,0), tempTile);
			}
		}
	}
	else
	{ 
		tempTile= GetWorld()->SpawnActor<ACATileSpace>();
		SRPCAppendSpace(this->GetActorLocation(), tempTile);
	}
	tempTile->Destroy();
}

void ACATileZone::SRPCAppendSpace_Implementation(FVector relativePosition, ACATileSpace* tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("SRPCAppendSpace"));
	
	FVector gridPosition = UFL_TileTools::SnapGridVector(relativePosition, 1);

	UE_LOG(LogTemp, Display, TEXT("grid position %f %f %f"), gridPosition.X, gridPosition.Y, gridPosition.Z);
	if (this->TileSpacesMap.Contains(gridPosition))
		return CRPCOnAppendSpace(false, tileSpace);
	CloneTileToZone(gridPosition, tileSpace);
	CRPCOnAppendSpace(true, tileSpace);
}

bool ACATileZone::SRPCAppendSpace_Validate(FVector relativePosition, ACATileSpace* tileSpace)
{
	return true;
}

void ACATileZone::MRPCOnAppendSpace_Implementation(bool successed, ACATileSpace* tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("MRPCOnAppendSpace"));
	tileSpace->SetOwner(GetWorld()->GetFirstPlayerController());
}

void ACATileZone::CRPCOnAppendSpace_Implementation(bool successed, ACATileSpace* tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("CRPCOnAppendSpace"));
	bRPCWait = false;
	OnAppendSpaceCallBack(successed, tileSpace);
}

void ACATileZone::SRPCRemoveSpace_Implementation(ACATileSpace* tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("SRPCRemoveSpace"));

	FVector gridPosition = UFL_TileTools::SnapGridVector(tileSpace->GetPosition(), 1);

	if (!this->TileSpacesMap.Contains(gridPosition))
		return CRPCOnRemoveSpace(false);
	DeleteTileToZone(gridPosition);
	CRPCOnRemoveSpace(true);
}

void ACATileZone::MRPCOnRemoveSpace_Implementation(bool successed)
{
}

void ACATileZone::CRPCOnRemoveSpace_Implementation(bool successed)
{
	UE_LOG(LogTemp, Display, TEXT("CRPCOnRemoveSpace"));
	bRPCWait = false;
}

void ACATileZone::TileToZone(FVector position, ACATileSpace* tileSpace)
{
	if (!HasAuthority() || !tileSpace)
		return;

	if (tileSpace)
	{
		// 위치 및 부모 설정
		tileSpace->SetParentZone(this);
		tileSpace->SetPosition(position);
		tileSpace->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		tileSpace->SetActorRelativeLocation(position * TileSize);
		// 로컬 맵에도 추가
		TileSpacesMap.Add(position, tileSpace);
	}
}

void ACATileZone::CloneTileToZone(FVector position, ACATileSpace* tileSpace)
{
	if (!HasAuthority() || !tileSpace)
		return;
	ACATileSpace* newTileSpace = nullptr;
	if (tileSpace->GetSpaceType() == ESpaceType::Floor)
	{
		newTileSpace = Cast<ACATileFloor>(tileSpace)->Clone();
	}
	else
	{
		newTileSpace = tileSpace->Clone();
	}
	if (newTileSpace)
	{
		// 위치 및 부모 설정
		newTileSpace->TileSize = tileSpace->TileSize;
		newTileSpace->SetParentZone(this);
		newTileSpace->SetPosition(position);
		newTileSpace->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		newTileSpace->SetActorRelativeLocation(position * newTileSpace->TileSize * this->TileSize);
		newTileSpace->SetActorScale3D(FVector(this->TileSize));

		// 로컬 맵에도 추가
		TileSpacesMap.Add(position, newTileSpace);

		// Floor 타일인 경우 벽 업데이트
		if (ACATileFloor* newFloor = Cast<ACATileFloor>(newTileSpace))
		{
			// 새로 생성된 타일의 벽 업데이트
			newFloor->UpdateWallVisible();
		}
	}
}

void ACATileZone::DeleteTileToZone(FVector position)
{
	if (!HasAuthority()) return;

	ACATileSpace* targetTileSpace = this->TileSpacesMap[position];
	
	this->TileSpacesMap.Remove(position);

	targetTileSpace->Destroy();
}

bool ACATileZone::IsTileSpaceEmpty(FVector position)
{
	if (!HasAuthority())
		return false;

	FVector gridPosition = UFL_TileTools::SnapGridVector(position, 1);
	return !this->TileSpacesMap.Contains(gridPosition);
}

void ACATileZone::AttachTile(FVector position, ACATileSpace* newTile)
{
	UE_LOG(LogTemp, Display, TEXT("AttachTile Called"));

	//// 네트워크 상태 체크
	//UE_LOG(LogTemp, Display, TEXT("Zone NetMode: %d"), static_cast<int32>(GetNetMode()));
	//UE_LOG(LogTemp, Display, TEXT("Zone HasAuthority: %d"), HasAuthority());

	//// Actor 상태 체크
	//UE_LOG(LogTemp, Display, TEXT("Zone Role: %d"), static_cast<int32>(GetLocalRole()));
	//UE_LOG(LogTemp, Display, TEXT("Zone Remote Role: %d"), static_cast<int32>(GetRemoteRole()));

	//ENetMode NetMode = GetNetMode();
	//UE_LOG(LogTemp, Display, TEXT("NetMode: %d"), static_cast<int32>(NetMode));
	if (!newTile)
		return ;
	bRPCWait = true;

	this->SendDataPosition = position;
	this->SendDataNewTile = newTile;
	this->SendDataNewTileClass = nullptr;
	if (GetOwner())
		SRPCAppendSpace(this->SendDataPosition, this->SendDataNewTile);
	else
		ATP_ThirdPersonCharacter::SetOwnerFor(this, GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ACATileZone::SpawnTile(FVector position, TSubclassOf<class ACATileSpace> newTile)
{
	if (!newTile)
		return;
	bRPCWait = true;

	this->SendDataPosition = position;
	this->SendDataNewTile = nullptr;
	this->SendDataNewTileClass = newTile;
	if (GetOwner())
		SRPCSpawnSpace(this->SendDataPosition, this->SendDataNewTileClass);
	else
		ATP_ThirdPersonCharacter::SetOwnerFor(this, GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ACATileZone::DeleteTile(ACATileSpace* targetTile)
{
	if (!targetTile )
		return;
	bRPCWait = true;
	SRPCRemoveSpace(targetTile);
}

bool ACATileZone::HasTypeNearByTile(FVector position, ESpaceType spaceType)
{
	FVector nearPosition;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				nearPosition = position + (this->TileSize * FVector(x, y, z));
				if (!IsTileSpaceEmpty(nearPosition) && this->TileSpacesMap[nearPosition]->GetSpaceType() == spaceType)
				{
					return true;
				}
			}
		}
	}
	return false;
}

ACATileSpace* ACATileZone::GetTileAtPosition(const FVector& position)
{
	FVector gridPosition = UFL_TileTools::SnapGridVector(position, 1);
	if (this->TileSpacesMap.Contains(gridPosition))
	{
		return this->TileSpacesMap[gridPosition];
	}
	return nullptr;
}

void ACATileZone::SRPCSpawnSpace_Implementation(FVector position, TSubclassOf<ACATileSpace> tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("SRPCAppendSpace"));

	ACATileSpace* newtile = this->GetWorld()->SpawnActor<ACATileSpace>(tileSpace);
	if (!newtile)
		return;
	newtile->SetActorLocation(position);

	CRPCOnAppendSpace(true, newtile);
}
