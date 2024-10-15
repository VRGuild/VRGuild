// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAReceptionist.h"

void ACAReceptionist::BeginTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("ACAReceptionist BeginTrace"));
}

void ACAReceptionist::EndTrace()
{
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
