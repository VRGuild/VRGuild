// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCustomInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	UPROPERTY()
	class UUserWidget* CustomUI;

	UPROPERTY(EditDefaultsOnly)
    TSubclassOf <class UUserWidget> CustomUIFactory;

	UPROPERTY(EditDefaultsOnly)
	class ATP_ThirdPersonCharacter* character;

	UFUNCTION()
	void ShowWidget();
		
};
