// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Actors/CABasePoster.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "Hall/Board/Notice/UI/CWGProjectNoticeFull.h"
#include "Global/Components/CACCarry.h"
#include "Global/Components/CACCharacterAnimMontage.h"

// Sets default values
ACABasePoster::ACABasePoster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	/*this->RootSceneComp = CreateDefaultSubobject<USceneComponent>(FName("RootSceneComp"));
	this->SetRootComponent(this->RootSceneComp);*/

	bReplicates = true;

	this->FrontSideComp = CreateDefaultSubobject<UWidgetComponent>(FName("FrontSide"));
	this->FrontSideComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->FrontSideComp->SetDrawSize(this->WidgetDrawSize);
	this->FrontSideComp->SetRelativeScale3D(FVector(0.1));

	FrontSideComp->SetCollisionProfileName("Interactable");

	this->BackSideComp = CreateDefaultSubobject<UWidgetComponent>(FName("BackSide"));
	this->BackSideComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->BackSideComp->SetRelativeLocation(FVector(-0.1, 0, 0));
	this->BackSideComp->SetRelativeRotation(FRotator(0, 180, 0));
	this->BackSideComp->SetDrawSize(this->WidgetDrawSize);
	this->BackSideComp->SetTwoSided(true);
	this->BackSideComp->SetRelativeScale3D(FVector(0.1));

	BackSideComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetHideMesh(true);

	HeldScale = FVector(.2f);
	RelativeSocketRot = FRotator(-30.7f, -90.f, -60.f);
	RelativeSocketLoc = FVector(8.7f, 0.f, -1.6f);

	PlayerCarryingMessage = TEXT("Replace Poster");
}

void ACABasePoster::BeginInteract(ACharacter* Initiator)
{
	Super::BeginInteract(Initiator);

	if (auto montageComp = Initiator->GetComponentByClass<UCACCharacterAnimMontage>())
	{
		montageComp->StartAnimMontage(EAnimMontageType::PICKUP);
	}
}

UUserWidget* ACABasePoster::GetPosterDisplayWidget() const
{
	return CreateWidget<UUserWidget>(GetWorld(), PosterWidgetToDisplayClass);
}

bool ACABasePoster::CanTrace(ACharacter* player) const
{
	bool bcanTrace = Super::CanTrace(player);

	return bcanTrace && CheckCanTrace(player);
}

void ACABasePoster::OnRep_bEnabled()
{
	Super::OnRep_bEnabled();
	auto owner = GetOwner<ACharacter>();

	if (IsEnabled())
	{
		FrontSideComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	}
	else FrontSideComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	/*if (owner && owner->IsLocallyControlled())
	{

	}*/
}

FString ACABasePoster::GetTraceMessage(ACharacter* player) const
{
	Super::GetTraceMessage(player);

	FString message = TEXT("Hold");

	if (auto carryComp = player->GetComponentByClass<UCACCarry>())
	{
		if (carryComp->GetCarriedActor() && carryComp->GetCarryType() == ECarriedType::COMMISSION)
		{
			message = PlayerCarryingMessage;
		}
	}

	return message;
}
