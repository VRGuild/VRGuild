// Fill out your copyright notice in the Description page of Project Settings.


#include "CWCharacterCustom.h"
#include "Components/Button.h"
#include "CACCharacterHead.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UCWCharacterCustom::NativeConstruct()
{
	Super::NativeConstruct();

	ATP_ThirdPersonCharacter* PlayerCharacter = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CharacterHeadComponent = PlayerCharacter->FindComponentByClass<UCACCharacterHead>();
	}
	Bt_HeadMesh0->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead0);
	Bt_HeadMesh1->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead1);
	Bt_HeadMesh2->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomHead2);
	Bt_CustomEnd->OnClicked.AddDynamic(this, &UCWCharacterCustom::CustomEnd);
}

void UCWCharacterCustom::CustomHead0()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchHead(0);
	}
}

void UCWCharacterCustom::CustomHead1()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchHead(1);
	}
}

void UCWCharacterCustom::CustomHead2()
{
	if (nullptr != CharacterHeadComponent)
	{
		CharacterHeadComponent->SwitchHead(2);
	}
}

void UCWCharacterCustom::CustomEnd()
{
	this->RemoveFromParent();
}
