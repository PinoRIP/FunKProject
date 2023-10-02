// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestRootVariationComponent.h"


// Sets default values for this component's properties
UTestFunKTestRootVariationComponent::UTestFunKTestRootVariationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

int32 UTestFunKTestRootVariationComponent::GetCount()
{
	return 2;
}

void UTestFunKTestRootVariationComponent::Begin(int32 index)
{
	Current = index;
	CalledIsReady = 0;
}

bool UTestFunKTestRootVariationComponent::IsReady()
{
	return WaitFor <= CalledIsReady++;
}

void UTestFunKTestRootVariationComponent::Finish()
{
	Current = INDEX_NONE;
	Super::Finish();
}

FString UTestFunKTestRootVariationComponent::GetName()
{
	if(Current == INDEX_NONE) return "Variation Root Test Pending";
	return "Variation Root Test " + FString::FromInt(Current);
}



