// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/Project/CBPLProjectOld.h"
#include "CWGProjectNotice.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGProjectNotice : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetProjectInfo(FProjectDetailInfo projectInfo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FProjectDetailInfo ProjectInfo;
};
