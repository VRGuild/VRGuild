// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/Actors/CABasePoster.h"
#include "CAProjectNotice.generated.h"

UCLASS()
class VRGUILD_API ACAProjectNotice : public ACABasePoster
{
	GENERATED_BODY()
public:
	ACAProjectNotice();
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;
	void Init(const FProjectDetailInfo& newData);

	virtual void OnCompletedCallback() override;
	virtual UUserWidget* GetPosterDisplayWidget() const override;

protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectDetailInfo NoticeData;

	virtual bool CheckCanTrace(ACharacter* player) const override;
};
