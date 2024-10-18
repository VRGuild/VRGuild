// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CACCharacterLower.h"

UCACCharacterLower::UCACCharacterLower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	CharacterSKM = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterLower"));

	SkeletalMeshBox.Add(0, nullptr);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempLower1(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (TempLower1.Succeeded())
	{ // TempHead1 Referecne 경로 수정 예정 
		USkeletalMesh* LowerMesh1 = TempLower1.Object;
		SkeletalMeshBox.Add(1, LowerMesh1);
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempLower2(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	{ // TempLower2 Referecne 경로 수정 예정 
		USkeletalMesh* LowerMesh2 = TempLower2.Object;
		SkeletalMeshBox.Add(2, LowerMesh2);
	}
}
