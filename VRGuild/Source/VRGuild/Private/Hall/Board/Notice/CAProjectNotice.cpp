// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "Hall/Board/Notice/UI/CWGProjectNoticeFull.h"
#include "Global/Components/CACCarry.h"
#include "Global/Components/CACCharacterAnimMontage.h"

void ACAProjectNotice::BeginPlay()
{
	Super::BeginPlay();

	if (this->WidgetFrontSide)
	{
		auto widget = CreateWidget<UCWGProjectNotice>(GetWorld(), this->WidgetFrontSide);
		if (widget) widget->SetProjectInfo(this->NoticeData);
		this->FrontSideComp->SetWidget(widget);
	}
	if (this->WidgetBackSide)
	{
		this->BackSideComp->SetWidgetClass(this->WidgetBackSide);
		BackSideComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACAProjectNotice::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorInteracted)
{
	Super::Init(bIsEnabled, owner, bAttachToOwner, actorInteracted);

	if (auto notice = Cast<ACAProjectNotice>(actorInteracted))
	{
		NoticeData = notice->NoticeData;
	}
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

void ACAProjectNotice::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACAProjectNotice, NoticeData);
}

void ACAProjectNotice::SetNoticeData(const FProjectNotice& newData)
{
	if(newData.ProjectNoticeId != -1)
		NoticeData = newData;
}

bool ACAProjectNotice::CheckCanTrace(ACharacter* player) const
{
	if (auto carryComp = player->GetComponentByClass<UCACCarry>())
	{
		if (auto carriedNotice = Cast<ACAProjectNotice>(carryComp->GetCarriedActor()))
		{
			return NoticeData.ProjectTitle != carriedNotice->NoticeData.ProjectTitle;
		}
	}

	return true;
}
