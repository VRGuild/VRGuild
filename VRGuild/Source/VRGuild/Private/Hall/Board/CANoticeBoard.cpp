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

#include <random>

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

	RollRange = 3.f;
	ScaleRange = 0.05f;
	LocRange = 7.f;
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

	FDataP data;
	GetData(data, ProjectNoticeClass);
	UE_LOG(LogTemp, Warning, TEXT("horizontalCount: %d, verticalCount: %d"), data.horizontalCount, data.verticalCount);

	for (int i = 0; i < data.verticalCount; ++i)
	{
		for (int j = 0; j < data.horizontalCount; ++j)
		{
			int32 index = data.horizontalCount * i + j;

			if (!ProjectInfoList.IsValidIndex(index)) return; // can't post anymore posters 

			std::random_device rd{};
			std::mt19937 rng(rd());

			std::normal_distribution<float> distScale(0.f, ScaleRange);
			float randScale = distScale(rng);

			std::normal_distribution<float> distRoll(0.f, RollRange);
			float randRoll = distRoll(rng);

			std::normal_distribution<float> distLoc(0.f, LocRange);
			float randY = distLoc(rng);
			float randZ = distLoc(rng);

			FVector randLoc = FVector(0.f, randY, randZ);

			FTransform trans;
			FVector widthVector = data.widthDir * FMath::Abs(data.posterWidth + data.spacerWidth) * j;
			FVector heigthVector = data.heightDir * FMath::Abs(data.posterHeight + data.spacerHeight) * i;

			trans.SetLocation(data.startLoc + heigthVector + widthVector + randLoc);
			trans.SetScale3D(FVector(SpawnedActorScale) + randScale);
			FRotator rot = GetActorRotation() + FRotator(0.f, 0.f, randRoll);
			trans.SetRotation(rot.Quaternion());

			SpawnProjectPoster(ProjectNoticeClass, trans, ProjectInfoList[index]);

			if (MaxPosterNumbers == index + 1) return;
		}
	}
}

