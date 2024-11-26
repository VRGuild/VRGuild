// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CADisplayer.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACCarry.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Global/Components/CACCharacterAnimMontage.h"
#include "Global/Components/CWCDisplayScroll.h"

ACADisplayer::ACADisplayer()
{
	SetReplicates(true);
	bNetUseOwnerRelevancy = true;
	ErrorMessage = TEXT("Cannot Interact: You don't have a commission in hand");
	DisplayMessage = TEXT("Place Commission");
	PickupMessage = TEXT("Pick up displayed actor");

	WidgetComponent = CreateDefaultSubobject<UCWCDisplayScroll>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	/*WidgetComponent2 = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent2");
	WidgetComponent2->SetupAttachment(WidgetComponent);
	WidgetComponent2->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	WidgetComponent2->SetRelativeLocation(FVector(1.f, 0.f, 0.f));
	WidgetComponent2->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);*/

	BoxOverlap->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ACADisplayer::BeginPlay()
{
	Super::BeginPlay();
}

//void ACADisplayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (PlayerThatStartedInteracting)
//	{
//		UpdatedMousePos = PlayerThatStartedInteracting->GetMousePos();
//
//		OnMousePressInteract(StartMousePos - UpdatedMousePos);
//	}	
//}

void ACADisplayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACADisplayer, ActorDisplayed);
}

bool ACADisplayer::CanTrace(ACharacter* initiator) const
{
	if (ActorDisplayed)
	{
		return (Owner == initiator && initiator->IsLocallyControlled());
	}

	return Super::CanTrace(initiator);
}

bool ACADisplayer::CanInteract(ACharacter* initiator) const
{
	return Super::CanInteract(initiator);
}

void ACADisplayer::BeginTrace(ACharacter* initiator)
{
	Super::BeginTrace(initiator);
}

void ACADisplayer::EndTrace(ACharacter* initiator)
{
	Super::EndTrace(initiator);

	/*if (ActorDisplayed)
	{
		SetActorTickEnabled(false);

		if (auto carry = PlayerThatStartedInteracting->GetComponentByClass<UCACCarry>())
		{
			carry->UnHideCarryWidget();
		}
	}*/
}

void ACADisplayer::EndScroll(ACharacter* initiator)
{

}

void ACADisplayer::BeginInteract(ACharacter* initiator)
{
	Super::BeginInteract(initiator);

	if (!initiator) return;

	/*if (ActorDisplayed)
	{
		SetActorTickEnabled(true);

		PlayerThatStartedInteracting = Cast<ATP_ThirdPersonCharacter>(initiator);

		if (auto carry = PlayerThatStartedInteracting->GetComponentByClass<UCACCarry>())
		{
			carry->HideCarryWidget();
		}
				
		StartMousePos = PlayerThatStartedInteracting->GetMousePos();		
	}
	else
	{
		
	}*/	

	if (auto carryComp = initiator->GetComponentByClass<UCACCarry>())
	{
		switch (carryComp->GetCarryType())
		{
		case ECarriedType::COMMISSION:
		{
			AActor* actorCarried = carryComp->GetCarriedActor();
			if (ensure(actorCarried) && !ActorDisplayed)
			{
				PlayerInitiated = initiator;
				ATP_ThirdPersonCharacter::SetOwnerFor(this, initiator);

				if (auto montageComp = initiator->GetComponentByClass<UCACCharacterAnimMontage>())
				{
					montageComp->StartAnimMontage(EAnimMontageType::PICKDOWN);
				}
			}
			break;
		}
		case ECarriedType::NONE:
		{
			ServerPickupCommission(initiator);
			UE_LOG(LogTemp, Warning, TEXT("Not nice"));


			if (auto montageComp = initiator->GetComponentByClass<UCACCharacterAnimMontage>())
			{
				montageComp->StartAnimMontage(EAnimMontageType::PICKDOWN);
			}
			break;
		}
		}
	}
}

