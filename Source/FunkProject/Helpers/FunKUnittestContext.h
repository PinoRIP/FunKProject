// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Internal/FunKTestBase.h"
#include "Internal/EventBus/FunKEventBusSubsystem.h"
#include "UObject/Object.h"
#include "Internal/Events/FunKEvent.h"
#include "FunKUnittestContext.generated.h"

/**
 * 
 */
UCLASS()
class FUNKPROJECT_API AFunKUnittestContext : public AFunKTestBase
{
	GENERATED_BODY()

public:
	bool Has(EFunKEventType InType);
	bool HasOnly(FFunKEvent InEvent);

	TArray<FFunKEvent> Events;

	virtual void RaiseEvent(FFunKEvent& Event) const override;

	static bool CheckContext(const FFunKEvent& check, const FFunKEvent& in);

	virtual void BeginDestroy() override;

private:
	UPROPERTY()
	UWorld* World = nullptr;

	FFunKEventBusRegistration Registration;
};
