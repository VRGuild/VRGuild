// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CACStickRayBoard.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRGUILD_API UCACStickRayBoard : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACStickRayBoard();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* BoardClickAction;

	// 레이캐스트 설정값들도 에디터에서 수정 가능하게
	UPROPERTY(EditAnywhere, Category = "Raycast")
	float RayLength = 1000.0f;
public:	

	UFUNCTION(BlueprintCallable)
	bool RayBoard();

	UFUNCTION(BlueprintImplementableEvent)
	void PointRayForMemo(const FHitResult& result);
	
	UFUNCTION(BlueprintCallable)
	void CreateBoardWord(FVector location, FString memoString);

	void OnClicked(const FInputActionValue& Value);
};
