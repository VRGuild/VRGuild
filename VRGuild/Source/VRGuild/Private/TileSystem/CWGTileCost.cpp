// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CWGTileCost.h"

void UCWGTileCost::InitializeSetting(ACATileZone* targetZone, ETileCostType tileCostType, FVector position, ESpaceType spaceType, int32 cost)
{
	this->TargetTileZone = targetZone;
	this->TileConstType = tileCostType;
	this->Position = position;
	this->SpaceType = spaceType;
	this->Cost = cost;
	UpdateInit();
}
