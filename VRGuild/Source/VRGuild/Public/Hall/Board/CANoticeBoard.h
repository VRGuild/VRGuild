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

struct FProjectNotice;
class UTestWidgetComp;

UCLASS()
class VRGUILD_API ACANoticeBoard : public AActor, public ICIInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACANoticeBoard();
	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	UStaticMeshComponent* BoardMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* BoardMesh;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings|Components")
	TObjectPtr<UTestWidgetComp> WidgetCompCancelButton;

	UFUNCTION(BlueprintCallable)
	void PostAllProjectNotice(FProjectListResponse projectNoticeList);

	UFUNCTION(BlueprintCallable)
	void PostProjectNotice(FVector position, FProjectDetailInfo projectNotice);

	UFUNCTION(BlueprintCallable)
	void PostReviewNotice(FVector position, FEvaluation reviewNotice); /*Change to FReviewNotice*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Notices)
	TSubclassOf<class ACAProjectNotice> ProjectNoticeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACAReviewNotice> ReviewNoticeClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<FProjectDetailInfo> ProjectDetailInfoList;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Settings")
	EPosterType PosterType;
};
