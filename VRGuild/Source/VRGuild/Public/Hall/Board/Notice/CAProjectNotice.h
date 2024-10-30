// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/Project/CBPLProject.h"

#include "CoreMinimal.h"
#include "Global/CACarryInteractable.h"
#include "CAProjectNotice.generated.h"


UCLASS()
class VRGUILD_API ACAProjectNotice : public ACACarryInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAProjectNotice();

	virtual void Init(bool bIsEnabled, ACharacter* owner, bool bAttachToOwner, AActor* actorOrigin) override;

	virtual void BeginTrace(ACharacter* Initiator) override;

	virtual void BeginInteract(ACharacter* Initiator) override;

	virtual UUserWidget* GetPosterDisplayWidget() const override;

	virtual bool CanTrace(ACharacter* player) const override; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void OnRep_bEnabled() override;

	virtual FString GetTraceMessage(ACharacter* player) const override;

public:	
	UPROPERTY(Replicated, BlueprintReadWrite)
	FProjectNotice NoticeData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D WidgetDrawSize = { 400,440 };

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* RootSceneComp;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* FrontSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* BackSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetFrontSide;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetBackSide;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Settings)
	FString PlayerCarryingMessage;
};
