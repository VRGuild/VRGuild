// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACTileFurniture.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FTileFurnitureInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FTileFurnitureInfo(){};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<AActor> TileFurniture;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* CustomImage;
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACTileFurniture : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACTileFurniture();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int, FTileFurnitureInfo> TileFurnitureBox;

	UFUNCTION(BlueprintCallable)
	void SwitchFurniture(int value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
