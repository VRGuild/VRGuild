// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Global/Interfaces/CIInteractionInterface.h"
#include "TestWidgetComp.generated.h"

/**
 * 
 */

class ACANoticeBoard;

UCLASS()
class VRGUILD_API UTestWidgetComp : public UWidgetComponent, public ICIInteractionInterface
{
	GENERATED_BODY()
public: 
	UTestWidgetComp();
protected:
	virtual void InitializeComponent() override;
	virtual bool CanTrace(ACharacter* Initiator) const override;
	virtual bool CanInteract(ACharacter* Initiator) const override;

	virtual void BeginTrace(ACharacter* Initiator) override;
	virtual void EndTrace(ACharacter* Initiator) override;
	virtual void BeginInteract(ACharacter* Initiator) override;
	virtual void EndInteract(ACharacter* Initiator) override;
private:
	TObjectPtr<ACANoticeBoard> NoticeBoard;
};
