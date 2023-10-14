// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestRootVariationComponent.h"


FString UTestFunKTestRootVariationFunctionality::GetReadableIdent() const
{
	if(Index == INDEX_NONE) return "Variation Root Test Pending";
	return "Variation Root Test " + FString::FromInt(Index);
}

void UTestFunKTestRootVariationFunctionality::OnAdded()
{
	Spawner->Current = Index;
	Spawner->CalledIsReady = 0;
}

void UTestFunKTestRootVariationFunctionality::OnRemoved()
{
	Spawner->Current = INDEX_NONE;
}

// Sets default values for this component's properties
UTestFunKTestRootVariationComponent::UTestFunKTestRootVariationComponent()
{
}

int32 UTestFunKTestRootVariationComponent::GetCount()
{
	return 2;
}

UFunKTestFunctionality* UTestFunKTestRootVariationComponent::GetFunctionality(int32 Index)
{
	UTestFunKTestRootVariationFunctionality* Functionality = NewObject<UTestFunKTestRootVariationFunctionality>();
	Functionality->Spawner = this;
	Functionality->Index = Index;

	return Functionality;
}

bool UTestFunKTestRootVariationComponent::IsReady(UFunKTestFunctionality* Instance, int32 Index)
{
	return WaitFor <= CalledIsReady++;
}



