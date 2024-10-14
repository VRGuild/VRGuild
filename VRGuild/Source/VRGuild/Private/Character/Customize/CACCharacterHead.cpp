// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CACCharacterHead.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

// Sets default values for this component's properties
UCACCharacterHead::UCACCharacterHead()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	CharacterSKM = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterHead"));

	SkeletalMeshBox.Add(0, nullptr);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempHead1(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (TempHead1.Succeeded())
	{ // TempHead1 Referecne 경로 수정 예정 
		USkeletalMesh* HeadMesh1 = TempHead1.Object;
		SkeletalMeshBox.Add(1, HeadMesh1);
	}
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempHead2(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	{ // TempHead2 Referecne 경로 수정 예정 
		USkeletalMesh* HeadMesh2 = TempHead2.Object;
		SkeletalMeshBox.Add(2, HeadMesh2);
	}
}

// Called when the game starts
void UCACCharacterHead::BeginPlay()
{
	Super::BeginPlay();
}


