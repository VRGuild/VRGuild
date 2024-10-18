// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCharacterPartBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCharacterPartBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACCharacterPartBase();

	virtual void InitializeComponent() override;
	
	UFUNCTION(BlueprintCallable)
	void SwitchSKM(int value);

	int ValueSelected;

protected:	
	class AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int, class USkeletalMesh*> SkeletalMeshBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* CharacterSKM;


	UFUNCTION(Server, Unreliable)
	void ServerSwitchSKM(int value);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSwitchSKM(int value);
};
