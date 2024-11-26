// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

#include "Global/Widgets/CWScrollBase.h"
#include "Global/CACarryInteractable.h"
#include "Global/Actors/CABasePoster.h"
#include "Hall/Board/CAReviewNotice.h"
#include "Global/CACarryInteractable.h"

#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

UCACCarry::UCACCarry()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);

	bProcessingHold = false;
}

void UCACCarry::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = GetOwner<ACharacter>();
}

void UCACCarry::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCACCarry, ActorInHand);
}

void UCACCarry::StartCarry(ACACarryInteractable* actorToHold)
{
	if (!ensure(ScrollBaseWidgetClass)) return;

	if (!actorToHold) return;

	UE_LOG(LogTemp, Warning, TEXT("Carry: 1111"));

	if (bProcessingHold) return;

	bProcessingHold = true;

	if (actorToHold->GetLocalRole() == ROLE_Authority && !Owner->HasAuthority())
	{
		//StartDrop(true);

		Read(actorToHold);
	}
	else
	{
		if (IsValid(ScrollBaseWidget))
		{
			UE_LOG(LogTemp, Warning, TEXT("Carry: 1111.1, remove %s from parent"), *GetNameSafe(ScrollBaseWidget));
			ScrollBaseWidget->RemoveFromParent();
			ScrollBaseWidget = nullptr;
		}

		UE_LOG(LogTemp, Warning, TEXT("Carry: 1111.2"));

		if (IsValid(ActorInHand))
		{
			ActorInHand->Destroy();
			ActorInHand = nullptr;
		}

		ServerHold(actorToHold);
	}	
}

void UCACCarry::StartDrop(bool bDoServerRPC)
{
	HideCarryWidget();

	if (ActorInHand)
	{
		if (IsValid(ScrollBaseWidget))
		{
			UE_LOG(LogTemp, Warning, TEXT("Carry: 1111.1, remove %s from parent"), *GetNameSafe(ScrollBaseWidget));
			ScrollBaseWidget->RemoveFromParent();
			ScrollBaseWidget = nullptr;
		}

		if (IsValid(ActorInHand))
		{
			ActorInHand->Destroy();
			ActorInHand = nullptr;
		}

		if (bDoServerRPC)
		{
			ServerDrop();
		}
	}
}

void UCACCarry::Read(ACACarryInteractable* ActorToRead)
{	
	if (auto Review = Cast<ACAReviewNotice>(ActorToRead))
	{
		ATP_ThirdPersonCharacter::SetInteracting(Owner, true);

		ReadWidget = Review->GetPosterDisplayWidget();

		ReadWidget->AddToViewport(-1);

		ActorRead = ActorToRead;
	}

	bProcessingHold = false;
}

void UCACCarry::StopReading()
{
	ATP_ThirdPersonCharacter::SetInteracting(Owner, false);
	ReadWidget->RemoveFromParent();
	ReadWidget = nullptr;
	ActorRead = nullptr;
}

void UCACCarry::HideCarryWidget()
{
	if (ScrollBaseWidget && ActorInHand)
	{
		if (ScrollBaseWidget->IsVisible())
		{
			ScrollBaseWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UCACCarry::UnHideCarryWidget()
{
	if (ScrollBaseWidget && ActorInHand)
	{
		if (!ScrollBaseWidget->IsVisible())
		{
			ScrollBaseWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

FGameplayTagContainer UCACCarry::GetGameplayTagContainer() const
{
	if (ActorInHand)
	{
		return ActorInHand->GetGameplayTagContainer();
	}
	return FGameplayTagContainer();
}

FString UCACCarry::GetMessageForNPC()
{
	if (!ActorInHand) return TEXT("");

	switch (ActorInHand->GetCarriedType())
	{
	case ECarriedType::COMMISSION:
	{
		return TEXT("Apply for Commission");
	}
	case ECarriedType::REGISTRATION:
	{
		return TEXT("Submit Registration");
	}
	case ECarriedType::NONE:
	{
		return TEXT("No carried objects");
	}
	}
	return TEXT("");
}

ECarriedType UCACCarry::GetCarryType() const
{
	if (ActorInHand)
	{
		return ActorInHand->GetCarriedType();
	}
	return ECarriedType::NONE;
}

ACACarryInteractable* UCACCarry::GetCarriedActor() const
{
	return ActorInHand;
}

void UCACCarry::DestroyActorRead()
{
	if (ActorRead)
	{
		ActorRead->Destroy();
		StopReading();
	}
}

void UCACCarry::OnRep_ActorInHand()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Carry: 3333"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
	if (Owner && Owner->IsLocallyControlled())
	{
		if (auto actor = Cast<ACABasePoster>(ActorInHand))
		{
			auto widgetToDisplay = actor->GetPosterDisplayWidget();
			if (ensure(widgetToDisplay))
			{
				ScrollBaseWidget = CreateWidget<UCWScrollBase>(GetWorld(), ScrollBaseWidgetClass);
				ScrollBaseWidget->Init(widgetToDisplay);
				ScrollBaseWidget->AddToViewport(-1);
			}
			else UE_LOG(LogTemp, Warning, TEXT("no widget to display in StartCarry()"));
		}
		else
		{
			if (ScrollBaseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("[%s] Carry: 3333.1 Remove from Parent"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
				ScrollBaseWidget->RemoveFromParent();
				ScrollBaseWidget = nullptr;
				
			}
		}
	}

	bProcessingHold = false;
}

void UCACCarry::ServerHold_Implementation(ACACarryInteractable* actorToHold)
{
	UE_LOG(LogTemp, Warning, TEXT("Carry: 2222"));

	if (ActorInHand)
	{
		ActorInHand->Destroy();
		ActorInHand = nullptr;
		OnRep_ActorInHand();
	}

	if (Owner && actorToHold)
	{
		UE_LOG(LogTemp, Warning, TEXT("Carry: 2222.1"));

		ActorInHand = GetWorld()->SpawnActorDeferred<ACACarryInteractable>(actorToHold->GetClass(), Owner->GetActorTransform());
		ActorInHand->Init(false, Owner, true, actorToHold);
		ActorInHand->FinishSpawning(Owner->GetActorTransform());

		if (ActorInHand)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Success %s"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"), *GetNameSafe(ActorInHand));

			if (ActorInHand->IsA<ACABasePoster>())
			{
				auto posterHeld = Cast<ACABasePoster>(ActorInHand);
				posterHeld->BindOnCompletedDelegate(Cast<ACABasePoster>(actorToHold));
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("%s Failed"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"));

		OnRep_ActorInHand();
	}
}

void UCACCarry::ServerDrop_Implementation()
{
	if (Owner && ActorInHand)
	{
		ActorInHand->Destroy();
		ActorInHand = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("%s ActorInHand destroyed "), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"));

		OnRep_ActorInHand();
	}
	else UE_LOG(LogTemp, Warning, TEXT("%s Missing ActorInHand"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"));
}