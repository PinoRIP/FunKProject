// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Variations/FunKTestVariationComponent.h"
#include "TestFunKTestVariationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FUNKPROJECT_API UTestFunKTestVariationComponent : public UFunKTestVariationComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTestFunKTestVariationComponent();

	virtual int32 GetCount() override;
	virtual void Begin(int32 index) override;
	virtual bool IsReady() override;
	virtual void Finish() override;
	virtual FString GetName() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Current = INDEX_NONE;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FunK")
	int32 WaitFor = 0;

	int32 CalledIsReady = 0;
};
