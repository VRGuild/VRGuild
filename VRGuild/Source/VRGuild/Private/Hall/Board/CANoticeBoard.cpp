// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CANoticeBoard.h"
#include "Global/Project/CBPLProject.h"
#include "Hall/Board/Notice/CAProjectNotice.h"
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

	ACAProjectNotice* newProjectNotice = GetWorld()->SpawnActor<ACAProjectNotice>(this->ProjectNoticeClass);

	newProjectNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	newProjectNotice->SetActorRelativeLocation(position);
	UCWGProjectNotice* FrontSideWidget = Cast<UCWGProjectNotice>(newProjectNotice->FrontSideComp->GetWidget());
	FrontSideWidget->SetProjectInfo(projectNotice);
}

