// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CACarryInteractable.h"
#include "Components/StaticMeshComponent.h"

#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Global/Components/CACCarry.h"



ACACarryInteractable::ACACarryInteractable()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);
	bReplicates = true;

	StaticMeshComp->SetCollisionProfileName("Interactable");
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
			UE_LOG(LogTemp, Warning, TEXT("1111"));
			carryComponent->StartCarry(ECarriedType::COMMISSION, SelfActor, PosterWidgetToDisplayClass);
		}
	}	
}

void ACACarryInteractable::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACarryInteractable EndInteract"));
}
