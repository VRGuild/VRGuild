// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"
#include "Global/API/BPL/CBPLDeveloper.h"

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

USTRUCT()
struct FDataP
{
	GENERATED_BODY()
public:
	float boardWidth;
	float boardHeight;

	float posterWidth;
	float posterHeight;

	FVector startLoc;

	FVector widthDir;
	FVector heightDir; 
	
	float spacerWidth;
	float spacerHeight;

	float maxWidth;
	float maxHeight;

	int horizontalCount = 0;
	int verticalCount = 1;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Components")
	TObjectPtr<UTestWidgetComp> WidgetCompCancelButton;

	UPROPERTY(EditAnywhere, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> TopSize;
	UPROPERTY(EditAnywhere, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> BottomSize;
	UPROPERTY(EditAnywhere, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> LeftSize;
	UPROPERTY(EditAnywhere, Category = "Settings|Components|Size")
	TObjectPtr<USceneComponent> RightSize;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Spacer", meta=(MakeEditWidget))
	FVector StartLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Settings|Spacer", meta = (MakeEditWidget))
	FVector SpacerWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Settings|Spacer", meta = (MakeEditWidget))
	FVector SpacerHeight;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void StartTrace();
	UFUNCTION(BlueprintImplementableEvent)	
	void EndTrace();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_MakeReview();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_MakeProjects();

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
	TArray<FDeveloperRequest> DevInfoList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	EPosterType PosterType;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float SpawnedActorScale;

	void RefreshBoard(ACharacter* initiator);
	
	UFUNCTION(Server, Reliable)
	void ServerRefreshBoard(ACharacter* initiator);
	
	virtual void OnRep_Owner() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), Category = "Settings|Interactions")
	int32 MaxPosterNumbers;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), Category = "Settings|Interactions")
	bool bDisplayRefreshButton;
	UPROPERTY(EditAnywhere, Category = "Settings|Random")
	float LocRange;
	UPROPERTY(EditAnywhere, Category = "Settings|Random")
	float RollRange;
	UPROPERTY(EditAnywhere, Category = "Settings|Random")
	float ScaleRange;

	void GetData(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass);
	void GetCounts(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass);
	void GetPosterDimensions(FDataP& data, const TSubclassOf<ACABasePoster>& posterClass);
	void GetDirections(FDataP& data, const FVector& startLoc);
	void GetStartLocation(FDataP& data);
	void GetMaxHeightAndWidth(FDataP& data, const FVector& startLoc);

	void SpawnProjectPoster(TSubclassOf<ACAProjectNotice> projectNoticeClass, const FTransform& trans, FProjectWithDetail projectInfo);
	void SpawnNoticePoster(TSubclassOf<ACAReviewNotice> reviewNoticeClass, const FTransform& trans, FDeveloperRequest devInfo);
	
	void ResetFeatureType();

	EFeatureType FeatureType;
	TArray<ACABasePoster*> Posters;
	bool bUpdating = false;
};
