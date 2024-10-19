// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

#include "Global/Widgets/CWScrollBase.h"

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

void UCACCarry::StartCarry(ECarriedType Type, TSubclassOf<AActor> ActorToHold, TSubclassOf<UUserWidget> WidgetToDisplay)
{
	if (WidgetToDisplay)
	{
		ScrollBaseWidget = CreateWidget<UCWScrollBase>(GetWorld(), ScrollBaseWidgetClass);

		if (ScrollBaseWidget && ScrollBaseWidget->Init(WidgetToDisplay))
		{
			UE_LOG(LogTemp, Warning, TEXT("2222"));
			ServerHoldPoster(ActorToHold);
		}
	}
}

FString UCACCarry::GetMessageForNPC()
{
	return FString();
}

void UCACCarry::OnRep_ActorInHand()
{
	if (Owner && Owner->IsLocallyControlled())
	{
		if (ActorInHand)
		{
			if (ScrollBaseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("4444"));
				ScrollBaseWidget->AddToViewport();
			}
		}
		else
		{
			if (!ScrollBaseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("5555"));
				ScrollBaseWidget->RemoveFromParent();
			}
		}
	}
}

void UCACCarry::ServerHoldPoster_Implementation(TSubclassOf<AActor> ActorToHold)
{
	UE_LOG(LogTemp, Warning, TEXT("3333"));
	if (Owner && ActorToHold)
	{
		ActorInHand = GetWorld()->SpawnActor<AActor>(ActorToHold, Owner->GetActorTransform());
		if (ActorInHand)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Success %s"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"),
				*GetNameSafe(ActorInHand));
		}
		else UE_LOG(LogTemp, Warning, TEXT("%s Failed"), GetWorld()->GetNetMode() == NM_Client ? TEXT("CLIENT") : TEXT("SERVER"));
	}
}