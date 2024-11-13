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
#include "Global/API/BPL/CBPLDeveloper.h"

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

	StartLocation = FVector::Zero();
	SpacerWidth += FVector(0.f, 15.f, 0.f);
	SpacerHeight += FVector(0.f, 0.f, 15.f);

	FeatureType = EFeatureType::NONE;
	bDisplayRefreshButton = false;

	SpawnedActorScale = .5f;
	MaxPosterNumbers = -1;
}

void ACANoticeBoard::BeginPlay()
{
	Super::BeginPlay();

	if (!bDisplayRefreshButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Notice board buttons disabled and not visible"), *GetNameSafe(this));
		WidgetCompCancelButton->SetHiddenInGame(true, true);
	}
}

void ACANoticeBoard::PostAllProjectNotice(FProjectDetailPagedResponse projectNoticeList)
{
	this->ProjectInfoList.Empty();
	this->ProjectInfoList.Append(projectNoticeList.data);
	Posters.Empty();

	auto defaultObj = ProjectNoticeClass->GetDefaultObject<ACABasePoster>();
	check(defaultObj);

	float horiLength = SpawnedActorScale * defaultObj->GetRightLength();
	float vertiLength = SpawnedActorScale * defaultObj->GetTopLength();

	float boardWidth = (TopSize->GetComponentLocation() - BottomSize->GetComponentLocation()).Length();
	float boardHeight = (LeftSize->GetComponentLocation() - RightSize->GetComponentLocation()).Length();

	float spacerWidth = (StartLocation - SpacerWidth).Length();
	float spacerHeight = (StartLocation - SpacerHeight).Length();

	TArray<FVector> nice;

	FVector startLoc = GetActorLocation() + StartLocation;

	int horizontalCount = 0;
	FVector leftSize = LeftSize->GetComponentLocation();
	leftSize.Z = GetActorLocation().Z + StartLocation.Z;
	FVector widthDir = (leftSize - startLoc);
	float maxWidth = widthDir.Length();
	widthDir.Normalize();

	float test = FMath::Abs((horiLength + spacerWidth) * horizontalCount);
	float testHuh = FMath::Abs(maxWidth);
	while (test < testHuh)
	{
		horizontalCount++;
		test = FMath::Abs((horiLength + spacerWidth) * horizontalCount);
	}

	int verticalCount = 1;
	FVector bottomSize = BottomSize->GetComponentLocation();
	bottomSize.Y = GetActorLocation().Y + StartLocation.Y;
	FVector heightDir = (bottomSize - startLoc);
	float maxHeight = heightDir.Length();
	heightDir.Normalize();

	float test1 = FMath::Abs((vertiLength + spacerHeight) * verticalCount);
	float testHuh1 = FMath::Abs(maxHeight);
	while (test1 < testHuh1)
	{
		verticalCount++;
		test1 = FMath::Abs((vertiLength + spacerHeight) * verticalCount);
	}

	UE_LOG(LogTemp, Warning, TEXT("horizontalCount: %d, verticalCount: %d"), horizontalCount, verticalCount);

	for (int i = 0; i < verticalCount; ++i)
	{
		for (int j = 0; j < horizontalCount; ++j)
		{
			int32 index = horizontalCount * i + j;

			if (!ProjectInfoList.IsValidIndex(index)) return; // can't post anymore posters 

			FTransform trans;
			FVector widthVector = widthDir * FMath::Abs(horiLength + spacerWidth) * j;
			FVector heigthVector = heightDir * FMath::Abs(vertiLength + spacerHeight) * i;

			trans.SetLocation(startLoc + heigthVector + widthVector);
			trans.SetScale3D(FVector(SpawnedActorScale));
			trans.SetRotation(GetActorRotation().Quaternion());

			SpawnProjectPoster(ProjectNoticeClass, trans, ProjectInfoList[index]);
		}
	}
}

