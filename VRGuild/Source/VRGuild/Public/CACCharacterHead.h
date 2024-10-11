// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCharacterHead.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCharacterHead : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACCharacterHead();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	class AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* CharacterHead;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMesh* HeadMesh0;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMesh* HeadMesh1;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMesh* HeadMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int, class USkeletalMesh*> HeadMeshBox;

	UFUNCTION()
	void SwitchHead(int value);

	UFUNCTION(Server, Unreliable)
	void ServerSwitchHead(int value);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSwitchHead(int value);

		
};
