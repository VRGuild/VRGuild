// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CACommissionPoster.h"
#include "Components/StaticMeshComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

ACACommissionPoster::ACACommissionPoster()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);
	bReplicates = true;
}

void ACACommissionPoster::BeginTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("ACACommisionPoster BeginTrace"));
}

void ACACommissionPoster::EndTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("ACACommisionPoster EndTrace"));
}

void ACACommissionPoster::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACommisionPoster BeginInteract"));

	auto character = Cast<ATP_ThirdPersonCharacter>(Initiator);
	if (character)
	{
		UE_LOG(LogTemp, Warning, TEXT("1111"));
		character->HoldPoster(SelfActor, PosterWidgetToDisplayClass);
	}
}

void ACACommissionPoster::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);
	UE_LOG(LogTemp, Warning, TEXT("ACACommisionPoster EndInteract"));
}
