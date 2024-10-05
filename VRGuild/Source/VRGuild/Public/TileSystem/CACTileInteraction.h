// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CACTileInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACTileInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACTileInteraction();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Owner;

	class UCameraComponent* OwnerCamera;

	float CurrTime;
	float RerenderTime = 0.1;

	FHitResult HitResult;

public:	

	bool DebugMode = false;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeComponent() override;
	
	void TileLineTrace();

	void HoverTile();
	void AddTile();
	void DeleteTile();

	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* TileAddAction;

	bool bOnClick = false;

	float OnClickTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MaxHoldTime = 1;

	void OnClicked(const FInputActionValue& Value);
	void OnHolding(const FInputActionValue& Value);
	void OnReleased(const FInputActionValue& Value);

};
