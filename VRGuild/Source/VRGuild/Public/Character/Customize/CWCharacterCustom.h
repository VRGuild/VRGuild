// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWCharacterCustom.generated.h"

/**
 *
 */
UCLASS()
class VRGUILD_API UCWCharacterCustom : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Bt_HeadMesh0;

	UPROPERTY(meta = (BindWidget))
	class UButton* Bt_HeadMesh1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Bt_HeadMesh2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Bt_CustomEnd;

	UFUNCTION()
	void CustomHead0();

	UFUNCTION()
	void CustomHead1();

	UFUNCTION()
	void CustomHead2();

	UFUNCTION()
	void CustomEnd();

	// Cast 
	UPROPERTY(EditDefaultsOnly)
	class UCACCharacterHead* CharacterHeadComponent;

};
