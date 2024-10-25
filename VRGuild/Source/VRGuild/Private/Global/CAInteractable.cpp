// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CAInteractable.h"
#include "Global/CGIGameInstance.h"
#include "Components/BoxComponent.h"
#include "../../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Global/Components/CACInteraction.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ACAInteractable::ACAInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TraceMessage = TEXT("Default Msg");
	bIsInteracting = false;
	
	RootComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = RootComp;
	
	BoxOverlap = CreateDefaultSubobject<UBoxComponent>("PlayerBoxOverlap");
	BoxOverlap->SetupAttachment(RootComp);
	BoxOverlap->SetBoxExtent(FVector(200.f));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComp);
	StaticMeshComp->SetCollisionProfileName("Interactable");

	SetHideMesh(false);
}

FGameplayTagContainer ACAInteractable::GetGameplayTagContainer() const
{
	return InteractionTag;
}

// Called when the game starts or when spawned
void ACAInteractable::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp->SetHiddenInGame(bHideMesh);

	GameInstance = GetWorld()->GetGameInstance<UCGIGameInstance>();

	if (BoxOverlap)
	{
		BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPlayerOverlapBegin);
		BoxOverlap->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnPlayerOverlapEnd);
	}
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

bool ACAInteractable::CanTrace(ACharacter* Initiator) const
{
	return true;
}

bool ACAInteractable::CanInteract(ACharacter* Initiator) const
{
	return true;
}

bool ACAInteractable::IsInteracting(ACharacter* Initiator) const
{
	return bIsInteracting;
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
	bIsInteracting = true;
}

void ACAInteractable::EndInteract(ACharacter* Initiator)
{
	bIsInteracting = false;
}

void ACAInteractable::OnRep_Owner()
{
	Super::OnRep_Owner();
}

void ACAInteractable::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->HasAuthority()) return;

	if (auto character = Cast<ATP_ThirdPersonCharacter>(OtherActor))
	{
		if (auto interactionComp = character->GetComponentByClass<UCACInteraction>())
		{
			if (!interactionComp->IsEnabled())
			{
				
			}	
			//UE_LOG(LogTemp, Warning, TEXT("Overlap begin with %s"), *GetNameSafe(OtherActor));
			interactionComp->Enable(this);
		}
	}

}

void ACAInteractable::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->HasAuthority()) return;

	if (auto character = Cast<ATP_ThirdPersonCharacter>(OtherActor))
	{
		if (auto interactionComp = character->GetComponentByClass<UCACInteraction>())
		{
			if (interactionComp->IsEnabled())
			{
				
			}
			//UE_LOG(LogTemp, Warning, TEXT("Overlap end with %s"), *GetNameSafe(OtherActor));
			interactionComp->Disable(this);
		}
	}
}

void ACAInteractable::SetHideMesh(bool bHide)
{
	bHideMesh = bHide;
}
