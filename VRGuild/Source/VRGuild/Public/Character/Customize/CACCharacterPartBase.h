// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACCharacterPartBase.generated.h"


USTRUCT(BlueprintType, Atomic)
struct FCustomCharacterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FCustomCharacterInfo(){};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMesh* CustomSkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* CustomImage;
};


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
    TMap<int, FCustomCharacterInfo> SkeletalMeshBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* CharacterSKM;

	UFUNCTION(Server, Unreliable)
	void ServerSwitchSKM(int value);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSwitchSKM(int value);

private:
	void BeginCustomSetup(int value);
};
