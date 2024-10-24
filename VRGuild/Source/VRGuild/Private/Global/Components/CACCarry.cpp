// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

#include "Global/Widgets/CWScrollBase.h"
#include "Global/CACarryInteractable.h"

UCACCarry::UCACCarry()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
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

void UCACCarry::StartCarry(ACACarryInteractable* ActorToHold)
{
	if (auto widgetClass = ActorToHold->GetPosterDisplayWidgetClass())
	{		
		if (ScrollBaseWidget)
		{
			ScrollBaseWidget->RemoveFromParent();
		}

		ScrollBaseWidget = CreateWidget<UCWScrollBase>(GetWorld(), ScrollBaseWidgetClass);
		ScrollBaseWidget->Init(widgetClass);

		ServerHold(ActorToHold->GetClass());
	}
}

void UCACCarry::StartDrop()
{
	if (/*ScrollBaseWidget && */ActorInHand)
	{
		ServerDrop();
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
	if (!ActorInHand) return TEXT("Default String");

	switch (ActorInHand->GetCarriedType())
	{
	case ECarriedType::COMMISSION:
	{
		return TEXT("Submit Commission");
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
	return TEXT("Default string");
}

ECarriedType UCACCarry::GetCarryType() const
{
	if (ActorInHand) return ActorInHand->GetCarriedType();
	
	return ECarriedType::NONE;
}

AActor* UCACCarry::GetCarriedActor() const
{
	return ActorInHand;
}

void UCACCarry::OnRep_ActorInHand()
{
	if (Owner && Owner->IsLocallyControlled())
	{
		if (ActorInHand)
		{
			if(ScrollBaseWidget)
				ScrollBaseWidget->AddToViewport();
		}
		else
		{
			if (ScrollBaseWidget)
				ScrollBaseWidget->RemoveFromParent();
		}
	}
}

void UCACCarry::ServerHold_Implementation(TSubclassOf<ACACarryInteractable> ActorToHold)
{
	if (Owner && ActorToHold)
	{
		ActorInHand = GetWorld()->SpawnActorDeferred<ACACarryInteractable>(ActorToHold, Owner->GetActorTransform());
		ActorInHand->Init(false, Owner, true);
		ActorInHand->FinishSpawning(Owner->GetActorTransform());

		if (ActorInHand)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Success %s"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"), *GetNameSafe(ActorInHand));
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