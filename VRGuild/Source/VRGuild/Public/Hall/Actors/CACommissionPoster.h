// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CACommissionPoster.generated.h"

/**
 * 
 */

class UStaticMeshComponent;

UCLASS()
class VRGUILD_API ACACommissionPoster : public ACAInteractable
{
	GENERATED_BODY()
	
public:
	ACACommissionPoster();

	virtual void BeginTrace() override;
	virtual void EndTrace() override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TSubclassOf<UUserWidget> PosterWidgetToDisplayClass;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TSubclassOf<AActor> SelfActor;
};
