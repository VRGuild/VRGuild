// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/Project/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/Actors/CABasePoster.h"
#include "CAReviewNotice.generated.h"

UCLASS()
class VRGUILD_API ACAReviewNotice : public ACABasePoster
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;
	void Init(const FProjectNotice& newData); /*Change to FReviewNotice*/

	virtual void OnCompletedCallback() override;
	virtual UUserWidget* GetPosterDisplayWidget() const override;
	

protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectNotice NoticeData; 

	virtual bool CheckCanTrace(ACharacter* player) const override;
	virtual void ServerExecuteOnCompletedDelegate_Implementation() override;
};