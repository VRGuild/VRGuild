// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CANoticeBoard.h"
#include "Global/Project/CBPLProject.h"
#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Hall/Board/CAReviewNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"

// Sets default values
ACANoticeBoard::ACANoticeBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoardMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("BoardMesh"));
	if (this->BoardMesh)
	{
		this->BoardMeshComp->SetStaticMesh(BoardMesh);
	}
	SetRootComponent(this->BoardMeshComp);
}

// Called when the game starts or when spawned
void ACANoticeBoard::BeginPlay()
{
	Super::BeginPlay();
	FProjectNotice test = FProjectNotice();
}

void ACANoticeBoard::PostProjectNotice(FVector position, FProjectNotice projectNotice)
{
	ACAProjectNotice* newProjectNotice = GetWorld()->SpawnActorDeferred<ACAProjectNotice>(this->ProjectNoticeClass, FTransform::Identity);
	if (ensure(newProjectNotice))
	{
		newProjectNotice->Init(projectNotice);

		newProjectNotice->FinishSpawning(FTransform::Identity);

		newProjectNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		newProjectNotice->SetActorRelativeLocation(position);
	}	
}

void ACANoticeBoard::PostReviewNotice(FVector position, FProjectNotice reviewNotice) /*Change to FReviewNotice*/ 
{
	ACAReviewNotice* newReviewNotice = GetWorld()->SpawnActorDeferred<ACAReviewNotice>(this->ReviewNoticeClass, FTransform::Identity);
	if (ensure(newReviewNotice))
	{
		newReviewNotice->Init(reviewNotice);
		newReviewNotice->FinishSpawning(FTransform::Identity);
		
		newReviewNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		newReviewNotice->SetActorRelativeLocation(position);	
	}
}

