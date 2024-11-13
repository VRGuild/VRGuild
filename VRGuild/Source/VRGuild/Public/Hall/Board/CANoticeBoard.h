// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "CANoticeBoard.generated.h"

UENUM(Blueprintable)
enum class EPosterType : uint8
{
	PROJECT UMETA(DisplayName = "Project"),
	REVIEW UMETA(DisplayName = "Review"),
	NONE UMETA(DisplayName = "None")
};

UENUM()
enum class EFeatureType : uint8
{
	REFRESH UMETA(DisplayName = "Refresh"),
	NONE UMETA(DisplayName = "None")
};

struct FProjectNotice;
class UTestWidgetComp;
class ACABasePoster;

UCLASS()
class VRGUILD_API ACANoticeBoard : public AActor
{
	GENERATED_BODY()
	
	friend class UTestWidgetComp;

public:	
	// Sets default values for this actor's properties
	ACANoticeBoard();
	virtual void BeginPlay() override;
protected:
	// Called every frame
	UStaticMeshComponent* BoardMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* BoardMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Components")
	TObjectPtr<UTestWidgetComp> WidgetCompCancelButton;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> TopSize;
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> BottomSize;
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> LeftSize;
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> RightSize;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Spacer", meta=(MakeEditWidget))
	FVector StartLocation;
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Spacer", meta = (MakeEditWidget))
	FVector SpacerWidth;
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Spacer", meta = (MakeEditWidget))
	FVector SpacerHeight;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_MakeReview();

	UFUNCTION(BlueprintCallable)
	void PostAllProjectNotice(FProjectDetailPagedResponse projectNoticeList);

	UFUNCTION(BlueprintCallable)
	void PostAllReviewNotice(const FDeveloperListResponse& devReviewList);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
	TSubclassOf<class ACAProjectNotice> ProjectNoticeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class ACAReviewNotice> ReviewNoticeClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectWithDetail> ProjectInfoList;

	UPROPERTY(BlueprintReadWrite)
	TArray<FDevInfo> DevInfoList;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings")
	EPosterType PosterType;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	float SpawnedActorScale;

private:
	void RefreshBoard(ACharacter* initiator);
	
	void ResetFeatureType();

	void SpawnProjectPoster(TSubclassOf<ACAProjectNotice> projectNoticeClass, const FTransform& trans, FProjectWithDetail projectInfo);
	void SpawnNoticePoster(TSubclassOf<ACAReviewNotice> reviewNoticeClass, const FTransform& trans, FDevInfo devInfo);

	EFeatureType FeatureType;
	TArray<ACABasePoster*> Posters;
	
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess), Category = "Settings|Interactions")
	bool bDisplayRefreshButton;
};