void ACANoticeBoard::PostAllReviewNotice(const FDeveloperListResponse& devReviewList)
{
	this->DevInfoList.Empty();
	this->DevInfoList.Append(devReviewList.data);
	Posters.Empty();

	auto defaultObj = ReviewNoticeClass->GetDefaultObject<ACABasePoster>();
	check(defaultObj);

	float horiLength = SpawnedActorScale * defaultObj->GetRightLength();
	float vertiLength = SpawnedActorScale * defaultObj->GetTopLength();

	float boardWidth = (TopSize->GetRelativeLocation() - BottomSize->GetRelativeLocation()).Length();
	float boardHeight = (LeftSize->GetRelativeLocation() - RightSize->GetRelativeLocation()).Length();

	float spacerWidth = (StartLocation - SpacerWidth).Length();
	float spacerHeight = (StartLocation - SpacerHeight).Length();

	TArray<FVector> nice;

	FVector tempLoc = RightSize->GetRelativeLocation();
	RightSize->SetRelativeLocation(StartLocation);
	FVector startLoc = RightSize->GetComponentLocation();
	RightSize->SetRelativeLocation(tempLoc);

	int horizontalCount = 0;
	FVector leftSize = LeftSize->GetComponentLocation();
	leftSize.Z = startLoc.Z;
	FVector widthDir = (leftSize - startLoc);
	float maxWidth = widthDir.Length();
	widthDir.Normalize();

	float test = FMath::Abs((horiLength + spacerWidth) * horizontalCount);
	float testHuh = FMath::Abs(maxWidth);
	while (test < testHuh)
	{
		horizontalCount++;
		test = FMath::Abs((horiLength + spacerWidth) * horizontalCount);
	}

	int verticalCount = 1;
	FVector bottomSize = BottomSize->GetComponentLocation();
	bottomSize.X = startLoc.X;
	FVector heightDir = (bottomSize - startLoc);
	float maxHeight = heightDir.Length();
	heightDir.Normalize();

	float test1 = FMath::Abs((vertiLength + spacerHeight) * verticalCount);
	float testHuh1 = FMath::Abs(maxHeight);
	while (test1 < testHuh1)
	{
		verticalCount++;
		test1 = FMath::Abs((vertiLength + spacerHeight) * verticalCount);
	}

	UE_LOG(LogTemp, Warning, TEXT("horizontalCount: %d, verticalCount: %d"), horizontalCount, verticalCount);

	for (int i = 0; i < verticalCount; ++i)
	{
		for (int j = 0; j < horizontalCount; ++j)
		{
			int32 index = horizontalCount * i + j;

			if (!DevInfoList.IsValidIndex(index)) return; // can't post anymore posters 
			
			FTransform trans;
			FVector widthVector = widthDir * FMath::Abs(horiLength + spacerWidth) * j;
			FVector heigthVector = heightDir * FMath::Abs(vertiLength + spacerHeight) * i;

			trans.SetLocation(startLoc + heigthVector + widthVector);
			trans.SetScale3D(FVector(SpawnedActorScale));
			trans.SetRotation(GetActorRotation().Quaternion());

			SpawnNoticePoster(ReviewNoticeClass, trans, DevInfoList[index]);

			if (MaxPosterNumbers == index + 1) return;
		}
	}
}

void ACANoticeBoard::SpawnProjectPoster(TSubclassOf<ACAProjectNotice> projectNoticeClass, const FTransform& trans, FProjectWithDetail projectInfo)
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto spawned = GetWorld()->SpawnActorDeferred<ACAProjectNotice>(projectNoticeClass, trans, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	spawned->Init(projectInfo);
	spawned->FinishSpawning(trans);

	Posters.Add(spawned);
}

void ACANoticeBoard::SpawnNoticePoster(TSubclassOf<ACAReviewNotice> reviewNoticeClass, const FTransform& trans, FDevInfo devInfo)
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto spawned = GetWorld()->SpawnActorDeferred<ACAReviewNotice>(reviewNoticeClass, trans, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	spawned->Init(devInfo);
	spawned->FinishSpawning(trans);

	Posters.Add(spawned);
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

		BP_MakeReview();
		break;
	}
	}
}

void ACANoticeBoard::ResetFeatureType()
{
	FeatureType = EFeatureType::NONE;
}
