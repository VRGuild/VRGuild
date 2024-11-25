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
	PrimaryComponentTick.bStartWithTickEnabled = true;
	SetIsReplicatedByDefault(false);

	bEnabled = false;

	InteractDistance = 600.f;
	InteractRadius = 60.f;

	bFullEnable = true;
}


// Called when the game starts
void UCACInteraction::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner<ACharacter>();
	if (Owner && !Owner->IsLocallyControlled())
	{
		Owner = nullptr;
	}
}

// Called every frame
void UCACInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();
	ICIInteractionInterface* InterfaceTraced = nullptr;

	if (IsEnabled() && CanTrace())
	{
		if (Owner && Owner->IsLocallyControlled())
		{
			UpdateTrace(InterfaceTraced);

			if (InterfaceTraced)
			{
				if (!InterfaceOnFocus)
				{
					InterfaceOnFocus = Cast<ICIInteractionInterface>(InterfaceTraced);
					BeginTrace();
				}
				else if (InterfaceOnFocus != InterfaceTraced)
				{
					EndTrace();

					InterfaceOnFocus = InterfaceTraced;
					BeginTrace();
				}
				else
				{
					BeginTrace();
				}
			}
			else if (InterfaceOnFocus) {
				EndTrace();
				InterfaceOnFocus = nullptr;
			}
		}
	}

	if (bDebugDraw)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Magenta, FString::Printf(TEXT("ActorTraced: %s"), *GetNameSafe(actorTraced)));
	}
}

void UCACInteraction::UpdateActorsOverlapped(AActor* actorOverlapped, bool bAdd)
{
	if (bAdd)
	{
		ActorsOverlapped.Add(actorOverlapped);
	}
	else
	{
		ActorsOverlapped.Remove(actorOverlapped);
	}
	//UE_LOG(LogTemp, Warning, TEXT("ActorsOverlapped: %d"), ActorsOverlapped.Num());
}

void UCACInteraction::Enable()
{
	if (bEnabled) return;

	UE_LOG(LogTemp, Warning, TEXT("Interaction Enabled: Actor after begin: %d"), ActorsOverlapped.Num());
	UE_LOG(LogTemp, Warning, TEXT("================================"));

	if (Owner && Owner->IsLocallyControlled())
	{
		bEnabled = true;
	}
}

void UCACInteraction::Disable()
{
	if (!bEnabled) return;

	UE_LOG(LogTemp, Warning, TEXT("Interaction Disabled: Actor after disable: %d"), ActorsOverlapped.Num());
	UE_LOG(LogTemp, Warning, TEXT("================================"));

	if (Owner && Owner->IsLocallyControlled())
	{
		bEnabled = false;
		EndTrace();
		InterfaceOnFocus = nullptr;
	}
}

void UCACInteraction::Interact()
{
	if (!InterfaceOnFocus) return;

	if (!bEnabled) return;

	if (ActorsOverlapped.Num() == 0) return;

	if (auto inter = InterfaceOnFocus)
	{
		if (InterfaceOnFocus && !InterfaceOnFocus->CanInteract(Owner))
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant Interact"));
			return;
		}

		BeginInteract();
	}
}

void UCACInteraction::BeginInteract()
{
	if (InterfaceOnFocus /*&& !InteractingActor && CanInteract(InterfaceOnFocus)*/)
	{
		if (!InterfaceOnFocus->CanInteract(Owner)) return;

		InterfaceOnFocus->BeginInteract(Owner);

		//EndTrace();
	}
	else UE_LOG(LogTemp, Warning, TEXT("No Begininteract"));
}

void UCACInteraction::EndInteract()
{
	if (InterfaceOnFocus /*&& !InteractingActor && CanInteract(InterfaceOnFocus)*/)
	{
		if (InterfaceOnFocus->CanInteract(Owner)) return;

		InterfaceOnFocus->EndInteract(Owner);

		//EndTrace();
	}
	else UE_LOG(LogTemp, Warning, TEXT("No Endinteract"));
}

void UCACInteraction::BeginTrace()
{
	if (!bIsTracing && InterfaceOnFocus)
	{
		UE_LOG(LogTemp, Warning, TEXT("2 - 11111"));
		InterfaceOnFocus->BeginTrace(Owner);
		bIsTracing = true;
	}
}

void UCACInteraction::EndTrace()
{
	if (bIsTracing && InterfaceOnFocus)
	{
		InterfaceOnFocus->EndTrace(Owner);
		bIsTracing = false;
	}
}

void UCACInteraction::UpdateTrace(ICIInteractionInterface*& interfaceTraced)
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
			if (auto tempInterface = Cast<ICIInteractionInterface>(Hits[i].GetActor()))
			{
				if (auto componentInterface = Cast<ICIInteractionInterface>(Hits[i].GetComponent()))
				{
					tempInterface = componentInterface;
				}

				if (!tempInterface->CanTrace(Owner)) continue;
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
				interfaceTraced = Cast<ICIInteractionInterface>(Hits[i].GetActor());
				if (auto temp = Cast<ICIInteractionInterface>(Hits[i].GetComponent()))
				{
					interfaceTraced = temp;
				}
				LargestDotValue = DotResult;
			}
		}
	}
}

bool UCACInteraction::IsEnabled() const
{
	return bEnabled;
}

bool UCACInteraction::CanTrace() const
{
	return ActorsOverlapped.Num() >= 1;
}

//ICIInteractionInterface* UCACInteraction::GetInterface(AActor* actor) const
//{
//	return Cast<ICIInteractionInterface>(actor);
//}