// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functionality/FunKTestFunctionality.h"
#include "Variations/FunKTestVariationComponent.h"
#include "TestFunKTestVariationComponent.generated.h"


UCLASS()
class UTestFunKTestVariationFunctionality : public UFunKTestFunctionality
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
	virtual UFunKTestFunctionality* GetFunctionality(int32 Index) override;
	virtual bool IsReady(UFunKTestFunctionality* Instance, int32 Index) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Current = INDEX_NONE;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FunK")
	int32 WaitFor = 0;

	int32 CalledIsReady = 0;

	friend UTestFunKTestVariationFunctionality;
};