void ACADisplayer::EndInteract(ACharacter* initiator)
{
	Super::EndInteract(initiator);

	if (!initiator) return;

	if (auto carryComp = initiator->GetComponentByClass<UCACCarry>())
	{
		switch (carryComp->GetCarryType())
		{
		case ECarriedType::COMMISSION:
		{

			break;
		}
		case ECarriedType::NONE:
		{
			if (ActorDisplayed && ensureAlways(Owner == initiator))
			{
				if (ActorDisplayed)
				{
					ServerPickupCommission(initiator);
				}
			}
			break;
		}
		}
	}
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
				UE_LOG(LogTemp, Warning, TEXT("ActorDisplayed: %s"), *GetNameSafe(ActorDisplayed));
				ServerDisplayCommission(actorCarried);
			}
			else UE_LOG(LogTemp, Warning, TEXT("ACADisplayer, OnRep_Owner, no carried actor in UCACCarryComponent"));
		}
	}
	else
	{
		/*if (WidgetComponent)
		{
			WidgetComponent->SetWidgetClass(nullptr);
		}*/
	}
}

FString ACADisplayer::GetTraceMessage(ACharacter* player) const
{
	Super::GetTraceMessage(player);

	bool bCan = false;

	UE_LOG(LogTemp, Warning, TEXT("BeginTrace"));

	if (auto carryComp = player->GetComponentByClass<UCACCarry>())
	{
		bCan = carryComp->GetCarryType() == ECarriedType::COMMISSION;
	}

	FString Message = bCan ? DisplayMessage : ErrorMessage;

	if (ActorDisplayed && Owner == player && player->IsLocallyControlled())
		Message = PickupMessage;

	return Message;
}

void ACADisplayer::OnRep_ActorDisplayed()
{
	if (ActorDisplayed)
	{
		Enabled(true);
		PlayerInitiated = nullptr;
	}
	else
	{
		Enabled(false);
		PlayerInitiated = nullptr;
	}

	//if (!WidgetComponent) return;

	//if (ActorDisplayed)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Success in displaying Actor Displayed"));
	//			
	//	WidgetComponent->SetWidget(ActorDisplayed->GetPosterDisplayWidget());
	//	WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);

	//	StartAnimateScrolling();

	//	/*WidgetComponent->SetTwoSided(true);

	//	WidgetComponent2->SetWidgetClass(BackSideWidgetClass);
	//	WidgetComponent2->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);*/
	//}
	//else
	//{
	//	WidgetComponent->SetWidget(nullptr);
	//	WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	//	StopAnimateScrolling();

	//	/*WidgetComponent2->SetWidget(nullptr);
	//	WidgetComponent2->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);*/
	//}	
}

void ACADisplayer::ServerDisplayCommission_Implementation(AActor* commissionPassed)
{
	if (auto actorSpawned = GetWorld()->SpawnActorDeferred<ACAProjectNotice>(commissionPassed->GetClass(), GetActorTransform(), this,
		nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
	{
		ActorDisplayed = actorSpawned;
		
		ActorDisplayed->Init(false, Cast<ACharacter>(Owner), false, commissionPassed);
				
		ActorDisplayed->FinishSpawning(GetActorTransform());
		
		UE_LOG(LogTemp, Warning, TEXT("ActorDisplayed: %s, commissionPassed: %s"), *GetNameSafe(ActorDisplayed), *GetNameSafe(commissionPassed));
		if (auto carryComp = Owner->GetComponentByClass<UCACCarry>())
		{
			if (ActorDisplayed)
			{
				carryComp->StartDrop(true);
			}
			//else Spawn ActorDisplayed in players hand. carryComp->StartCarry(ECarriedType::NONE,  );
		}
	}	
}

void ACADisplayer::ServerPickupCommission_Implementation(ACharacter* player)
{
	if (!player || !Owner) return;
	
	if (Owner == player)
	{
		if (auto carryComp = player->GetComponentByClass<UCACCarry>())
		{	
			carryComp->StartCarry(ActorDisplayed);
			SetOwner(nullptr);
			ActorDisplayed->SetActorHiddenInGame(true);
			ActorDisplayed->SetLifeSpan(10.f);
			ActorDisplayed = nullptr;
		}
	}
}
