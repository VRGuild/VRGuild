// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CACarryInteractable.generated.h"

/**
 * 
 */

class ACharacter;

UCLASS()
class VRGUILD_API ACACarryInteractable : public ACAInteractable
{
	GENERATED_BODY()
	
public:
	ACACarryInteractable();

	void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner);

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

	FVector GetHeldScale() const;

	TSubclassOf<UUserWidget> GetPosterDisplayWidgetClass() const;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<UUserWidget> PosterWidgetToDisplayClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<ACACarryInteractable> SelfActor;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector HeldScale;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FName HoldSocketName;

private:
	UPROPERTY(Replicated)
	bool bEnabled;
};
