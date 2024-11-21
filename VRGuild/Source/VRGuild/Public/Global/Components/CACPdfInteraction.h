// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "CACPdfInteraction.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACPdfInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACPdfInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	class UCameraComponent* OwnerCamera;

	float CurrTime;
	float RerenderTime = 0.1;

	FHitResult HitResult;

	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* PdfClickAction;

	void OnClicked(const FInputActionValue& Value);


	AActor* TileLineTrace();
};
