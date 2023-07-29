// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sinks/FunKSink.h"
#include "UObject/Object.h"
#include "FunKUnittestSink.generated.h"

/**
 * 
 */
UCLASS()
class FUNKPROJECT_API UFunKUnittestSink : public UObject, public IFunKSink
{
	GENERATED_BODY()

public:
	virtual void RaiseEvent(const FFunKEvent& raisedEvent) const override;

	bool Has(EFunKEventType InType);
	bool HasOnly(FFunKEvent InEvent);

	TArray<FFunKEvent> Events;

	static bool CheckContext(const FFunKEvent& check, const FFunKEvent& in);
};
