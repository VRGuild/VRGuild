// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CAReviewNotice.h"
#include "Global/API/BPL/CBPLBase.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGReviewNotice.h"
#include "GameFramework/Character.h"
#include "Global/Components/CACCarry.h"
#include "Global/API/CACCharacterAPI.h"

ACAReviewNotice::ACAReviewNotice()
{
	bReplicates = true;
}

void ACAReviewNotice::BeginPlay()
{
	Super::BeginPlay();

	auto* FrontSideWidget = CreateWidget</*UCWGReviewNotice*/UUserWidget>(GetWorld(), WidgetFrontSide);

	if (!ensureAlways(FrontSideWidget))
		return;
	/*FrontSideWidget->SetReviewInfo(NoticeData);*/

	if (this->WidgetFrontSide)
	{
		this->FrontSideComp->SetWidget(FrontSideWidget);
	}
	if (this->WidgetBackSide)
	{
		this->BackSideComp->SetWidgetClass(this->WidgetBackSide);
	}
}

void ACAReviewNotice::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin)
{
	Super::Init(bIsEnabled, owner, bAttachToOwner, actorOrigin);

	if (auto notice = Cast<ACAReviewNotice>(actorOrigin))
	{
		Init(notice->DevData);
	}
}

void ACAReviewNotice::Init(const FDeveloperRequest& newData) /*Change to FReviewNotice*/
{
	UE_LOG(LogTemp, Warning, TEXT("ReviewNotice SetNoticeData success"));

	if (newData.devInfo.devId != 0)
	{
		DevData = newData;
		UpdatePoster();
	}
}

void ACAReviewNotice::OnCompletedCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("OnCompletedCallback done in ACAReviewNotice [%s]"), GetWorld()->GetNetMode() == NM_Client ? 
	TEXT("CLIENT") : TEXT("SerVER"));

	

	Destroy();
}

UUserWidget* ACAReviewNotice::GetPosterDisplayWidget()
{
	UUserWidget* widget = Super::GetPosterDisplayWidget();

	UpdatePoster(widget);

	return widget;
}

bool ACAReviewNotice::CheckCanTrace(ACharacter* player) const
{
	if (auto carryComp = player->GetComponentByClass<UCACCarry>())
	{
		if (auto carriedNotice = Cast<ACAReviewNotice>(carryComp->GetCarriedActor()))
		{
			return DevData.devInfo.devId != carriedNotice->DevData.devInfo.devId;
		}
	}

	return true;
}

void ACAReviewNotice::ServerExecuteOnCompletedDelegate_Implementation()
{	
	Super::ServerExecuteOnCompletedDelegate_Implementation();

	if (auto owner = GetOwner())
	{
		if (auto carryComp = owner->GetComponentByClass<UCACCarry>())
		{
			carryComp->StartDrop(true);
		}
	}
}