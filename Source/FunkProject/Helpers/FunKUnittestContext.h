// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunKTestBase.h"
#include "EventBus/FunKEventBusSubsystem.h"
#include "UObject/Object.h"
#include "Events/FunKEvent.h"
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

	static bool CheckContext(const FFunKEvent& Check, const FFunKEvent& In);

	virtual void BeginDestroy() override;

private:
	UPROPERTY()
	UWorld* World = nullptr;

	FFunKEventBusRegistration Registration;
};
