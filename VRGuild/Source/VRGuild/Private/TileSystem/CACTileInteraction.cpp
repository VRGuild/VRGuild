// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CACTileInteraction.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "TileSystem/CATileSpace.h"
#include "TileSystem/CATileFloor.h"
#include "TileSystem/CATileCube.h"
#include "TileSystem/FL_TileTools.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Global/API/CACEtherAPI.h"

// Sets default values for this component's properties
UCACTileInteraction::UCACTileInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCACTileInteraction::BeginPlay()
{
	Super::BeginPlay();

	if (Owner->IsA<ATP_ThirdPersonCharacter>())
	{
		ATP_ThirdPersonCharacter* character = Cast<ATP_ThirdPersonCharacter>(Owner);
		// 입력 액션 바인딩
		if (APlayerController* PlayerController = Cast<APlayerController>(character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				// Enhanced Input Component 찾기
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
				{
					EnhancedInputComponent->BindAction(TileAddAction, ETriggerEvent::Started, this, &UCACTileInteraction::OnClicked);
					EnhancedInputComponent->BindAction(TileAddAction, ETriggerEvent::Ongoing, this, &UCACTileInteraction::OnHolding);
					EnhancedInputComponent->BindAction(TileAddAction, ETriggerEvent::Canceled, this, &UCACTileInteraction::OnReleased);
				}
			}
		}
	}
	// ...
}

void UCACTileInteraction::InitializeComponent()
{
	Super::InitializeComponent();

	this->Owner = GetOwner();

	if (Owner->IsA<ATP_ThirdPersonCharacter>())
	{
		ATP_ThirdPersonCharacter* character = Cast<ATP_ThirdPersonCharacter>(Owner);
		OwnerCamera = character->GetFollowCamera();
	}
}

bool UCACTileInteraction::SetSelectedTileCube(TSubclassOf<ACATileCube> tileCube)
{
	if (!tileCube)
		return false;
	this->SelectedTileCube = tileCube;
	return true;
}

AActor* UCACTileInteraction::TileLineTrace()
{
	if (!OwnerCamera)
		return nullptr;
	FHitResult hitResult;
	FVector start = this->OwnerCamera->GetComponentLocation();
	FVector end = start  + (this->OwnerCamera->GetForwardVector() * 3000);
	FCollisionQueryParams params;
	params.AddIgnoredActor(Owner);

	bool hit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params);

#if WITH_EDITOR 
	DrawDebugLine(GetWorld(), start, end, hit ? FColor::Cyan : FColor::Red, false, 3);
#endif

	if (hit)
	{
		HitResult = hitResult;
		return HitResult.GetActor();
	}
	return nullptr;
}

void UCACTileInteraction::HoverTile()
{
	// 알파 작업
	
}

void UCACTileInteraction::OnClicked(const FInputActionValue& Value)
{
	bHold = true;
	// 누르면 발생한다
	if (DebugMode)
		UE_LOG(LogTemp, Display, TEXT("OnClicked"));
	TileLineTrace();
}

void UCACTileInteraction::OnHolding(const FInputActionValue& Value)
{
	// 누르고 있을때 발생 한다
	if (DebugMode)
		UE_LOG(LogTemp, Display, TEXT("OnHolding"));
	if (!bHold)
		return ;
	currHoldTime += GetWorld()->DeltaTimeSeconds;
	if (currHoldTime > MaxHoldTime)
	{
		bHold = false;
		currHoldTime = 0;
		DeleteTile();
	}
}


void UCACTileInteraction::OnReleased(const FInputActionValue& Value)
{
	// 짧게 누르고 띄면 발생한다
	currHoldTime = 0;
	bHold = false;
	if (DebugMode)
		UE_LOG(LogTemp, Display, TEXT("OnReleased"));
	//AddTile();
	FEther price;

	price.silverAmount = 10;
	price.cause = "fucking Genius!!";

	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());
	if (!target)
		return;
	if (target->GetSpaceType() == ESpaceType::Floor)
	{
		if (HitResult.GetComponent()->GetName() == "CeilingComp")
		{
			// 아무 작업 하지않음
		}
		else if (HitResult.GetComponent()->GetName() == "BaseFloorComp")
		{
			// 만들지 않음
			// AddTile();
		}
		else
		{
			CheckPayEther(price, "Wall Object");
		}
	}

}

void UCACTileInteraction::AddTile()
{
	UE_LOG(LogTemp, Display, TEXT("AddTile Called"));

	if (!HitResult.GetActor() || !HitResult.GetActor()->IsA<ACATileSpace>())
		return;

	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());
	if (!target)
		return;

	if (target->GetSpaceType() == ESpaceType::Floor)
	{
		if (HitResult.GetComponent()->GetName() == "BaseFloorComp")
		{
			if (this->SelectedTileCube)
			{
				target->SpawnSpace(HitResult, this->SelectedTileCube);
			}
		}
		else if (HitResult.GetComponent()->GetName() == "CeilingComp")
		{
			// 아무 작업 하지않음
		}
		else
		{
			target->AttachSpace(HitResult, target);
		}
	}
	/*
	else
	{
		target->AttachSpace(HitResult, target);
	}
	*/
}

void UCACTileInteraction::DeleteTile()
{
	UE_LOG(LogTemp, Display, TEXT("DeleteTile Called"));

	if (!HitResult.GetActor() || !HitResult.GetActor()->IsA<ACATileSpace>())
		return;

	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());

	target->Delete();
}

