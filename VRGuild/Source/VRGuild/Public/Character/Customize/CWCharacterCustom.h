// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CGIGameInstance.h"
#include "Global/UI/API/CWGCharacterCustomAPI.h"
#include "CWCharacterCustom.generated.h"

/**
 *
 */
UCLASS()
class VRGUILD_API UCWCharacterCustom : public UCWGCharacterCustomAPI
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	FCharacterCustomData Data;

	UFUNCTION(BlueprintCallable)
	void CustomHead(int32 index);
	
	UFUNCTION(BlueprintCallable)
	void CustomBody(int32 index);
	
	UFUNCTION(BlueprintCallable)
	void CustomLower(int32 index);

	// Custom SaveInstance
	UFUNCTION(BlueprintCallable)
	TArray<int32> CustomSave();

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
