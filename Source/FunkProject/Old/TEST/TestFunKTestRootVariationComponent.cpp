// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestRootVariationComponent.h"


FString UTestFunKTestRootVariationFragment::GetLogName() const
{
	if (Index == INDEX_NONE)
		return "Variation Root Test Pending";
	
	return "Variation Root Test " + FString::FromInt(Index);
}

void UTestFunKTestRootVariationFragment::OnAdded()
{
	Spawner->Current = Index;
	Spawner->CalledIsReady = 0;
}

void UTestFunKTestRootVariationFragment::OnRemoved()
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

UFunKTestFragment* UTestFunKTestRootVariationComponent::GetFragment(int32 Index)
{
	UTestFunKTestRootVariationFragment* Functionality = NewObject<UTestFunKTestRootVariationFragment>();
	Functionality->Spawner = this;
	Functionality->Index = Index;

	return Functionality;
}

bool UTestFunKTestRootVariationComponent::IsReady(UFunKTestFragment* Instance, int32 Index)
{
	return WaitFor <= CalledIsReady++;
}



