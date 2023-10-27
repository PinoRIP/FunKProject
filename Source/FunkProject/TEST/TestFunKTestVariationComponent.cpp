// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestVariationComponent.h"


FString UTestFunKTestVariationFragment::GetLogName() const
{
	if(Index == INDEX_NONE)
		return "Variation Root Test Pending";
	
	return "Variation Root Test " + FString::FromInt(Index);
}

void UTestFunKTestVariationFragment::OnAdded()
{
	Spawner->Current = Index;
	Spawner->CalledIsReady = 0;
}

void UTestFunKTestVariationFragment::OnRemoved()
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

UFunKTestFragment* UTestFunKTestVariationComponent::GetFragment(int32 Index)
{
	UTestFunKTestVariationFragment* Functionality = NewObject<UTestFunKTestVariationFragment>();
	Functionality->Spawner = this;
	Functionality->Index = Index;

	return Functionality;
}

bool UTestFunKTestVariationComponent::IsReady(UFunKTestFragment* Instance, int32 Index)
{
	return WaitFor <= CalledIsReady++;
}
