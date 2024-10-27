// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Actors/CAPortal.h"
#include "Global/Components/CACInteraction.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

ACAPortal::ACAPortal()
{
	BoxOverlap->SetCollisionProfileName("Portal");
}

bool ACAPortal::CanTrace(ACharacter* Initiator) const
{
	//return Super::CanTrace(Initiator);
	return false;
}

bool ACAPortal::CanInteract(ACharacter* Initiator) const
{
	return Super::CanInteract(Initiator);
}

void ACAPortal::BeginTrace(ACharacter* Initiator)
{
	Super::BeginTrace(Initiator);
}

void ACAPortal::EndTrace(ACharacter* Initiator)
{
	Super::EndTrace(Initiator);
}

void ACAPortal::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);
	
	StartDisplay();
}

void ACAPortal::EndInteract(ACharacter* Initiator)
{
	Super::EndInteract(Initiator);
}

void ACAPortal::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (OtherActor->HasAuthority()) return;

	UE_LOG(LogTemp, Warning, TEXT("1Overlapped %s"), *GetNameSafe(OtherComp));

	if (bOverlapped) return;
	
	if (auto character = Cast<ACharacter>(OtherActor))
	{
		if (character->IsLocallyControlled())
		{
			bOverlapped = true;
			BeginInteract(character);
		}
	}
}

void ACAPortal::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	if (OtherActor->HasAuthority()) return;
	
	if (!bOverlapped) return;

	bOverlapped = false;
}
