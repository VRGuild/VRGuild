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

	UFUNCTION(BlueprintCallable)
	void CustomHead(int32 index);
	
	UFUNCTION(BlueprintCallable)
	void CustomBody(int32 index);
	
	UFUNCTION(BlueprintCallable)
	void CustomLower(int32 index);

	// Custom End 
	UFUNCTION(BlueprintCallable)
	void CustomEnd();

	// Cast 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) // , meta=(ExposeOnSpawn)
	class UCACCharacterHead* CharacterHeadComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCACCharacterBody* CharacterBodyComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCACCharacterLower* CharacterLowerComponent;

	class UCACCustomInteraction* CharacterCustomComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerComponentLoaded();
};
