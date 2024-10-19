// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CACCustomInteraction.h"
#include "Character/Customize/CWCharacterCustom.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Global/CGIGameInstance.h"

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
		if (!CustomUIFactory)
			return;
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

void UCACCustomInteraction::SaveCustomData(FCharacterCustomData data)
{
	auto GameInstance = GetWorld()->GetGameInstance<UCGIGameInstance>();
	if (GameInstance)
	{
		GameInstance->CustomData = data;

		if (Owner)
		{
			if (auto characterOwner = Cast<ACharacter>(Owner))
			{
				if(auto playerController = characterOwner->GetController<APlayerController>())
				{
					playerController->ClientTravel(TEXT("127.0.0.1:7777"), ETravelType::TRAVEL_Absolute);
				}
			}
		}
	}
}

