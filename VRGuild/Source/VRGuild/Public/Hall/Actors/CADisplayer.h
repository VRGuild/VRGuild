// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CADisplayer.generated.h"

/**
 * 
 */

class ACAProjectNotice;
class UWidgetComponent;
class ATP_ThirdPersonCharacter;
class UCWCDisplayScroll;

UCLASS()
class VRGUILD_API ACADisplayer : public ACAInteractable
{
	GENERATED_BODY()
public:
	ACADisplayer();

	virtual void BeginPlay() override;

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	void EndScroll(ACharacter* Initiator);

	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	//virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Owner() override;
	
	virtual FString GetTraceMessage(ACharacter* player) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Settings)
	TObjectPtr<UCWCDisplayScroll> WidgetComponent;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Settings)
	TObjectPtr<UWidgetComponent> WidgetComponent2;*/

	UFUNCTION(Server, Reliable)
	void ServerDisplayCommission(AActor* commissionPassed);
	
	UFUNCTION(Server, Reliable)
	void ServerPickupCommission(ACharacter* player);

	UFUNCTION(BlueprintImplementableEvent)
	void StartAnimateScrolling();
	UFUNCTION(BlueprintImplementableEvent)
	void StopAnimateScrolling();
	UFUNCTION(BlueprintImplementableEvent)
	void OnMousePressInteract(FVector2D result);

private:
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	FString ErrorMessage;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FString DisplayMessage;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FString PickupMessage;

	UPROPERTY(ReplicatedUsing = OnRep_ActorDisplayed)
	TObjectPtr<ACAProjectNotice> ActorDisplayed;
	UFUNCTION()
	void OnRep_ActorDisplayed();

	/*FVector2D StartMousePos;
	FVector2D UpdatedMousePos;
	TObjectPtr<ATP_ThirdPersonCharacter> PlayerThatStartedInteracting;*/


	/*UPROPERTY(EditDefaultsOnly, Category = Settings)
	TSubclassOf<UUserWidget> BackSideWidgetClass;*/
};
