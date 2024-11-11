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

protected:
	UFUNCTION(BlueprintCallable)
	void PostAllProjectNotice(FProjectPagedResponse projectNoticeList);

	UFUNCTION(BlueprintCallable)
	void PostProjectNotice(FVector position, FProjectWithSupport projectNotice);

	UFUNCTION(BlueprintCallable)
	void PostAllProjectDetailNotice(FProjectDetailPagedResponse projectNoticeList);

	UFUNCTION(BlueprintCallable)
	void PostProjectDetailNotice(FVector position, FProjectWithDetail projectNotice);

	UFUNCTION(BlueprintCallable)
	void PostReviewNotice(FVector position, FEvaluation reviewNotice); /*Change to FReviewNotice*/

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
	TSubclassOf<class ACAProjectNotice> ProjectNoticeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<class ACAReviewNotice> ReviewNoticeClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectWithSupport> ProjectInfoList;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectWithDetail> ProjectDetailInfoList;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings")
	EPosterType PosterType;

private:
	void RefreshBoard(ACharacter* initiator);
	
	void ResetFeatureType();

	EFeatureType FeatureType;
	TArray<ACABasePoster*> Posters;
	
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess), Category = "Settings|Interactions")
	bool bDisplayRefreshButton;
};
