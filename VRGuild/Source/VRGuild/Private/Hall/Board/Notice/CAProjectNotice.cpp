// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "Hall/Board/Notice/UI/CWGProjectNoticeFull.h"
#include "Global/Components/CACCarry.h"
#include "Global/Components/CACCharacterAnimMontage.h"

ACAProjectNotice::ACAProjectNotice()
{
	ConstructorHelpers::FClassFinder<UUserWidget> tempBackSide(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hall/Board/Notice/UI/WBP_ProjectNoticeBackSide.WBP_ProjectNoticeBackSide_C'"));
	if (tempBackSide.Succeeded())
	{
		this->BackSideComp->SetWidgetClass(tempBackSide.Class);
	}
}

void ACAProjectNotice::BeginPlay()
{
	Super::BeginPlay();

	auto* FrontSideWidget = CreateWidget<UCWGProjectNotice>(GetWorld(), WidgetFrontSide);

	if (ensure(FrontSideWidget))
		FrontSideWidget->SetProjectInfo(NoticeData);

	if (this->WidgetFrontSide)
	{
		this->FrontSideComp->SetWidget(FrontSideWidget);
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

void ACAProjectNotice::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorInteracted)
{
	Super::Init(bIsEnabled, owner, bAttachToOwner, actorInteracted);

	if (auto notice = Cast<ACAProjectNotice>(actorInteracted))
	{
		Init(notice->NoticeData);
	}
}

void ACAProjectNotice::Init(const FProjectDetailInfo& newData)
{
	UE_LOG(LogTemp, Warning, TEXT("ProjectNotice SetNoticeData success"));

	if (newData.projectId != -1)
		NoticeData = newData;
}

void ACAProjectNotice::OnCompletedCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("OnCompletedCallback done in ACAProjectNotice"));
}

UUserWidget* ACAProjectNotice::GetPosterDisplayWidget() const
{
	auto widget = Super::GetPosterDisplayWidget();
	auto ProjectAPIWidget = Cast<UCWGProjectNoticeFull>(widget);
	if (ensure(ProjectAPIWidget))
	{
		ProjectAPIWidget->OnSetDetailInfo(this->NoticeData);
		return ProjectAPIWidget;
	}
	return nullptr;
}

bool ACAProjectNotice::CheckCanTrace(ACharacter* player) const
{
	if (auto carryComp = player->GetComponentByClass<UCACCarry>())
	{
		if (auto carriedNotice = Cast<ACAProjectNotice>(carryComp->GetCarriedActor()))
		{
			return NoticeData.projectId != carriedNotice->NoticeData.projectId;
		}
	}

	return true;
}

