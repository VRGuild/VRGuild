// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CACarryInteractable.h"
#include "CABasePoster.generated.h"

/**
 *
 */

DECLARE_DELEGATE(CompletedDelegate);

UCLASS()
class VRGUILD_API ACABasePoster : public ACACarryInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACABasePoster();

	virtual void BeginInteract(ACharacter* Initiator) override;

	virtual UUserWidget* GetPosterDisplayWidget() const;

	virtual bool CanTrace(ACharacter* player) const override;

	virtual void BindOnCompletedDelegate(ACABasePoster* posterToBind);
	UFUNCTION(BlueprintCallable)
	void ExecuteOnCompletedDelegate();

protected:
	CompletedDelegate OnCompleted;
	virtual void OnCompletedCallback();
	UFUNCTION(Server, Reliable)
	virtual void ServerExecuteOnCompletedDelegate();

	virtual void Destroyed() override;
	virtual void OnRep_bEnabled() override;

	virtual FString GetTraceMessage(ACharacter* player) const override;

	virtual bool CheckCanTrace(ACharacter* player) const PURE_VIRTUAL(ACABasePoster::CheckCanTrace, return false;);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|On Board Actor")
	FVector2D WidgetDrawSize = { 400,440 };

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* RootSceneComp;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* FrontSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* BackSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|On Board Actor")
	TSubclassOf<UUserWidget> WidgetFrontSide;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|On Board Actor")
	TSubclassOf<UUserWidget> WidgetBackSide;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings|Player")
	TSubclassOf<UUserWidget> PosterWidgetToDisplayClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Player")
	FString PlayerCarryingMessage;
};
