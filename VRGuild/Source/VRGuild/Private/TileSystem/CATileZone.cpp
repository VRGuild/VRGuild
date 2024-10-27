// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileZone.h"
#include "TileSystem/CATileSpace.h"
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

	this->TileSize = 128;
	CreateDefualtSpace();
}

void ACATileZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(ACATileZone, TileSpacesArray);
}

void ACATileZone::OnRep_TileSpaces()
{
	UE_LOG(LogTemp, Display, TEXT("OnRep_TileSpaces"));
	// TArray가 업데이트될 때마다 TMap 재구성
	TileSpacesMap.Empty();
	for (const FTileSpaceData& TileData : TileSpacesArray)
	{
		if (TileData.TileSpace)
		{
			TileSpacesMap.Add(TileData.Position, TileData.TileSpace);
		}
	}
}

void ACATileZone::OnRep_Owner()
{
	Super::OnRep_Owner();
	SRPCAppendSpace(this->SendDataPosition, this->nSendDataNewTile);
}


void ACATileZone::CreateDefualtSpace()
{
	if (this->HasAuthority())
	{
		ACATileSpace* tempTile = GetWorld()->SpawnActor<ACATileSpace>();
		tempTile->SetActorScale3D(FVector(this->TileSize));
		SRPCAppendSpace(FVector(0,0,0), tempTile);
		tempTile->Destroy();
	}
}

void ACATileZone::SRPCAppendSpace_Implementation(FVector relativePosition, ACATileSpace* tileSpace)
{
	UE_LOG(LogTemp, Display, TEXT("SRPCAppendSpace"));
	
	FVector gridPosition = UFL_TileTools::SnapGridVector(relativePosition, 1);

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


void ACATileZone::CloneTileToZone(FVector position, ACATileSpace* tileSpace)
{
	if (!HasAuthority() || !tileSpace)
		return;

	ACATileSpace* newTileSpace = tileSpace->Clone();

	if (newTileSpace)
	{
		// 위치 및 부모 설정
		newTileSpace->SetParentZone(this);
		newTileSpace->SetPosition(position);
		newTileSpace->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		newTileSpace->SetActorRelativeLocation(position * TileSize);
		newTileSpace->SetActorScale3D(FVector(this->TileSize));

		// TArray에 추가
		TileSpacesArray.Add(FTileSpaceData(position, newTileSpace));
		// 로컬 맵에도 추가
		TileSpacesMap.Add(position, newTileSpace);
	}
}

void ACATileZone::DeleteTileToZone(FVector position)
{
	if (!HasAuthority()) return;

	for (int32 i = TileSpacesArray.Num() - 1; i >= 0; --i)
	{
		if (TileSpacesArray[i].Position == position)
		{
			if (TileSpacesArray[i].TileSpace)
			{
				TileSpacesArray[i].TileSpace->Destroy();
			}
			TileSpacesArray.RemoveAt(i);
			break;
		}
	}

	// 로컬 맵에서도 제거
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
	this->nSendDataNewTile = newTile;
	SRPCAppendSpace(position, newTile);
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

