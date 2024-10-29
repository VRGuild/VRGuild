// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAReceptionist.h"
#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACInteraction.h"
#include "Global/CACarryInteractable.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ACAReceptionist::BeginPlay()
{
	Super::BeginPlay();
}

void ACAReceptionist::BeginTrace(ACharacter* Initiator)
{
	if (!Initiator) return;

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginTrace"));

	if (auto CarryComponent = Initiator->GetComponentByClass<UCACCarry>())
	{
		FString message = CarryComponent->GetMessageForNPC();
		
		if (message == TEXT("")) message = GetTraceMessage();
		
		SetTraceMessage(message);
	}

	Super::BeginTrace(Initiator);
}

void ACAReceptionist::EndTrace(ACharacter* Initiator)
{
	Super::EndTrace(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist EndTrace"));
}

void ACAReceptionist::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);

	if (Initiator)
	{
		ATP_ThirdPersonCharacter::SetInteracting(Initiator, true);

		if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
		{
			switch (carryComp->GetCarryType())
			{
			case ECarriedType::COMMISSION:
			{
				DisplayCommossionPopup(true);
				break;
			}
			case ECarriedType::REGISTRATION:
			{
				break;
			}
			case ECarriedType::NONE:
			{
				DisplayDefaultPopup(true);
				break;
			}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginINteract"));
}

void ACAReceptionist::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);

	if (Initiator)
	{
		ATP_ThirdPersonCharacter::SetInteracting(Initiator, false);

		if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
		{
			switch (carryComp->GetCarryType())
			{
			case ECarriedType::COMMISSION:
			{
				DisplayCommossionPopup(true);
				break;
			}
			case ECarriedType::REGISTRATION:
			{
				break;
			}
			case ECarriedType::NONE:
			{
				DisplayDefaultPopup(false);
				break;
			}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist EndINteract"));
}