// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/CBPLDynamicWidget.h"

void UCBPLDynamicWidget::SetImageTexture(UImage* image, UTexture2D* texture)
{
    if (image && texture)
    {
        image->SetBrushFromTexture(texture);
    }
}

void UCBPLDynamicWidget::SetImageSize(UImage* image, FVector2D imageSize)
{
    if (image)
    {
        image->SetDesiredSizeOverride(imageSize);
    }
}
