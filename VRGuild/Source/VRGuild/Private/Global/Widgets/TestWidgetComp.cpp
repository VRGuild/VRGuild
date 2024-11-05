// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Widgets/TestWidgetComp.h"
#include "Global/Widgets/CWBaseWorld.h"

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
}

void UTestWidgetComp::EndInteract(ACharacter* Initiator)
{
}
