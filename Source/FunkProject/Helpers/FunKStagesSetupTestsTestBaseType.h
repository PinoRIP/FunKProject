// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Old/FunKTestBase.h"
#include "FunKStagesSetupTestsTestBaseType.generated.h"

/**
 * 
 */
UCLASS()
class FUNKPROJECT_API AFunKStagesSetupTestsTestBaseType : public AFunKTestBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void TestFunction1()
	{
		TestFunction1HasBeenCalled = true;
	}

	bool TestFunction1HasBeenCalled = false;

	UFUNCTION()
	void TestFunction2()
	{
		TestFunction2HasBeenCalled = true;
	}

	bool TestFunction2HasBeenCalled = false;
	
	UFUNCTION()
	void TestFunction3()
	{
		TestFunction3HasBeenCalled = true;
	}

	bool TestFunction3HasBeenCalled = false;

	UFUNCTION()
	void TestFunction4()
	{
		TestFunction4HasBeenCalled = true;
	}

	bool TestFunction4HasBeenCalled = false;
};
