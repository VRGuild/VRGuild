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
	bCanInteract = true;
}


// Called when the game starts
void UCACInteraction::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner<ACharacter>();
	
	if (Owner && !Owner->IsLocallyControlled())
		Owner = nullptr;
}

// Called every frame
void UCACInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	AActor* actorTraced = nullptr;

	if (Owner && Owner->IsLocallyControlled())
	{
		UpdateTrace(actorTraced);
		
		if (actorTraced)
		{
			if (actorTraced->Implements<UCIInteractionInterface>())
			{
				if (!ActorOnFocus)
				{
					ActorOnFocus = actorTraced;
					BeginTrace();
				}
				else if (ActorOnFocus != actorTraced)
				{
					EndTrace();

					ActorOnFocus = actorTraced;
					BeginTrace();
				}
				else
				{
					BeginTrace();
				}
			}
		}
		else if (ActorOnFocus) {
			EndTrace();
			ActorOnFocus = nullptr;
		}
	}

	if (bDebugDraw)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("InteractingActor: %s"), *GetNameSafe(InteractingActor)));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Magenta, FString::Printf(TEXT("ActorTraced: %s"), *GetNameSafe(actorTraced)));
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
	}
}

void UCACInteraction::Disable()
{
	if (Owner && Owner->IsLocallyControlled())
	{
		bEnabled = false;
		SetComponentTickEnabled(false);
		EndTrace();
	}
}

void UCACInteraction::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("ActorOnFocus %s, InteractingActor %s, bCanInteract %d"),
		*GetNameSafe(ActorOnFocus), *GetNameSafe(InteractingActor), bCanInteract
		);
	if (ActorOnFocus && !InteractingActor && bCanInteract)
	{
		InteractingActor = ActorOnFocus;
		GetInterface(InteractingActor)->BeginInteract(Owner);
		bCanInteract = false;

		EndTrace();
	}
	else UE_LOG(LogTemp, Warning, TEXT("No begininteract"));
}

void UCACInteraction::EndInteract()
{
	if (InteractingActor && !bCanInteract)
	{
		GetInterface(InteractingActor)->EndInteract(Owner);
		InteractingActor = nullptr;
		bCanInteract = true;

		EndTrace();
	}
	else UE_LOG(LogTemp, Warning, TEXT("No Endinteract"));
}

void UCACInteraction::BeginTrace()
{
	if (!bIsTracing && ActorOnFocus)
	{
		GetInterface(ActorOnFocus)->BeginTrace(Owner);
		bIsTracing = true;
	}
}

void UCACInteraction::EndTrace()
{
	if (bIsTracing && ActorOnFocus)
	{
		GetInterface(ActorOnFocus)->EndTrace(Owner);
		bIsTracing = false;
	}
}

void UCACInteraction::UpdateTrace(AActor*& actorTraced)
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
	}

	QueryParams.AddIgnoredActor(Owner);
	if (GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryparams, Shape, QueryParams))
	{
		float LargestDotValue = -100.f;
		for (int i = Hits.Num() - 1; i >= 0; --i)
		{
			if (auto temp = Cast<ICIInteractionInterface>(Hits[i].GetActor()))
			{
				if (!temp->IsActive()) continue;
				
				if(!CanInteract(Hits[i].GetActor())) continue;
			}
			else continue;


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
				actorTraced = Hits[i].GetActor();
				LargestDotValue = DotResult;
			}
		}
	}
}

ICIInteractionInterface* UCACInteraction::GetInterface(AActor* actor) const
{
	return Cast<ICIInteractionInterface>(actor);
}

bool UCACInteraction::CanInteract(AActor* actor) const
{
	if (InteractingActor == actor)
		return false;
	return true;
}