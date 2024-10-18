// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWScrollBase.generated.h"

/**
 * 
 */

class UScrollBox;
class UInputMappingContext;
class UInputAction;

UCLASS()
class VRGUILD_API UCWScrollBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn))
	TSubclassOf<UUserWidget> WidgetToDisplay;
	bool bIsHidden;
	float Offset;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float OffsetSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float WheelScrollMultiplier;

	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TObjectPtr<UInputMappingContext> ScrollingInputContext;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TObjectPtr<UInputAction> IA_Scroll;

	UFUNCTION()
	void OnScrollActive(const FInputActionValue& Action);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimForward();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimReverse();

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;
};
