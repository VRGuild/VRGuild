// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CACTileInteraction.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "TileSystem/CATileSpace.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values for this component's properties
UCACTileInteraction::UCACTileInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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


// Called every frame
void UCACTileInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	CurrTime += DeltaTime;
	if (CurrTime < RerenderTime)
		return;
	CurrTime = 0;

	// ...

	if (bOnClick)
	{
		this->OnClickTime += RerenderTime;
		return;
	}

	TileLineTrace();

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

void UCACTileInteraction::TileLineTrace()
{
	if (!OwnerCamera)
		return;
	FHitResult hitResult;
	FVector start = this->OwnerCamera->GetComponentLocation();
	FVector end = start  + (this->OwnerCamera->GetForwardVector() * 3000);
	FCollisionQueryParams params;
	params.AddIgnoredActor(Owner);

	bool hit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params);

	if (hit)
	{
		HitResult = hitResult;
		HoverTile();
	}
	//DrawDebugLine(GetWorld(), start, end, hit ? FColor::Cyan : FColor::Red, false, 3);
}

void UCACTileInteraction::HoverTile()
{
	// 알파 작업
	
}

void UCACTileInteraction::OnClicked(const FInputActionValue& Value)
{
	// 누르면 발생한다
	if (DebugMode)
		UE_LOG(LogTemp, Display, TEXT("OnClicked"));
	bOnClick = true;
}

void UCACTileInteraction::OnHolding(const FInputActionValue& Value)
{
	// 누르고 있을때 발생 한다
	if (bOnClick) {
		if (DebugMode)
			UE_LOG(LogTemp, Display, TEXT("OnHolding %f"), OnClickTime);
	}
	if (OnClickTime > MaxHoldTime)
	{
		DeleteTile();
		bOnClick = false;
		this->OnClickTime = 0;
	}
}


void UCACTileInteraction::OnReleased(const FInputActionValue& Value)
{
	// 짧게 누르고 띄면 발생한다
	if (DebugMode)
		UE_LOG(LogTemp, Display, TEXT("OnReleased"));
	AddTile();
	bOnClick = false;
	this->OnClickTime = 0;
}

void UCACTileInteraction::AddTile()
{
	UE_LOG(LogTemp, Display, TEXT("AddTile Called"));
	
	if (!HitResult.GetActor() || !HitResult.GetActor()->IsA<ACATileSpace>())
		return;

	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());
	
	target->AddSpace(HitResult.Normal);
}

void UCACTileInteraction::DeleteTile()
{
	UE_LOG(LogTemp, Display, TEXT("DeleteTile Called"));

	if (!HitResult.GetActor() || !HitResult.GetActor()->IsA<ACATileSpace>())
		return;

	ACATileSpace* target = Cast<ACATileSpace>(HitResult.GetActor());

	target->DeleteSpace();
}

