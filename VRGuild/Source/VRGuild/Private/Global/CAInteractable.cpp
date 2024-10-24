// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CAInteractable.h"
#include "Global/CGIGameInstance.h"

// Sets default values
ACAInteractable::ACAInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TraceMessage = TEXT("Default Msg");
}

FGameplayTagContainer ACAInteractable::GetGameplayTagContainer() const
{
	return InteractionTag;
}

// Called when the game starts or when spawned
void ACAInteractable::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = GetWorld()->GetGameInstance<UCGIGameInstance>();
}

void ACAInteractable::SetTraceMessage(FString newMsg)
{
	TraceMessage = newMsg;
}

FString ACAInteractable::GetTraceMessage() const
{
	return TraceMessage;
}

// Called every frame
void ACAInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACAInteractable::CanInteract(ACharacter* Initiator) const
{
	return true;
}

void ACAInteractable::BeginTrace(ACharacter* Initiator)
{
	if (ensure(GameInstance))
	{
		GameInstance->DisplayTraceMessage(true, TraceMessage);
	}
}

void ACAInteractable::EndTrace(ACharacter* Initiator)
{
	if (ensure(GameInstance))
	{
		GameInstance->DisplayTraceMessage(false, TraceMessage);
	}
}

void ACAInteractable::BeginInteract(ACharacter* Initiator)
{
	//
}

void ACAInteractable::EndInteract(ACharacter* Initiator)
{
	//
}

void ACAInteractable::OnRep_Owner()
{
	Super::OnRep_Owner();
}

