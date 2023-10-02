// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunKTestVariationComponent.h"


// Sets default values for this component's properties
UTestFunKTestVariationComponent::UTestFunKTestVariationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

int32 UTestFunKTestVariationComponent::GetCount()
{
	return 2;
}

void UTestFunKTestVariationComponent::Begin(int32 index)
{
	Current = index;
	CalledIsReady = 0;
}

bool UTestFunKTestVariationComponent::IsReady()
{
	return WaitFor <= CalledIsReady++;
}

void UTestFunKTestVariationComponent::Finish()
{
	Current = INDEX_NONE;
	Super::Finish();
}

FString UTestFunKTestVariationComponent::GetName()
{
	return "Variation Test " + FString::FromInt(Current);
}

