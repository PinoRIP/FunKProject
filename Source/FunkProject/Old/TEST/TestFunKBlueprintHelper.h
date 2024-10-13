// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFunKBlueprintHelper.generated.h"

class UFunKTestVariationComponent;
/**
 * 
 */
UCLASS()
class FUNKPROJECT_API UTestFunKBlueprintHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FunK|Test")
	static void BeginVariationComponent(UFunKTestVariationComponent* Component, int32 Index = 0);

	UFUNCTION(BlueprintCallable, Category = "FunK|Test")
	static void FinishVariationComponent(UFunKTestVariationComponent* Component);
	
};
