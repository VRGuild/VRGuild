// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/API/BPL/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/UI/API/CWGProjectAPI.h"
#include "CWGProjectNoticeFull.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGProjectNoticeFull : public UCWGProjectAPI
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSetDetailInfo(FProjectWithDetail ProjectInfo);
};
