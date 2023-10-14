// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functionality/FunKTestFunctionality.h"
#include "Variations/FunKTestRootVariationComponent.h"
#include "TestFunKTestRootVariationComponent.generated.h"

class UTestFunKTestRootVariationComponent;

UCLASS()
class UTestFunKTestRootVariationFunctionality : public UFunKTestFunctionality
{
	GENERATED_BODY()

public:
	virtual FString GetReadableIdent() const override;
	virtual void OnAdded() override;
	virtual void OnRemoved() override;
	
	UPROPERTY()
	TWeakObjectPtr<UTestFunKTestRootVariationComponent> Spawner = nullptr;
	int32 Index;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FUNKPROJECT_API UTestFunKTestRootVariationComponent : public UFunKTestRootVariationComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTestFunKTestRootVariationComponent();

	virtual int32 GetCount() override;
	virtual UFunKTestFunctionality* GetFunctionality(int32 Index) override;
	virtual bool IsReady(UFunKTestFunctionality* Instance, int32 Index) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Current = INDEX_NONE;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FunK")
	int32 WaitFor = 0;

	int32 CalledIsReady = 0;

	friend UTestFunKTestRootVariationFunctionality;
};
