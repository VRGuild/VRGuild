// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWGProjectNotice.generated.h"

struct FProjectNotice;
/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGProjectNotice : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetProjectInfo(FProjectNotice projectNotice);

};
