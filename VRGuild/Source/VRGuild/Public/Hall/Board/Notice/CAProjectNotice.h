// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/Project/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/Actors/CABasePoster.h"
#include "CAProjectNotice.generated.h"

UCLASS()
class VRGUILD_API ACAProjectNotice : public ACABasePoster
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;

	virtual UUserWidget* GetPosterDisplayWidget() const override;
	
	void SetNoticeData(const FProjectNotice& newData);

protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectNotice NoticeData;

	virtual bool CheckCanTrace(ACharacter* player) const override;
};
