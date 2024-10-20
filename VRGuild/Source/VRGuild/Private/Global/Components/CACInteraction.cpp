// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CACInteraction.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "Hall/Actors/CAReceptionist.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"),
	false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

// Sets default values for this component's properties
UCACInteraction::UCACInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(false);

	InteractDistance = 600.f;
	InteractRadius = 60.f;
	ActorOnFocus = nullptr;
	bCanInteract = true;
}


// Called when the game starts
void UCACInteraction::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner<ACharacter>();
	//Only Clients can Interact
	if (Owner && Owner->HasAuthority() || !Owner->IsLocallyControlled())
		Owner = nullptr;
}

// Called every frame
void UCACInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	if (Owner && Owner->IsLocallyControlled())
	{
		//AActor* ActorOnFocus = nullptr;
		UpdateTrace();

		if(!bCanInteract) return;

		if (ActorOnFocus)
		{
			if (ActorOnFocus->Implements<UCIInteractionInterface>())
			{
				if (!InteractingActor)
				{
					InteractingActor = ActorOnFocus;
					BeginTrace();
				}
				else if (InteractingActor != ActorOnFocus)
				{
					EndTrace();

					InteractingActor = ActorOnFocus;
					BeginTrace();
				}
				else BeginTrace();
			}
		}
		else if (InteractingActor) {
			EndTrace();
			InteractingActor = nullptr;
		}
	}
}

void UCACInteraction::Enable()
{
	//If Interactable actor is already in map, remove actor from map
	//else add interactable actor to map

	if (Owner && Owner->IsLocallyControlled())
	{
		bEnabled = true;
		SetComponentTickEnabled(true);
		ActorOnFocus = nullptr;
	}
}

void UCACInteraction::Disable()
{
	if (Owner && Owner->IsLocallyControlled())
	{
		bEnabled = false;
		SetComponentTickEnabled(false);
		EndTrace();
		ActorOnFocus = nullptr;
	}
}

void UCACInteraction::BeginInteract()
{
	if (InteractingActor && bCanInteract)
	{
		GetInterface()->BeginInteract(Owner);
		EndTrace();
		bCanInteract = false;
		
		/*if (bEnabled)
			SetComponentTickEnabled(false);*/
	}
	else UE_LOG(LogTemp, Warning, TEXT("No begininteract"));
}

void UCACInteraction::EndInteract()
{
	if (InteractingActor && !bCanInteract)
	{
		GetInterface()->EndInteract(Owner);
		bCanInteract = true;

		if (!bEnabled)
		{
			InteractingActor = nullptr;
			//SetComponentTickEnabled(true);
		}
		//else InteractingActor = nullptr;
	}
	else UE_LOG(LogTemp, Warning, TEXT("No Endinteract"));
}

void UCACInteraction::UpdateTrace()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FVector Start = Owner->GetPawnViewLocation();
	FVector End = Start + GetOwner()->GetActorForwardVector() * InteractDistance;

	FVector WorldLoc;
	FVector WorldDir;

	auto PC = Owner->GetController<APlayerController>();
	if (PC)
	{
		int32 ViewportSizeX;
		int32 ViewportSizeY;
		PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
		FVector2D ScreenLoc = FVector2D(ViewportSizeX / 2, ViewportSizeY / 2);
		if (PC->DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, WorldLoc, WorldDir))
		{
			Start = WorldLoc;
			End = Start + WorldDir * InteractDistance;
		}
	}

	TArray<FHitResult> Hits;
	FCollisionObjectQueryParams ObjectQueryparams;
	//ObjectQueryparams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryparams.AddObjectTypesToQuery(ECC_GameTraceChannel1);
	FCollisionQueryParams QueryParams;
	FCollisionShape Shape;
	Shape.SetSphere(InteractRadius);

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 0.f);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Black, FString::Printf(TEXT("Actor* %s"), *GetNameSafe(InteractingActor)));
	}

	QueryParams.AddIgnoredActor(Owner);
	if (GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryparams, Shape, QueryParams))
	{
		float LargestDotValue = -100.f;
		for (int i = Hits.Num() - 1; i >= 0; --i)
		{
			if (bDebugDraw)
			{
				DrawDebugSphere(GetWorld(), Hits[i].ImpactPoint, InteractRadius, 32, FColor::Blue, false, 0.0f);
			}

			FVector ImpactVector = Hits[i].ImpactPoint;
			FVector DistVector = ImpactVector - WorldLoc;

			DistVector.Normalize();
			FVector WorldDirTemp = WorldDir;

			DistVector.Z = 0.f;
			WorldDirTemp.Z = 0.f;

			float DotResult = FVector::DotProduct(DistVector, WorldDirTemp);
			if (DotResult > LargestDotValue)
			{
				ActorOnFocus = Hits[i].GetActor();
				LargestDotValue = DotResult;
			}
		}
	}
}

const AActor* UCACInteraction::GetActorOnFocus() const
{
	return ActorOnFocus;
}

void UCACInteraction::BeginTrace()
{
	if (!bIsTracing && InteractingActor)
	{
		GetInterface()->BeginTrace(Owner);
		bIsTracing = true;
	}
}

void UCACInteraction::EndTrace()
{
	if (bIsTracing && InteractingActor)
	{
		GetInterface()->EndTrace(Owner);
		bIsTracing = false;
	}
}

ICIInteractionInterface* UCACInteraction::GetInterface() const
{
	return Cast<ICIInteractionInterface>(InteractingActor);
}

bool UCACInteraction::CanInteract() const
{
	return bCanInteract;
}