// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CATileSpace.h"
#include "TileSystem/CATileZone.h"
#include "TileSystem/FL_TileTools.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACATileSpace::ACATileSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;

	this->TileSpaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TileSpaceMesh"));
	SetRootComponent(TileSpaceMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/s_cube_1cm.s_cube_1cm'"));

	if (tempMesh.Succeeded())
		this->TileSpaceMesh->SetStaticMesh(tempMesh.Object);

	// material 가져오기
	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempBaseColor(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/TileSystem/Matrials/Instances/MI_BaseColor.MI_BaseColor'"));
	
	if (tempBaseColor.Succeeded())
		this->TileBaseMat = tempBaseColor.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempOpacityColor(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/TileSystem/Matrials/Instances/MI_OpacityColor.MI_OpacityColor'"));
	if (tempOpacityColor.Succeeded())
		this->TileOpacityMat = tempOpacityColor.Object;

	// 색상 적용
	if (this->TileSpaceMesh && TileBaseMat)
		TileSpaceMesh->SetMaterial(0, TileBaseMat);


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

    // Mesh 컴포넌트 복사
    if (this->GetTileSpaceMesh() && NewSpace->GetTileSpaceMesh())
    {
        NewSpace->GetTileSpaceMesh()->SetStaticMesh(this->GetTileSpaceMesh()->GetStaticMesh());
        NewSpace->GetTileSpaceMesh()->SetMaterial(0, this->GetTileBaseMat());
        NewSpace->GetTileSpaceMesh()->SetVisibility(true);
    }

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

        // 필요한 경우 컴포넌트도 리플리케이션 설정
        if (TileSpaceMesh)
        {
            TileSpaceMesh->SetIsReplicated(true);
        }
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

void ACATileSpace::AttachSpace(FVector relativeVector, ACATileSpace* newTileSpace)
{
	if (!ParentZone->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("ParentZone is not valid"));
		return;
	}
    this->ParentZone->AttachTile(relativeVector, newTileSpace);
}

void ACATileSpace::Delete()
{
	this->ParentZone->DeleteTile(this);
}


