// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/Project/CBPLProjectOld.h"
#include "CWGReviewNotice.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGReviewNotice : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetReviewInfo(FProjectNotice notice); /*Change to FReviewNotice*/

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FProjectNotice ProjectInfo; /*Change to FReviewNotice*/
};
