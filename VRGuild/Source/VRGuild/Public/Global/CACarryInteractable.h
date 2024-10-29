// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/CAInteractable.h"
#include "CACarryInteractable.generated.h"

/**
 * 
 */

UENUM(Blueprintable)
enum class ECarriedType : uint8
{
	COMMISSION UMETA(DisplayName = "Commission"),
	REGISTRATION UMETA(DisplayName = "Registration"),
	NONE UMETA(DisplayName = "None")
};

class ACharacter;

UCLASS()
class VRGUILD_API ACACarryInteractable : public ACAInteractable
{
	GENERATED_BODY()
	
public:
	ACACarryInteractable();

	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorInteracted);

	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;

	FVector GetHeldScale() const;

	ECarriedType GetCarriedType() const;

	virtual UUserWidget* GetPosterDisplayWidget() const;

	bool IsEnabled() const;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<UUserWidget> PosterWidgetToDisplayClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<ACACarryInteractable> SelfActor;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector HeldScale;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector RelativeSocketLoc;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FRotator RelativeSocketRot;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FName HoldSocketName;

	UPROPERTY(EditAnywhere, Category = "Settings")
	ECarriedType CarryType;

	UFUNCTION()
	virtual void OnRep_bEnabled();
private:
	UPROPERTY(ReplicatedUsing = OnRep_bEnabled)
	bool bEnabled;
};
