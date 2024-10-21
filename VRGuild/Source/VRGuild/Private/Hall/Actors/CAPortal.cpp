// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAPortal.h"

void ACAPortal::BeginTrace(ACharacter* Initiator)
{
	UE_LOG(LogTemp, Warning, TEXT("ACAPortal BeginTrace"));
}

void ACAPortal::EndTrace(ACharacter* Initiator)
{
	UE_LOG(LogTemp, Warning, TEXT("ACAPortal EndTrace"));
}

void ACAPortal::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACAPortal BeginINteract"));
}

void ACAPortal::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACAPortal EndINteract"));
}
