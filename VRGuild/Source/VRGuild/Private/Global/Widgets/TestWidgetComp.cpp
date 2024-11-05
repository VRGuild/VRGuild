// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Widgets/TestWidgetComp.h"
#include "Global/Widgets/CWBaseWorld.h"
#include "GameFramework/Character.h"
#include "Hall/Board/CANoticeBoard.h"

UTestWidgetComp::UTestWidgetComp()
{
	bWantsInitializeComponent = true;
}

void UTestWidgetComp::InitializeComponent()
{
	Super::InitializeComponent();

	NoticeBoard = GetOwner<ACANoticeBoard>();
}

bool UTestWidgetComp::CanTrace(ACharacter* Initiator) const
{
	return true;
}

bool UTestWidgetComp::CanInteract(ACharacter* Initiator) const
{
	return true;
}

void UTestWidgetComp::BeginTrace(ACharacter* Initiator)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside BeginTrace Stuff YEAH Actor %s"),
		*GetNameSafe(Initiator));
	auto widget = GetWidget();
	auto button = Cast<UCWBaseWorld>(widget);
	if (button)
	{
		button->PlayHoverAnim();
	}
}

void UTestWidgetComp::EndTrace(ACharacter* Initiator)
{
}

void UTestWidgetComp::BeginInteract(ACharacter* Initiator)
{
	if (NoticeBoard)
	{
		NoticeBoard->RefreshBoard(Initiator);
	}
}

void UTestWidgetComp::EndInteract(ACharacter* Initiator)
{
}
