// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CACStickRayBoard.h"
#include "Hall/Board/CAMemoBoard.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values for this component's properties
UCACStickRayBoard::UCACStickRayBoard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCACStickRayBoard::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController =GetWorld()->GetFirstPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Enhanced Input Component 찾기
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(BoardClickAction, ETriggerEvent::Started, this, &UCACStickRayBoard::OnClicked);
			}
		}
	}
	// ...
	
}

void UCACStickRayBoard::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UCACStickRayBoard::RayBoard(AActor* Memo)
{
//	if (!Memo)
//		return false;

	// 카메라 위치 가져오기
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (!CameraManager)
		return false;

	// 카메라 위치와 방향 가져오기
	FVector start = CameraManager->GetCameraLocation();
	FVector cameraForward = CameraManager->GetActorForwardVector() * 1000.0f;
	FVector end = start + cameraForward * RayLength;

	FHitResult hitResult;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(GetOwner());

	// 디버그 라인 그리기 (개발 중에 레이 확인용)
	#if WITH_EDITOR 
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, 0, 1.0f);
	#endif

    if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, queryParams))
    {
        ACAMemoBoard* hitMemoBoard = Cast<ACAMemoBoard>(hitResult.GetActor());
        if (hitMemoBoard)
        {
            // 여기서 메모보드에 대한 처리
			hitMemoBoard->StickBoard(Memo, hitResult.ImpactPoint - hitMemoBoard->GetActorLocation());
            return true;
        }
    }
	return false;
}

void UCACStickRayBoard::OnClicked(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Is Clicked"));
	AActor* currentMemo = nullptr;
	RayBoard(currentMemo);
}

