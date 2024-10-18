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

}



