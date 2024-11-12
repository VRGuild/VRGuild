// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Global/API/BPL/CBPLDeveloper.h"


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void SetReviewInfo(FDeveloperRequest notice); /*Change to FReviewNotice*/

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FDeveloperRequest ProjectInfo; /*Change to FReviewNotice*/
};