void ACANoticeBoard::PostAllReviewNotice(const FDeveloperListResponse& devReviewList)
{
	this->DevInfoList.Empty();
	this->DevInfoList.Append(devReviewList.data);
	Posters.Empty();

	FDataP data;
	GetData(data, ReviewNoticeClass);
	UE_LOG(LogTemp, Warning, TEXT("horizontalCount: %d, verticalCount: %d"), data.horizontalCount, data.verticalCount);

	for (int i = 0; i < data.verticalCount; ++i)
	{
		for (int j = 0; j < data.horizontalCount; ++j)
		{
			int32 index = data.horizontalCount * i + j;

			if (!DevInfoList.IsValidIndex(index)) return; // can't post anymore posters 

			std::random_device rd{};
			std::mt19937 rng(rd());

			std::normal_distribution<float> distScale(0.f, ScaleRange);
			float randScale = distScale(rng);

			std::normal_distribution<float> distRoll(0.f, RollRange);
			float randRoll = distRoll(rng);

			std::normal_distribution<float> distLoc(0.f, LocRange);
			float randY = distLoc(rng);
			float randZ = distLoc(rng);

			FVector randLoc = FVector(0.f, randY, randZ);

			FTransform trans;
			FVector widthVector = data.widthDir * FMath::Abs(data.posterWidth + data.spacerWidth) * j;
			FVector heigthVector = data.heightDir * FMath::Abs(data.posterHeight + data.spacerHeight) * i;

			trans.SetLocation(data.startLoc + heigthVector + widthVector + randLoc);
			trans.SetScale3D(FVector(SpawnedActorScale) + randScale);
			FRotator rot = GetActorRotation() + FRotator(0.f, 0.f, randRoll);
			trans.SetRotation(rot.Quaternion());

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

void ACANoticeBoard::SpawnNoticePoster(TSubclassOf<ACAReviewNotice> reviewNoticeClass, const FTransform& trans, FDeveloperRequest devInfo)
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
	case EPosterType::PROJECT:
	{
		if (GetOwner() == nullptr)
			ATP_ThirdPersonCharacter::SetOwnerFor(this, initiator);
		else ServerRefreshBoard(initiator);
	}
	}
}

void ACANoticeBoard::OnRep_Owner()
{
	Super::OnRep_Owner();

	if (PosterType == EPosterType::PROJECT)
	{
		ServerRefreshBoard(GetOwner<ACharacter>());
	}
}

void ACANoticeBoard::ServerRefreshBoard_Implementation(ACharacter* initiator)
{
	for (auto poster : Posters)
	{
		if (poster) poster->Destroy();
	}
	Posters.Empty();

	BP_MakeProjects();
}

void ACANoticeBoard::GetData(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass)
{
	auto defaultObj = posterClass->GetDefaultObject<ACABasePoster>();
	check(defaultObj);

	data.boardWidth = (TopSize->GetRelativeLocation() - BottomSize->GetRelativeLocation()).Length();
	data.boardHeight = (LeftSize->GetRelativeLocation() - RightSize->GetRelativeLocation()).Length();

	data.spacerWidth = (StartLocation - SpacerWidth).Length();
	data.spacerHeight = (StartLocation - SpacerHeight).Length();

	GetStartLocation(data);

	GetPosterDimensions(data, posterClass);

	GetDirections(data, data.startLoc);

	GetMaxHeightAndWidth(data, data.startLoc);

	GetCounts(data, ReviewNoticeClass);
}

void ACANoticeBoard::GetCounts(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass)
{
	float test = FMath::Abs((data.posterWidth + data.spacerWidth) * data.horizontalCount);
	float testHuh = FMath::Abs(data.maxWidth);
	while (test < testHuh)
	{
		data.horizontalCount++;
		test = FMath::Abs((data.posterWidth + data.spacerWidth) * data.horizontalCount);
	}

	float test1 = FMath::Abs((data.posterHeight+ data.spacerHeight) * data.verticalCount);
	float testHuh1 = FMath::Abs(data.maxHeight);
	while (test1 < testHuh1)
	{
		data.verticalCount++;
		test1 = FMath::Abs((data.posterHeight + data.spacerHeight) * data.verticalCount);
	}
}

void ACANoticeBoard::GetPosterDimensions(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass)
{
	auto defaultObj = posterClass->GetDefaultObject<ACABasePoster>();
	check(defaultObj);

	data.posterWidth = SpawnedActorScale * defaultObj->GetWidth();
	data.posterHeight = SpawnedActorScale * defaultObj->GetHeight();
}

void ACANoticeBoard::GetStartLocation(FDataP& data)
{
	FVector tempLoc = RightSize->GetRelativeLocation();
	RightSize->SetRelativeLocation(StartLocation);
	data.startLoc = RightSize->GetComponentLocation();
	RightSize->SetRelativeLocation(tempLoc);
}

void ACANoticeBoard::GetMaxHeightAndWidth(FDataP& data, const FVector& startLoc)
{
	FVector leftSize = LeftSize->GetComponentLocation();
	leftSize.Z = startLoc.Z;
	FVector widthDir = (leftSize - startLoc);
	data.maxWidth = widthDir.Length();

	FVector bottomSize = BottomSize->GetComponentLocation();
	bottomSize.X = startLoc.X;
	FVector heightDir = (bottomSize - startLoc);
	data.maxHeight = heightDir.Length();
}

void ACANoticeBoard::GetDirections(FDataP& data, const FVector& startLoc)
{
	FVector leftSize = LeftSize->GetComponentLocation();
	leftSize.Z = startLoc.Z;
	data.widthDir = (leftSize - startLoc);
	data.widthDir.Normalize();

	int verticalCount = 1;
	FVector bottomSize = BottomSize->GetComponentLocation();
	bottomSize.X = startLoc.X;
	data.heightDir = (bottomSize - startLoc);
	data.heightDir.Normalize();
}

void ACANoticeBoard::ResetFeatureType()
{
	FeatureType = EFeatureType::NONE;
}
