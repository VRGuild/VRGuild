// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"
#include "Global/API/BPL/CBPLDeveloper.h"

#include "CoreMinimal.h"
#include "Global/Actors/CABasePoster.h"
#include "CAReviewNotice.generated.h"

class UCACCharacterAPI;

UCLASS()
class VRGUILD_API ACAReviewNotice : public ACABasePoster
{
	GENERATED_BODY()
public:
	ACAReviewNotice();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;
	void Init(const FDeveloperRequest& newData); /*Change to FReviewNotice*/

	virtual void OnCompletedCallback() override;
	virtual UUserWidget* GetPosterDisplayWidget() override;
	

protected:
	UPROPERTY(BlueprintReadOnly)
	FDeveloperRequest DevData;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePoster(UUserWidget* posterWidget = nullptr);

	virtual bool CheckCanTrace(ACharacter* player) const override;
	virtual void ServerExecuteOnCompletedDelegate_Implementation() override;
};