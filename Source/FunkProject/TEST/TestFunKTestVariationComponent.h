// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Extensions/FunKTestFragment.h"
#include "Extensions/FunKTestVariationComponent.h"
#include "TestFunKTestVariationComponent.generated.h"


class UTestFunKTestVariationComponent;

UCLASS(NotBlueprintType, HideDropdown)
class UTestFunKTestVariationFragment : public UFunKTestFragment
{
	GENERATED_BODY()

public:
	virtual FString GetReadableIdent() const override;
	virtual void OnAdded() override;
	virtual void OnRemoved() override;
	
	UPROPERTY()
	TWeakObjectPtr<UTestFunKTestVariationComponent> Spawner = nullptr;
	int32 Index;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FUNKPROJECT_API UTestFunKTestVariationComponent : public UFunKTestVariationComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTestFunKTestVariationComponent();

	virtual int32 GetCount() override;
	virtual UFunKTestFragment* GetFragment(int32 Index) override;
	virtual bool IsReady(UFunKTestFragment* Instance, int32 Index) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Current = INDEX_NONE;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FunK")
	int32 WaitFor = 0;

	int32 CalledIsReady = 0;

	friend UTestFunKTestVariationFragment;
};
