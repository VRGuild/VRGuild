// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAReceptionist.h"
#include "Global/Components/CACCarry.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACInteraction.h"

void ACAReceptionist::BeginTrace(ACharacter* Initiator)
{	
	if(!Initiator) return;

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginTrace"));

	if(auto CarryComponent = Initiator->GetComponentByClass<UCACCarry>())
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

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginINteract"));
}

void ACAReceptionist::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);

	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist EndINteract"));
}
