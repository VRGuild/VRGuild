// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Global/CGIGameInstance.h"

#include "CACCustomInteraction.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCustomInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACCustomInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	class AActor* Owner;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* CustomUI;

	UPROPERTY(EditDefaultsOnly)
    TSubclassOf <class UUserWidget> CustomUIFactory;

	UPROPERTY(BlueprintReadOnly)
	class ATP_ThirdPersonCharacter* character;

	UFUNCTION()
	void ShowWidget();
	
	UFUNCTION(BlueprintCallable)
	void SaveCustomData(FCharacterCustomData data);

	FCharacterCustomData CustomData;
};
