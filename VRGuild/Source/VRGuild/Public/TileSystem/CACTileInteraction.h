// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CACTileInteraction.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACTileInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACTileInteraction();

private:
	class ACATileSpace* grapTileSpace;

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

	virtual void InitializeComponent() override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//UFUNCTION(Server, Reliable,)
	//void SRPCAddTile(FVector relativePosition, class ACATileSpace* tileSpace);
	//void SRPCAddTile_Implementation(FVector relativePosition, class ACATileSpace* tileSpace);

	AActor* TileLineTrace();

	void HoverTile();
	void AddTile();
	void DeleteTile();

	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* TileAddAction;

	bool bHold = false;
	float currHoldTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MaxHoldTime = 1;

	void OnClicked(const FInputActionValue& Value);
	void OnHolding(const FInputActionValue& Value);
	void OnReleased(const FInputActionValue& Value);


};
