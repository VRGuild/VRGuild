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
class UEnhancedInputLocalPlayerSubsystem;

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
	
	float Offset;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float OffsetSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float WheelScrollMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TObjectPtr<UInputMappingContext> DefaultInputContext;
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TObjectPtr<UInputMappingContext> ScrollingInputContext;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TObjectPtr<UInputMappingContext> UIModeContext;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TObjectPtr<UInputAction> IA_Scroll;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TObjectPtr<UInputAction> IA_UIMode;

	UFUNCTION()
	void OnScrollActive(const FInputActionValue& Action);
	UFUNCTION()
	void OnUIModeActive(const FInputActionValue& Action);
	void ChangeInputModeToUI(bool bEnable);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimForward();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimReverse();

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;

private:
	void CheckIfUIMode();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;

	bool bIsHidden;
	bool bUIMode;
};
