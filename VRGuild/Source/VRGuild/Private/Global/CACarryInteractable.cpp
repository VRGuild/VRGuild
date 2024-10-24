// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CACarryInteractable.h"
#include "Components/StaticMeshComponent.h"

#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Global/Components/CACCarry.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

ACACarryInteractable::ACACarryInteractable()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);
	bReplicates = true;
	bEnabled = true;
	StaticMeshComp->SetCollisionProfileName("Interactable");

	HeldScale = FVector(.5f);
	HoldSocketName = "RightSocketHold";
}

void ACACarryInteractable::BeginPlay()
{
	Super::BeginPlay();
	if (!bEnabled)
	{
		SetActorScale3D(HeldScale);
		StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	}
}

void ACACarryInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACACarryInteractable, bEnabled);
}

void ACACarryInteractable::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner)
{
	bEnabled = bIsEnabled;
	if (owner)
	{
		SetOwner(owner);
	}

	if (bAttachToOwner)
	{
		AttachToComponent(owner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, HoldSocketName);
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
			carryComponent->StartCarry(ECarriedType::COMMISSION, SelfActor, PosterWidgetToDisplayClass);
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
			carryComponent->StartDrop();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable EndInteract"));
}

FVector ACACarryInteractable::GetHeldScale() const
{
	return HeldScale;
}

TSubclassOf<UUserWidget> ACACarryInteractable::GetPosterDisplayWidgetClass() const
{
	return PosterWidgetToDisplayClass;
}
