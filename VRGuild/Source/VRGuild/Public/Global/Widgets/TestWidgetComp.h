// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TestWidgetComp.generated.h"

/**
 * 
 */

class ACANoticeBoard;

enum class EFeatureType : uint8;

UCLASS()
class VRGUILD_API UTestWidgetComp : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UTestWidgetComp();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	UFUNCTION()
	void OnButtonReleased();

	UPROPERTY(EditDefaultsOnly, Category="Settings|Notice|Feature")
	EFeatureType FeatureType;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Settings|Notice")
	TObjectPtr<ACANoticeBoard> NoticeBoard;
};
