// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CAInteractable.h"

// Sets default values
ACAInteractable::ACAInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanInteract = true;
}

// Called when the game starts or when spawned
void ACAInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACAInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACAInteractable::CanInteract() const
{
	return bCanInteract;
}

void ACAInteractable::BeginTrace()
{
	//
}

void ACAInteractable::EndTrace()
{
	//
}

void ACAInteractable::BeginInteract(ACharacter* Initiator)
{
	bCanInteract = false;
}

void ACAInteractable::EndInteract(ACharacter* Initiator)
{
	bCanInteract = true;
}

