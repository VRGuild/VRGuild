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
	bUIMode = false;

	if (WidgetToDisplay)
	{
		if (auto Widget = CreateWidget(GetOwningPlayer(), WidgetToDisplay))
		{
			ScrollBox->AddChild(Widget);
			ScrollBox->SetConsumeMouseWheel(EConsumeMouseWheel::Never);
		}
	}
	EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer());
	if (EnhancedInputSubsystem)
	{
		EnhancedInputSubsystem->AddMappingContext(ScrollingInputContext, 0);
		EnhancedInputSubsystem->AddMappingContext(UIModeContext, 0);
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(IA_Scroll, ETriggerEvent::Triggered, this, &UCWScrollBase::OnScrollActive);
		EnhancedInput->BindAction(IA_UIMode, ETriggerEvent::Started, this, &UCWScrollBase::OnUIModeActive);
		EnhancedInput->BindAction(IA_UIMode, ETriggerEvent::Completed, this, &UCWScrollBase::OnUIModeActive);
	}
}

void UCWScrollBase::NativeDestruct()
{
	if (GetOwningPlayer() && EnhancedInputSubsystem)
	{		
		EnhancedInputSubsystem->RemoveMappingContext(ScrollingInputContext);
		EnhancedInputSubsystem->RemoveMappingContext(UIModeContext);
	}

	Super::NativeDestruct();
}

void UCWScrollBase::OnScrollActive(const FInputActionValue& Action)
{
	float value = Action.Get<float>();

	if (IsPlayingAnimation()) return;

	//This code moves the scroller in the same direction as the mouse scroll direction
	Offset += value * OffsetSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Offset %f"), Offset);
	UE_LOG(LogTemp, Warning, TEXT("Max: %f"), ScrollBox->GetScrollOffsetOfEnd());

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

		CheckIfUIMode();
	}
	else if (Offset > 0.f)
	{
		PlayAnimReverse();
		Offset = 0.f;
		ScrollBox->SetScrollOffset(Offset);
	}
}

void UCWScrollBase::OnUIModeActive(const FInputActionValue& Action)
{
	if (bUIMode || bIsHidden) return;

	bool value = Action.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("Keyboard down %d"), value);

	if (EnhancedInputSubsystem)
	{
		if (value)
		{
			EnhancedInputSubsystem->RemoveMappingContext(ScrollingInputContext);
		}
		else EnhancedInputSubsystem->AddMappingContext(ScrollingInputContext, 0);
	}
	
	ChangeInputModeToUI(value);
}

void UCWScrollBase::ChangeInputModeToUI(bool bEnable)
{
	if (bEnable)
	{
		GetOwningPlayer()->SetShowMouseCursor(true);
		if (EnhancedInputSubsystem)
		{
			EnhancedInputSubsystem->RemoveMappingContext(DefaultInputContext);
		}
	}
	else
	{
		GetOwningPlayer()->SetShowMouseCursor(false);
		if (EnhancedInputSubsystem)
		{
			EnhancedInputSubsystem->AddMappingContext(DefaultInputContext, 0);
		}
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	}
}

void UCWScrollBase::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	if (bIsHidden)
	{
		bIsHidden = false;
		ScrollBox->SetWheelScrollMultiplier(WheelScrollMultiplier);
	}
	else
	{
		bIsHidden = true;
	}
}

void UCWScrollBase::CheckIfUIMode()
{
	if (!bUIMode && Offset > 750.f)
	{
		bUIMode = true;
	}
	else if (bUIMode && Offset < 750.f)
	{
		bUIMode = false;
	}
	ChangeInputModeToUI(bUIMode);
}
