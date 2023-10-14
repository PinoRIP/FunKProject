// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestVariationComponent.h"


FString UTestFunKTestVariationFunctionality::GetReadableIdent() const
{
	if(Index == INDEX_NONE) return "Variation Root Test Pending";
	return "Variation Root Test " + FString::FromInt(Index);
}

void UTestFunKTestVariationFunctionality::OnAdded()
{
	Spawner->Current = Index;
	Spawner->CalledIsReady = 0;
}

void UTestFunKTestVariationFunctionality::OnRemoved()
{
	Spawner->Current = INDEX_NONE;
}

// Sets default values for this component's properties
UTestFunKTestVariationComponent::UTestFunKTestVariationComponent()
{
}

int32 UTestFunKTestVariationComponent::GetCount()
{
	return 2;
}

UFunKTestFunctionality* UTestFunKTestVariationComponent::GetFunctionality(int32 Index)
{
	UTestFunKTestVariationFunctionality* Functionality = NewObject<UTestFunKTestVariationFunctionality>();
	Functionality->Spawner = this;
	Functionality->Index = Index;

	return Functionality;
}

bool UTestFunKTestVariationComponent::IsReady(UFunKTestFunctionality* Instance, int32 Index)
{
	return WaitFor <= CalledIsReady++;
}
