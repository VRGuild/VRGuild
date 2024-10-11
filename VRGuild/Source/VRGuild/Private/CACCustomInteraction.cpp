// Fill out your copyright notice in the Description page of Project Settings.


#include "CACCustomInteraction.h"
#include "CWCharacterCustom.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values for this component's properties
UCACCustomInteraction::UCACCustomInteraction()
{
	bWantsInitializeComponent = true;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

}


// Called when the game starts
void UCACCustomInteraction::BeginPlay()
{
	Super::BeginPlay();

	ShowWidget();
	// ...
}

void UCACCustomInteraction::InitializeComponent()
{
	Super::InitializeComponent();

	this->Owner = GetOwner();
	if (Owner->IsA<ATP_ThirdPersonCharacter>())
	{
		character = Cast<ATP_ThirdPersonCharacter>(Owner);
	}
}

void UCACCustomInteraction::ShowWidget()
{
	if (character->IsLocallyControlled())
	{
		CustomUI = CreateWidget<UCWCharacterCustom>(GetWorld(), CustomUIFactory);
		if (CustomUI)
		{
			CustomUI->AddToViewport();
			auto pc = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (pc)
			{
				pc->SetShowMouseCursor(true);
			}
		}
	}
}

