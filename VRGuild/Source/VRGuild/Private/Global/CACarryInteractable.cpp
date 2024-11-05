// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CACarryInteractable.h"
#include "Components/StaticMeshComponent.h"

#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Global/Components/CACCarry.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

#include "Blueprint/UserWidget.h"

#include "Engine/SkeletalMeshSocket.h"

ACACarryInteractable::ACACarryInteractable()
{
	bReplicates = true;
	bEnabled = true;

	HeldScale = FVector(.5f);
	RelativeSocketRot = FRotator(0.f);
	RelativeSocketLoc = FVector(0.f);

	HoldSocketName = "RightSocketHold";
	CarryType = ECarriedType::NONE;
}

void ACACarryInteractable::BeginPlay()
{
	Super::BeginPlay();
	if (!bEnabled)
	{
		SetActorScale3D(HeldScale);
	}
}

void ACACarryInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACACarryInteractable, bEnabled);
}

void ACACarryInteractable::OnRep_bEnabled()
{
	//
}

void ACACarryInteractable::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorInteracted)
{
	bEnabled = bIsEnabled;
	OnRep_bEnabled();
	if (owner)
	{
		SetOwner(owner);
	}

	if (bAttachToOwner)
	{

		if (owner->GetMesh()->DoesSocketExist(HoldSocketName))
		{
			/*FTransform socketTransform;
			socketTransform.SetTranslation(RelativeSocketLoc);
			socketTransform.SetRotation(RelativeSocketRot.Quaternion());
			socketTransform.SetScale3D(HeldScale);
			SetActorTransform(socketTransform);*/

			//FTransform socketTransform;
			//int32 outBoneIndex;
			//owner->GetMesh()->GetSocketInfoByName(HoldSocketName, socketTransform, outBoneIndex);
			//
			//UE_LOG(LogTemp, Warning, TEXT("Trans before: %s"), *socketTransform.ToString());
			//
			//socketTransform.SetTranslation(RelativeSocketLoc);
			//socketTransform.SetRotation(RelativeSocketRot.Quaternion());
			//socketTransform.SetScale3D(HeldScale);

			//owner->GetMesh()->GetSocketInfoByName(HoldSocketName, socketTransform, outBoneIndex);
			//
			//UE_LOG(LogTemp, Warning, TEXT("Trans after: %s"), *socketTransform.ToString());

			AttachToComponent(owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HoldSocketName);

			UE_LOG(LogTemp, Warning, TEXT("SUCCESS"));
		}
		else UE_LOG(LogTemp, Warning, TEXT("NONE"));
		//else
		//{			
		//	USkeletalMeshSocket* NewSocket = NewObject<USkeletalMeshSocket>(owner->GetMesh()->SkeletalMesh);
		//	NewSocket->SocketName = HoldSocketName;
		//	NewSocket->RelativeLocation = RelativeSocketLoc;
		//	NewSocket->RelativeRotation = RelativeSocketRot;
		//	NewSocket->RelativeScale = HeldScale;

		//	// Add the socket to the skeletal mesh
		//	owner->GetMesh()->SkeletalMesh->AddSocket(NewSocket, true);
		//}		
	}
}

bool ACACarryInteractable::CanTrace(ACharacter* Initiator) const
{
	return bEnabled;
}

void ACACarryInteractable::BeginTrace(ACharacter* Initiator)
{
	Super::BeginTrace(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable BeginTrace"));
}

void ACACarryInteractable::EndTrace(ACharacter* Initiator)
{
	Super::EndTrace(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable EndTrace"));
}

void ACACarryInteractable::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable BeginInteract"));

	if (Initiator)
	{
		if (auto carryComponent = Initiator->GetComponentByClass<UCACCarry>())
		{
			carryComponent->StartCarry(this);
		}
	}
}

void ACACarryInteractable::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);
	if (Initiator)
	{
		if (auto carryComponent = Initiator->GetComponentByClass<UCACCarry>())
		{
			carryComponent->StartDrop(true);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable EndInteract"));
}

FVector ACACarryInteractable::GetHeldScale() const
{
	return HeldScale;
}

ECarriedType ACACarryInteractable::GetCarriedType() const
{
	return CarryType;
}

bool ACACarryInteractable::IsEnabled() const
{
	return bEnabled;
}
