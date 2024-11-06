// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Widgets/TestWidgetComp.h"
#include "Global/Widgets/CWBaseWorld.h"
#include "GameFramework/Character.h"
#include "Hall/Board/CANoticeBoard.h"
#include "Components/Button.h"

UTestWidgetComp::UTestWidgetComp()
{
	bWantsInitializeComponent = true;

	FeatureType = EFeatureType::NONE;
}

void UTestWidgetComp::BeginPlay()
{
	Super::BeginPlay();

	ensure(NoticeBoard = GetOwner<ACANoticeBoard>());

	ensureMsgf(FeatureType != EFeatureType::NONE, TEXT("make sure to initialize FeatureType"));

	auto what = GetUserWidgetObject();
	if (auto widget = Cast<UCWBaseWorld>(what))
	{
		widget->Button->OnReleased.AddDynamic(this, &UTestWidgetComp::OnButtonReleased);
	}
}

void UTestWidgetComp::InitializeComponent()
{
	Super::InitializeComponent();
}

void UTestWidgetComp::OnButtonReleased()
{
	if (!NoticeBoard) return;

	switch (FeatureType)
	{
	case EFeatureType::REFRESH:
	{
		NoticeBoard->RefreshBoard(nullptr);
		break;
	}
	}
}
