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
	if (!ensure(ScrollBaseWidgetClass)) return;
	UE_LOG(LogTemp, Warning, TEXT("Carry: 1111"));

	auto widgetToDisplay = ActorToHold->GetPosterDisplayWidget();
	if (ensure(widgetToDisplay))
	{
		if (ScrollBaseWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Carry: 1111.1, remove %s from parent"), *GetNameSafe(ScrollBaseWidget));
			ScrollBaseWidget->RemoveFromParent();
			ScrollBaseWidget = nullptr;
		}

		UE_LOG(LogTemp, Warning, TEXT("Carry: 1111.2"));
		ScrollBaseWidget = CreateWidget<UCWScrollBase>(GetWorld(), ScrollBaseWidgetClass);
		ScrollBaseWidget->Init(widgetToDisplay);

		ServerHold(ActorToHold->GetClass());

		
	}
	else UE_LOG(LogTemp, Warning, TEXT("no widget to display in StartCarry()"));
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
	UE_LOG(LogTemp, Warning, TEXT("[%s] Carry: 3333"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
	if (Owner && Owner->IsLocallyControlled())
	{
		if (ActorInHand)
		{
			if (ScrollBaseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("[%s] Carry: 3333.1 Add to Viewport"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
				ScrollBaseWidget->AddToViewport();
			}
		}
		else
		{
			if (ScrollBaseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("[%s] Carry: 3333.1 Remove from Parent"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
				ScrollBaseWidget->RemoveFromParent();
			}
		}
	}
}

void UCACCarry::ServerHold_Implementation(TSubclassOf<ACACarryInteractable> ActorToHold)
{
	UE_LOG(LogTemp, Warning, TEXT("Carry: 2222"));
	if (Owner && ActorToHold)
	{
		UE_LOG(LogTemp, Warning, TEXT("Carry: 2222.1"));

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