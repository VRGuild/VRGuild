// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CANoticeBoard.h"
#include "Global/Project/CBPLProjectOld.h"
#include "Hall/Board/Notice/CAProjectNotice.h"
#include "Hall/Board/CAReviewNotice.h"
#include "Components/WidgetComponent.h"
#include "Hall/Board/Notice/UI/CWGProjectNotice.h"
#include "Global/Widgets/TestWidgetComp.h"
#include "Global/Actors/CABasePoster.h"
#include "../../../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

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

	bReplicates = true;

	WidgetCompCancelButton = CreateDefaultSubobject<UTestWidgetComp>("WidgetCompCancelButton");
	WidgetCompCancelButton->SetupAttachment(RootComponent);
	WidgetCompCancelButton->SetCollisionProfileName("Interactable");

	TopSize = CreateDefaultSubobject<USceneComponent>("TopSize");
	TopSize->SetupAttachment(RootComponent);
	TopSize->SetRelativeLocation(FVector(0.f, 0.f, 20.f));

	BottomSize = CreateDefaultSubobject<USceneComponent>("BottomSize");
	BottomSize->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
	BottomSize->SetupAttachment(RootComponent);

	RightSize = CreateDefaultSubobject<USceneComponent>("RightSize");
	RightSize->SetRelativeLocation(FVector(0.f, 20.f, 0.f));
	RightSize->SetupAttachment(RootComponent);

	LeftSize = CreateDefaultSubobject<USceneComponent>("LeftSize");
	LeftSize->SetRelativeLocation(FVector(0.f, -20.f, 0.f));
	LeftSize->SetupAttachment(RootComponent);

	SpacerWidth += FVector(0.f, 15.f, 0.f);
	SpacerHeight += FVector(0.f, 0.f, 15.f);

	FeatureType = EFeatureType::NONE;
	bDisplayRefreshButton = false;

	SpawnedActorScale = .5f;
}

void ACANoticeBoard::BeginPlay()
{
	Super::BeginPlay();

	if (!bDisplayRefreshButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Notice board buttons disabled and not visible"), *GetNameSafe(this));
		WidgetCompCancelButton->SetHiddenInGame(true, true);
		//WidgetCompCancelButton->Trace
	}
}

void ACANoticeBoard::PostAllProjectNotice(FProjectListResponse projectNoticeList)
{
	this->ProjectDetailInfoList.Empty();
	this->ProjectDetailInfoList.Append(projectNoticeList.data);
	/*for (int32 i = 0; i < projectNoticeList.data.Num() ;  i++ )
	{
		PostProjectNotice(FVector(0, -120 * i, 0), projectNoticeList.data[i]); 
	}*/

	for (int32 i = 0; i < 5 ;  i++ )
	{
		PostProjectNotice(FVector(0, -120 * i, 0), FProjectDetailInfo());
	}
}

void ACANoticeBoard::PostProjectNotice(FVector position, FProjectDetailInfo projectNotice)
{
	ACAProjectNotice* newProjectNotice = GetWorld()->SpawnActorDeferred<ACAProjectNotice>(this->ProjectNoticeClass, FTransform::Identity);
	if (ensure(newProjectNotice))
	{
		ScaleSpawnedActor(newProjectNotice);
		
		newProjectNotice->Init(projectNotice);

		newProjectNotice->FinishSpawning(FTransform::Identity);

		newProjectNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		newProjectNotice->SetActorRelativeLocation(position);

		Posters.Add(newProjectNotice);
	}	
}

void ACANoticeBoard::PostReviewNotice(FVector position, FEvaluation reviewNotice) /*Change to FReviewNotice*/
{
	ACAReviewNotice* newReviewNotice = GetWorld()->SpawnActorDeferred<ACAReviewNotice>(this->ReviewNoticeClass, FTransform::Identity);
	if (ensure(newReviewNotice))
	{
		ScaleSpawnedActor(newReviewNotice);

		newReviewNotice->Init(reviewNotice);
		newReviewNotice->FinishSpawning(FTransform::Identity);
		
		newReviewNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		newReviewNotice->SetActorRelativeLocation(position);	
		
		Posters.Add(newReviewNotice);
	}
}

void ACANoticeBoard::RefreshBoard(ACharacter* initiator)
{
	FeatureType = EFeatureType::REFRESH;

	switch (PosterType)
	{
	case EPosterType::REVIEW:
	{
		for (auto poster : Posters)
		{
			UE_LOG(LogTemp, Warning, TEXT("What %s"), *GetNameSafe(poster));
			poster->Destroy();
		}
		break;
	}
	}
}

void ACANoticeBoard::ResetFeatureType()
{
	FeatureType = EFeatureType::NONE;
}

void ACANoticeBoard::ScaleSpawnedActor(AActor* actorSpawned)
{
	if (!actorSpawned) return;
	actorSpawned->SetActorScale3D(FVector(SpawnedActorScale));
}
