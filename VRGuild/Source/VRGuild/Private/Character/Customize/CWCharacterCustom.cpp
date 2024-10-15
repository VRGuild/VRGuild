// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CWCharacterCustom.h"
#include "Components/Button.h"
#include "Character/Customize/CACCharacterHead.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Customize/CACCharacterPartBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Character/Customize/CACCharacterBody.h"
#include "Character/Customize/CACCharacterLower.h"


void UCWCharacterCustom::NativeConstruct()
{
	Super::NativeConstruct();

	ATP_ThirdPersonCharacter* PlayerCharacter = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CharacterHeadComponent = PlayerCharacter->FindComponentByClass<UCACCharacterHead>();
		CharacterBodyComponent = PlayerCharacter->FindComponentByClass<UCACCharacterBody>();
		CharacterLowerComponent = PlayerCharacter->FindComponentByClass<UCACCharacterLower>();
	}
	Bt_HeadMesh0->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead0);
	Bt_HeadMesh1->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead1);
	Bt_HeadMesh2->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead2);
	Bt_BodyMesh1->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomBody1);
	Bt_BodyMesh2->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomBody2);
	Bt_LowerMesh1->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomLower1);
	Bt_LowerMesh2->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomLower2);
	Bt_CustomEnd->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomEnd);
}

void UCWCharacterCustom::CustomHead0()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchSKM(0);
	}
}

void UCWCharacterCustom::CustomHead1()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchSKM(1);
	}
}

void UCWCharacterCustom::CustomHead2()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchSKM(2);
	}
}

void UCWCharacterCustom::CustomBody1()
{
	if (nullptr != CharacterBodyComponent)
	{
		CharacterBodyComponent->SwitchSKM(1);
	}
}

void UCWCharacterCustom::CustomBody2()
{
	if (nullptr != CharacterBodyComponent)
	{
		CharacterBodyComponent->SwitchSKM(2);
	}
}

void UCWCharacterCustom::CustomLower1()
{
	if (nullptr != CharacterLowerComponent)
	{
		CharacterLowerComponent->SwitchSKM(1);
	}
}

void UCWCharacterCustom::CustomLower2()
{
	if (nullptr != CharacterLowerComponent)
	{
		CharacterLowerComponent->SwitchSKM(2);
	}
}

void UCWCharacterCustom::CustomEnd()
{
	this->RemoveFromParent();
}
