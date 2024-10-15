// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CACCharacterBody.h"

UCACCharacterBody::UCACCharacterBody()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	CharacterSKM = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterBody"));

	SkeletalMeshBox.Add(0, nullptr);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempBody1(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (TempBody1.Succeeded())
	{ // TempHead1 Referecne 경로 수정 예정 
		USkeletalMesh* BodyMesh1 = TempBody1.Object;
		SkeletalMeshBox.Add(1, BodyMesh1);
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempBody2(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	{ // TempBody2 Referecne 경로 수정 예정 
		USkeletalMesh* BodyMesh2 = TempBody2.Object;
		SkeletalMeshBox.Add(2, BodyMesh2);
	}
}
