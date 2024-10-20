// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Widgets/CWDisplayMessage.h"
#include "Components/TextBlock.h"

void UCWDisplayMessage::Init(FString msg)
{
	TextBlock_Message->SetText(FText::FromString(msg));
}
