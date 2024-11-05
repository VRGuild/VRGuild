// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CANoticeBoard.generated.h"

UENUM(Blueprintable)
enum class EPosterType : uint8
{
	PROJECT UMETA(DisplayName = "Project"),
	REVIEW UMETA(DisplayName = "Review"),
	NONE UMETA(DisplayName = "None")
};

struct FProjectNotice;

UCLASS()
class VRGUILD_API ACANoticeBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACANoticeBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UStaticMeshComponent* BoardMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* BoardMesh;

protected:
	UFUNCTION(BlueprintCallable)
	void PostProjectNotice(FVector position, FProjectNotice projectNotice);

	UFUNCTION(BlueprintCallable)
	void PostReviewNotice(FVector position, FProjectNotice reviewNotice); /*Change to FReviewNotice*/ 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Notices)
	TSubclassOf<class ACAProjectNotice> ProjectNoticeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACAReviewNotice> ReviewNoticeClass;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Settings")
	EPosterType PosterType;
};
