// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACAProjectNotice::ACAProjectNotice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->RootSceneComp = CreateDefaultSubobject<USceneComponent>(FName("RootSceneComp"));
	this->SetRootComponent(this->RootSceneComp);

	SetReplicates(true);

	this->FrontSideComp = CreateDefaultSubobject<UWidgetComponent>(FName("FrontSide"));
	this->FrontSideComp->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	this->FrontSideComp->SetDrawSize(this->WidgetDrawSize);
	this->FrontSideComp->SetRelativeScale3D(FVector(0.2));
	ConstructorHelpers::FClassFinder<UUserWidget> tempFrontSide(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hall/Board/Notice/UI/WBP_ProjectNoticeFrontSide.WBP_ProjectNoticeFrontSide_C'"));

	if (tempFrontSide.Succeeded())
	{
		this->FrontSideComp->SetWidgetClass(tempFrontSide.Class);
	}

	this->BackSideComp = CreateDefaultSubobject<UWidgetComponent>(FName("BackSide"));
	this->BackSideComp->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	this->BackSideComp->SetRelativeLocation(FVector(-0.1,0,0));
	this->BackSideComp->SetRelativeRotation(FRotator(0, 180,0));
	this->BackSideComp->SetDrawSize(this->WidgetDrawSize);
	this->BackSideComp->SetTwoSided(true);
	this->BackSideComp->SetRelativeScale3D(FVector(0.2));
	ConstructorHelpers::FClassFinder<UUserWidget> tempBackSide(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hall/Board/Notice/UI/WBP_ProjectNoticeBackSide.WBP_ProjectNoticeBackSide_C'"));
	if (tempBackSide.Succeeded())
	{
		this->BackSideComp->SetWidgetClass(tempBackSide.Class);
	}
}

// Called when the game starts or when spawned
void ACAProjectNotice::BeginPlay()
{
	Super::BeginPlay();
	
	if (this->WidgetFrontSide)
	{
		this->FrontSideComp->SetWidgetClass(this->WidgetFrontSide);
		UCWGProjectNotice* tempFrontSideComp = Cast<UCWGProjectNotice>(FrontSideComp->GetWidget());
		if (tempFrontSideComp)
			tempFrontSideComp->SetProjectInfo(this->NoticeData);
	}
	if (this->WidgetBackSide)
	{
		this->BackSideComp->SetWidgetClass(this->WidgetBackSide);
	}
}

void ACAProjectNotice::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACAProjectNotice, NoticeData);
}
