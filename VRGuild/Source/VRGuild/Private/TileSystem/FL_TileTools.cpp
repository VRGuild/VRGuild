// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/FL_TileTools.h"

FVector UFL_TileTools::SnapGridVector(FVector vector, float gridSize)
{
	FVector gridVector = FVector(
		FMath::GridSnap(vector.X, gridSize),
		FMath::GridSnap(vector.Y, gridSize),
		FMath::GridSnap(vector.Z, gridSize)
	);
	return gridVector;
}
