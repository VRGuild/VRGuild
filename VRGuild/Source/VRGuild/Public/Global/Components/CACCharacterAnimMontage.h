// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCharacterAnimMontage.generated.h"


UENUM(BlueprintType)
enum class EAnimMontageType : uint8
{
	POINT UMETA(DisplayName="Point"),
	PICKUP UMETA(DisplayName = "Pickup"),
	PICKDOWN UMETA(DisplayName = "Pickdown"),
	DANCE UMETA(DisplayName = "Dance")
};


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACCharacterAnimMontage : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCACCharacterAnimMontage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* PointAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* PickupAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* PickdownAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* DanceAnim;

	UFUNCTION(BlueprintImplementableEvent)
	void StartAnimMontage(EAnimMontageType value);



};
