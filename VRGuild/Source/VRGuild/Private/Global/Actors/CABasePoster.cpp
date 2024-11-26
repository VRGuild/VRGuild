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
	
	bCanCarry = true;

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

	TopSize = CreateDefaultSubobject<USceneComponent>("TopSize");
	TopSize->SetupAttachment(RootComp);
	TopSize->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	
	BottomSize = CreateDefaultSubobject<USceneComponent>("BottomSize");
	BottomSize->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
	BottomSize->SetupAttachment(RootComp);
	
	RightSize = CreateDefaultSubobject<USceneComponent>("RightSize");
	RightSize->SetRelativeLocation(FVector(0.f, 20.f, 0.f));
	RightSize->SetupAttachment(RootComp);
	
	LeftSize = CreateDefaultSubobject<USceneComponent>("LeftSize");
	LeftSize->SetRelativeLocation(FVector(0.f, -20.f, 0.f));
	LeftSize->SetupAttachment(RootComp);

	SetHideMesh(true);

	HeldScale = FVector(.2f);
	RelativeSocketRot = FRotator(-30.7f, -90.f, -60.f);
	RelativeSocketLoc = FVector(8.7f, 0.f, -1.6f);

	PlayerCarryingMessage = TEXT("Replace Poster");
}

void ACABasePoster::BeginInteract(ACharacter* Initiator)
{
	if (bCanCarry)
	{
		Super::BeginInteract(Initiator);

		if (auto montageComp = Initiator->GetComponentByClass<UCACCharacterAnimMontage>())
		{
			montageComp->StartAnimMontage(EAnimMontageType::PICKUP);
		}
	}
	else
	{

	}
}

void ACABasePoster::EndInteract(ACharacter* Initiator)
{
	if (bCanCarry)
	{
		Super::EndInteract(Initiator);
	}	
	else
	{

	}
}

UUserWidget* ACABasePoster::GetPosterDisplayWidget()
{
	return CreateWidget<UUserWidget>(GetWorld(), PosterWidgetToDisplayClass);
}

bool ACABasePoster::CanTrace(ACharacter* player) const
{
	bool bcanTrace = Super::CanTrace(player);

	return bcanTrace && CheckCanTrace(player);
}

void ACABasePoster::BindOnCompletedDelegate(ACABasePoster* posterToBind)
{
	OnCompleted.BindUObject(posterToBind, &ACABasePoster::OnCompletedCallback);
}

void ACABasePoster::ExecuteOnCompletedDelegate()
{
	ServerExecuteOnCompletedDelegate();
}

float ACABasePoster::GetWidth() const
{
	return (LeftSize->GetRelativeLocation() - RightSize->GetRelativeLocation()).Length();
}

float ACABasePoster::GetHeight() const
{
	return (BottomSize->GetRelativeLocation() - TopSize->GetRelativeLocation()).Length();
}

void ACABasePoster::OnCompletedCallback()
{
	//
}

void ACABasePoster::ServerExecuteOnCompletedDelegate_Implementation()
{	
	OnCompleted.ExecuteIfBound();	
}

void ACABasePoster::Destroyed()
{
	OnCompleted.Unbind();
	Super::Destroyed();
}

void ACABasePoster::OnRep_bEnabled()
{
	Super::OnRep_bEnabled();
	auto owner = GetOwner<ACharacter>();

	if (IsEnabled())
	{
		FrontSideComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);	
	}
	else
	{
		FrontSideComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		FrontSideComp->SetTwoSided(true);
	}

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
