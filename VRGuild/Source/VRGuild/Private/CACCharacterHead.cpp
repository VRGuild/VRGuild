// Fill out your copyright notice in the Description page of Project Settings.


#include "CACCharacterHead.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

// Sets default values for this component's properties
UCACCharacterHead::UCACCharacterHead()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
	CharacterHead = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterHead"));

	HeadMesh0 = nullptr;
	HeadMeshBox.Add(0, HeadMesh0);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempHead1(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (TempHead1.Succeeded())
	{ // TempHead1 Referecne 경로 수정 예정 
		HeadMesh1 = TempHead1.Object;
		HeadMeshBox.Add(1, HeadMesh1);
	}
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempHead2(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	{ // TempHead2 Referecne 경로 수정 예정 
		HeadMesh2 = TempHead2.Object;
		HeadMeshBox.Add(2, HeadMesh2);
	}
}

void UCACCharacterHead::InitializeComponent()
{
	Super::InitializeComponent();

	this->Owner = GetOwner();
	if (Owner->IsA<ATP_ThirdPersonCharacter>())
	{
		ATP_ThirdPersonCharacter* character = Cast<ATP_ThirdPersonCharacter>(Owner);
		CharacterHead->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		CharacterHead->SetLeaderPoseComponent(character->GetMesh());
	}
}
// Called when the game starts
void UCACCharacterHead::BeginPlay()
{
	Super::BeginPlay();

}

void UCACCharacterHead::SwitchHead(int value)
{
	ServerSwitchHead(value);
}

void UCACCharacterHead::ServerSwitchHead_Implementation(int value)
{
	MulticastSwitchHead(value);
}

void UCACCharacterHead::MulticastSwitchHead_Implementation(int value)
{
	if (nullptr != CharacterHead)
	{
		CharacterHead->SetSkeletalMesh(HeadMeshBox[value]);
	}
}


