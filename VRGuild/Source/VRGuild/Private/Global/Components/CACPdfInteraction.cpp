// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CACPdfInteraction.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "InputActionValue.h"
#include "Global/PDF/CAPdfViewer.h"

// Sets default values for this component's properties
UCACPdfInteraction::UCACPdfInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCACPdfInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (GetOwner()->IsA<ATP_ThirdPersonCharacter>())
	{
		ATP_ThirdPersonCharacter* character = Cast<ATP_ThirdPersonCharacter>(GetOwner());
		OwnerCamera = character->GetFollowCamera();
		// 입력 액션 바인딩
		if (APlayerController* PlayerController = Cast<APlayerController>(character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				// Enhanced Input Component 찾기
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
				{
					EnhancedInputComponent->BindAction(PdfClickAction, ETriggerEvent::Started, this, &UCACPdfInteraction::OnClicked);
				}
			}
		}
	}
}


void UCACPdfInteraction::OnClicked(const FInputActionValue& Value)
{
	AActor* HitActor = TileLineTrace();

}


AActor* UCACPdfInteraction::TileLineTrace()
{
	if (!OwnerCamera)
		return nullptr;
	FHitResult hitResult;
	FVector start = this->OwnerCamera->GetComponentLocation();
	FVector end = start + (this->OwnerCamera->GetForwardVector() * 3000);
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());

	bool hit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params);

#if WITH_EDITOR 
	DrawDebugLine(GetWorld(), start, end, hit ? FColor::Cyan : FColor::Red, false, 3);
#endif

	if (hit)
	{
		HitResult = hitResult;
		if (HitResult.GetActor()->IsA<ACAPdfViewer>())
		{
			ACAPdfViewer* target = Cast< ACAPdfViewer>(HitResult.GetActor());
			UPrimitiveComponent* hitComp = HitResult.GetComponent();
			if (hitComp->GetName() == "BT_Right")
				target->NextCall();
			if (hitComp->GetName() == "BT_Left")
				target->PrevCall();
		}
		return HitResult.GetActor();
	}
	return nullptr;
}
