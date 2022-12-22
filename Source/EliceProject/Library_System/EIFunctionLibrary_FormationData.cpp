// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_System/EIFunctionLibrary_FormationData.h"

FVector UEIFunctionLibrary_FormationData::GetFormationPosition(FVector InCenterPosition, int32 InInterval, int32 InSlotIdx)
{
	/* ±âº» PositionIndex
	* ------------------
	*|	0  |  1  |  2  |
	*|	3  |  4  |  5  |
	*|	6  |  7  |  8  |
	* ------------------*/

	FVector Formation = FVector::ZeroVector;
	switch (InSlotIdx)
	{
	case 0: Formation = InCenterPosition + FVector(InInterval, -InInterval, 0.f);	break;
	case 1: Formation = InCenterPosition + FVector(InInterval, 0.f, 0.f);			break;
	case 2: Formation = InCenterPosition + FVector(InInterval, InInterval, 0.f);	break;
	case 3: Formation = InCenterPosition + FVector(0.f, -InInterval, 0.f);			break;
	case 4: Formation = InCenterPosition + FVector(0.f, 0.f, 0.f);					break;
	case 5: Formation = InCenterPosition + FVector(0.f, InInterval, 0.f);			break;
	case 6: Formation = InCenterPosition + FVector(-InInterval, -InInterval, 0.f);	break;
	case 7: Formation = InCenterPosition + FVector(-InInterval, 0.f, 0.f);			break;
	case 8: Formation = InCenterPosition + FVector(-InInterval, +InInterval, 0.f);	break;
	}

	return Formation;
}

