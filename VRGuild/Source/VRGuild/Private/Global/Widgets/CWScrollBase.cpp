// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Widgets/CWScrollBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/ScrollBox.h"

void UCWScrollBase::NativeConstruct()
{
	Super::NativeConstruct();

	OffsetSpeed = 100.f;
	WheelScrollMultiplier = 5.f;
	bIsHidden = false;

	if (WidgetToDisplay)
	{
		if (auto Widget = CreateWidget(GetOwningPlayer(), WidgetToDisplay))
		{
			ScrollBox->AddChild(Widget);
			ScrollBox->SetConsumeMouseWheel(EConsumeMouseWheel::Never);
		}
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ScrollingInputContext, 0);
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(IA_Scroll, ETriggerEvent::Triggered, this, &UCWScrollBase::OnScrollActive);
	}
}

void UCWScrollBase::NativeDestruct()
{
	if (GetOwningPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(ScrollingInputContext);
		}
	}

	Super::NativeDestruct();
}

void UCWScrollBase::OnScrollActive(const FInputActionValue& Action)
{
	float value = Action.Get<float>();

	if (IsPlayingAnimation())
	{
		UE_LOG(LogTemp, Warning, TEXT("Playing Anim"));
		return;
	}

	//This code moves the scroller in the same direction as the mouse scroll direction
	Offset += value * OffsetSpeed;
	if (bIsHidden && Offset < 0.f)
	{
		Offset = 0.f;
	}
	else if (Offset > ScrollBox->GetScrollOffsetOfEnd())
	{
		Offset = ScrollBox->GetScrollOffsetOfEnd();
	}
	else ScrollBox->SetScrollOffset(Offset);

	if (!bIsHidden)
	{
		if (Offset < 0.f)
		{
			PlayAnimForward();
			Offset = 0.f;
			ScrollBox->SetWheelScrollMultiplier(0.f);
		}		
	}
	else if (Offset > 0.f)
	{
		PlayAnimReverse();
		Offset = 0.f;
		ScrollBox->SetScrollOffset(Offset);
	}
}

void UCWScrollBase::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);
	UE_LOG(LogTemp, Warning, TEXT("Offset %f"), Offset);

	if (bIsHidden)
	{
		bIsHidden = false;
		ScrollBox->SetWheelScrollMultiplier(WheelScrollMultiplier);
	}
	else bIsHidden = true;
}
