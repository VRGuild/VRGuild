// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CACCharacterPartBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values for this component's properties
UCACCharacterPartBase::UCACCharacterPartBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UCACCharacterPartBase::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = GetOwner();
	if (Owner->IsA<ATP_ThirdPersonCharacter>())
	{
		ATP_ThirdPersonCharacter* character = Cast<ATP_ThirdPersonCharacter>(Owner);
		CharacterSKM->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		CharacterSKM->SetLeaderPoseComponent(character->GetMesh());
	}

}

void UCACCharacterPartBase::SwitchSKM(int value)
{
	ServerSwitchSKM(value);
}

void UCACCharacterPartBase::ServerSwitchSKM_Implementation(int value)
{
	MulticastSwitchSKM(value);
}

void UCACCharacterPartBase::MulticastSwitchSKM_Implementation(int value)
{
	if (nullptr != CharacterSKM && SkeletalMeshBox.Find(value) != nullptr)
	{
		ValueSelected = value;
		CharacterSKM->SetSkeletalMesh(SkeletalMeshBox[ValueSelected].CustomSkeletalMesh);
	}
}