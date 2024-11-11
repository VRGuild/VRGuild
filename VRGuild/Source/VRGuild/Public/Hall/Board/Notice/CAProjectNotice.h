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
	void Init(const FProjectWithSupport& newData);
	void InitDetail(const FProjectWithDetail& newData);

	virtual void OnCompletedCallback() override;
	virtual UUserWidget* GetPosterDisplayWidget() const override;
	
	UPROPERTY()
	TSubclassOf<class UCWGProjectNotice> s;
protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectWithSupport NoticeData;
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectWithDetail NoticeDetailData;

	virtual bool CheckCanTrace(ACharacter* player) const override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetInfoPost(FProjectWithSupport data);
	UFUNCTION(BlueprintImplementableEvent)
	void OnSetInfoDetailPost(FProjectWithDetail data);
};
