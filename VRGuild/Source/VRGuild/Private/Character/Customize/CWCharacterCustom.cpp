// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CWCharacterCustom.h"
#include "Components/Button.h"
#include "Character/Customize/CACCharacterHead.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Customize/CACCharacterPartBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Character/Customize/CACCharacterBody.h"
#include "Character/Customize/CACCharacterLower.h"
#include "Character/Customize/CACCustomInteraction.h"


void UCWCharacterCustom::NativeConstruct()
{
	Super::NativeConstruct();

	ATP_ThirdPersonCharacter* PlayerCharacter = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CharacterHeadComponent = PlayerCharacter->FindComponentByClass<UCACCharacterHead>();
		CharacterBodyComponent = PlayerCharacter->FindComponentByClass<UCACCharacterBody>();
		CharacterLowerComponent = PlayerCharacter->FindComponentByClass<UCACCharacterLower>();
		CharacterCustomComponent = PlayerCharacter->FindComponentByClass<UCACCustomInteraction>();
		OnPlayerComponentLoaded();
	}
}

void UCWCharacterCustom::CustomHead(int32 index)
{
	if (nullptr != CharacterHeadComponent)
		CharacterHeadComponent->SwitchSKM(index);
}

void UCWCharacterCustom::CustomBody(int32 index)
{
	if (nullptr != CharacterBodyComponent)
	{
		CharacterBodyComponent->SwitchSKM(index);
	}
}

void UCWCharacterCustom::CustomLower(int32 index)
{
	if (nullptr != CharacterLowerComponent)
	{
		CharacterLowerComponent->SwitchSKM(1);
	}
}

void UCWCharacterCustom::CustomEnd()
{
	if (nullptr != CharacterCustomComponent)
	{
		FCharacterCustomData Data; 
		Data.Selections.Add(CharacterHeadComponent->ValueSelected);
		Data.Selections.Add(CharacterBodyComponent->ValueSelected);
		Data.Selections.Add(CharacterLowerComponent->ValueSelected);
		CharacterCustomComponent->SaveCustomData(Data);
		this->RemoveFromParent();
	}	
}
