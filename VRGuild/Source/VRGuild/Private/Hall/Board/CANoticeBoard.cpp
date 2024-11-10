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
#include "Global/Actors/CABasePoster.h"

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

	/*if(HasAuthority() && PosterType == EPosterType::PROJECT)
		PostAllProjectNotice(FProjectListResponse());*/
}

void ACANoticeBoard::PostAllProjectNotice(FProjectListResponse projectNoticeList)
{
	this->ProjectDetailInfoList.Empty();
	this->ProjectDetailInfoList.Append(projectNoticeList.data);
	/*for (int32 i = 0; i < projectNoticeList.data.Num() ;  i++ )
	{
		PostProjectNotice(FVector(0, -120 * i, 0), projectNoticeList.data[i]);
	}*/

	auto defaultObj = ProjectNoticeClass->GetDefaultObject<ACABasePoster>();

	float horiLength = SpawnedActorScale * defaultObj->GetRightLength();
	float vertiLength = SpawnedActorScale * defaultObj->GetTopLength();

	float boardWidth = (TopSize->GetComponentLocation() - BottomSize->GetComponentLocation()).Length();
	float boardHeight = (LeftSize->GetComponentLocation() - RightSize->GetComponentLocation()).Length();

	float spacerWidth = (StartLocation - SpacerWidth).Length();
	float spacerHeight = (StartLocation - SpacerHeight).Length();

	TArray<FVector> nice;

	FVector startLoc = GetActorLocation() + StartLocation;

	int horiCount = 0;
	FVector leftSize = LeftSize->GetComponentLocation();
	leftSize.Z = GetActorLocation().Z + StartLocation.Z;
	FVector widthDir = (leftSize - startLoc);
	float maxWidth = widthDir.Length();
	widthDir.Normalize();
	
	DrawDebugLine(GetWorld(), startLoc, startLoc + widthDir * 200.f, FColor::Blue, true, 10.f, 0, 2.f);

	float test = FMath::Abs((horiLength + spacerWidth) * horiCount);
	float testHuh = FMath::Abs(maxWidth);
	while (test < testHuh)
	{
		horiCount++;
		test = FMath::Abs((horiLength + spacerWidth) * horiCount);
	}

	int vertiCount = 1;
	FVector bottomSize = BottomSize->GetComponentLocation();
	bottomSize.Y = GetActorLocation().Y + StartLocation.Y;
	FVector heightDir = (bottomSize - startLoc);
	float maxHeight = heightDir.Length();
	heightDir.Normalize();

	DrawDebugLine(GetWorld(), startLoc, startLoc + heightDir * 200.f, FColor::Red, true, 10.f, 0, 2.f);

	float test1 = FMath::Abs((vertiLength + spacerHeight) * vertiCount);
	float testHuh1 = FMath::Abs(maxHeight);
	while (test1 < testHuh1)
	{
		vertiCount++;
		test1 = FMath::Abs((vertiLength + spacerHeight) * vertiCount);
	}

	UE_LOG(LogTemp, Warning, TEXT("HoriCount: %d, VertiCount: %d"), horiCount, vertiCount);

	for (int i = 0; i < vertiCount; ++i)
	{
		for (int j = 0; j < horiCount; ++j)
		{
			FTransform trans;
			FVector widthVector = widthDir * FMath::Abs(horiLength + spacerWidth) * j;
			FVector heigthVector = heightDir * FMath::Abs(vertiLength + spacerHeight) * i;

			trans.SetLocation(startLoc + heigthVector + widthVector);
			trans.SetScale3D(FVector(SpawnedActorScale));
			trans.SetRotation(GetActorRotation().Quaternion());

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			auto spawned = GetWorld()->SpawnActor(ProjectNoticeClass, &trans, param);
		}
	}


	//Store location
	//nice.Add(FVector(StartLocation.X, (boardWidth + spacerWidth + boardWidth) * horiCount + StartLocation.Y, StartLocation.Z));
	//nice.Add(FVector(StartLocation.X, StartLocation.Y, (boardHeight + spacerHeight + boardHeight) * vertiCount + StartLocation.Z));

	/*for (int32 i = 0; i < 30; i++)
	{
		PostProjectNotice(GetPostLocation(i), FProjectDetailInfo());
	}*/
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

		newReviewNotice->SetActorLocation(position);

		/*newReviewNotice->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		newReviewNotice->SetActorRelativeLocation(position);*/

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

FVector ACANoticeBoard::GetPostLocation(int32 index)
{
	//if (!actorToSpawn) return FVector();
	return FVector();

	//StartLocation *= index * StartLocation.RightVector *
}
