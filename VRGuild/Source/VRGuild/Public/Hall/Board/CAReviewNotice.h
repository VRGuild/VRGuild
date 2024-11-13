// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/Actors/CABasePoster.h"
#include "CAReviewNotice.generated.h"

UCLASS()
class VRGUILD_API ACAReviewNotice : public ACABasePoster
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;
	void Init(const FDevInfo& newData); /*Change to FReviewNotice*/

	virtual void OnCompletedCallback() override;
	virtual UUserWidget* GetPosterDisplayWidget() const override;
	

protected:
	UPROPERTY(BlueprintReadWrite)
	FDevInfo DevData;

	virtual bool CheckCanTrace(ACharacter* player) const override;
	virtual void ServerExecuteOnCompletedDelegate_Implementation() override;
};