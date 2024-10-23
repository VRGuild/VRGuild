// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAReceptionist.h"
#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACInteraction.h"

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
		SetTraceMessage(CarryComponent->GetMessageForNPC());
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
		if (auto interactComp = Initiator->GetComponentByClass<UCACInteraction>())
		{
			interactComp->Disable();
		}

		auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Initiator->GetController<APlayerController>()->GetLocalPlayer());
		if (EnhancedInputSubsystem)
		{
			if (ensure(DefaultInputContext) && EnhancedInputSubsystem->HasMappingContext(DefaultInputContext))
			{
				EnhancedInputSubsystem->RemoveMappingContext(DefaultInputContext);
			}

			if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
			{
				switch (carryComp->GetCarryType())
				{
				case ECarriedType::COMMISSION:
				{
					DisplayCommossionPopup(true);
					if (ensure(ScrollInputContext) && EnhancedInputSubsystem->HasMappingContext(ScrollInputContext))
					{
						EnhancedInputSubsystem->RemoveMappingContext(ScrollInputContext);
					}
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

		Initiator->GetController<APlayerController>()->SetShowMouseCursor(true);
	}



	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginINteract"));
}

void ACAReceptionist::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);

	if (Initiator)
	{
		if (auto InteractComp = Initiator->GetComponentByClass<UCACInteraction>())
		{
			InteractComp->Enable();
		}

		auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Initiator->GetController<APlayerController>()->GetLocalPlayer());
		if (EnhancedInputSubsystem)
		{
			if (ensure(DefaultInputContext) && !EnhancedInputSubsystem->HasMappingContext(DefaultInputContext))
			{
				EnhancedInputSubsystem->AddMappingContext(DefaultInputContext, 0);
			}

			if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
			{
				switch (carryComp->GetCarryType())
				{
				case ECarriedType::COMMISSION:
				{
					DisplayCommossionPopup(true);
					if (ensure(ScrollInputContext) && !EnhancedInputSubsystem->HasMappingContext(ScrollInputContext))
					{
						EnhancedInputSubsystem->AddMappingContext(ScrollInputContext, 0);
					}
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

		Initiator->GetController<APlayerController>()->SetShowMouseCursor(false);
	}

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist EndINteract"));
}