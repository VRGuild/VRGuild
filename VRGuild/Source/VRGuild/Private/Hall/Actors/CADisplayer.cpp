// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CADisplayer.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACCarry.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"

#include "Global/CACarryInteractable.h"

ACADisplayer::ACADisplayer()
{
	SetReplicates(true);
	bNetUseOwnerRelevancy = true;
	ErrorMessage = TEXT("Cannot Interact: You don't have a commission in hand");
	DisplayMessage = TEXT("Place Commission");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

bool ACADisplayer::CanInteract(ACharacter* Initiator) const
{
	if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
	{
		return carryComp->GetCarryType() == ECarriedType::COMMISSION;
	}

	return false;
}

void ACADisplayer::BeginTrace(ACharacter* Initiator)
{
	FString Message = !CanInteract(Initiator) ? ErrorMessage : DisplayMessage;
	SetTraceMessage(Message);

	Super::BeginTrace(Initiator);
}

void ACADisplayer::EndTrace(ACharacter* Initiator)
{
	Super::EndTrace(Initiator);
}

void ACADisplayer::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);

	if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
	{
		switch (carryComp->GetCarryType())
		{
		case ECarriedType::COMMISSION:
		{
			AActor* actorCarried = carryComp->GetCarriedActor();
			if (ensure(actorCarried) && !ActorDisplayed)
			{
				UE_LOG(LogTemp, Warning, TEXT("1111"));
				ATP_ThirdPersonCharacter::SetOwnerFor(this, Initiator);

			}
			break;
		}
		case ECarriedType::NONE:
		{
			break;
		}
		}
	}
}

void ACADisplayer::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);

	if (auto carryComp = Initiator->GetComponentByClass<UCACCarry>())
	{
		switch (carryComp->GetCarryType())
		{
		case ECarriedType::COMMISSION:
		{
			if (ActorDisplayed)
			{
				ATP_ThirdPersonCharacter::SetOwnerFor(this, nullptr);
			}
			break;
		}
		case ECarriedType::NONE:
		{
			break;
		}
		}
	}
}

void ACADisplayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACADisplayer, ActorDisplayed);
}

void ACADisplayer::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	if (Owner)
	{
		if (auto carryComp = Owner->GetComponentByClass<UCACCarry>())
		{
			auto actorCarried = carryComp->GetCarriedActor();
			if (ensure(actorCarried))
			{
				UE_LOG(LogTemp, Warning, TEXT("3333"));
				UE_LOG(LogTemp, Warning, TEXT("ActorDisplayed: %s"), *GetNameSafe(ActorDisplayed));
				ServerDisplayCommission(actorCarried);
			}
			else UE_LOG(LogTemp, Warning, TEXT("ACADisplayer, OnRep_Owner, no carried actor in UCACCarryComponent"));
		}
	}
	else ServerDisplayCommission(nullptr);
}

void ACADisplayer::OnRep_ActorDisplayed()
{
	if (ActorDisplayed)
	{
		UE_LOG(LogTemp, Warning, TEXT("5555 -- add widget"));
		UE_LOG(LogTemp, Warning, TEXT("Success in displaying Actor Displayed"));
				
		WidgetComponent->SetWidgetClass(ActorDisplayed->GetPosterDisplayWidgetClass());
	}
	else
	{
		WidgetComponent->SetWidgetClass(nullptr);
		UE_LOG(LogTemp, Warning, TEXT("5555 -- remove widget"));
	}
	
}

void ACADisplayer::ServerDisplayCommission_Implementation(AActor* commissionPassed)
{
	if (auto actorSpawned = GetWorld()->SpawnActorDeferred<ACACarryInteractable>(commissionPassed->GetClass(), GetActorTransform(), this,
		nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
	{
		ActorDisplayed = actorSpawned;
		
		ActorDisplayed->Init(false, Cast<ACharacter>(Owner), false);
				
		ActorDisplayed->FinishSpawning(GetActorTransform());
		
		UE_LOG(LogTemp, Warning, TEXT("ActorDisplayed: %s, commissionPassed: %s"), *GetNameSafe(ActorDisplayed), *GetNameSafe(commissionPassed));
		if (auto carryComp = Owner->GetComponentByClass<UCACCarry>())
		{
			if (ActorDisplayed)
			{
				UE_LOG(LogTemp, Warning, TEXT("4444"));
				carryComp->StartDrop();
			}
			//else Spawn ActorDisplayed in players hand. carryComp->StartCarry(ECarriedType::NONE,  );
		}
	}	
}
