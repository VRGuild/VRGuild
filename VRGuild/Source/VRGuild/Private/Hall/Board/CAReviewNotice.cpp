// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CAReviewNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGReviewNotice.h"

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

void ACAReviewNotice::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ACAReviewNotice::Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin)
{
	Super::Init(bIsEnabled, owner, bAttachToOwner, actorOrigin);

	if (auto notice = Cast<ACAReviewNotice>(actorOrigin))
	{
		Init(notice->NoticeData);
	}
}

void ACAReviewNotice::Init(const FProjectNotice& newData) /*Change to FReviewNotice*/
{
	UE_LOG(LogTemp, Warning, TEXT("ReviewNotice SetNoticeData success"));

	if (newData.ProjectNoticeId != -1)
		NoticeData = newData;
}

UUserWidget* ACAReviewNotice::GetPosterDisplayWidget() const
{
	return Super::GetPosterDisplayWidget();
}

bool ACAReviewNotice::CheckCanTrace(ACharacter* player) const
{
	return true;
}
