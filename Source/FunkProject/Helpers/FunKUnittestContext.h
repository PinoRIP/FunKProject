// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBus/FunKEventBusSubsystem.h"
#include "UObject/Object.h"
#include "Events/FunKEvent.h"
#include "FunKUnittestContext.generated.h"

/**
 * 
 */
UCLASS()
class FUNKPROJECT_API UFunKUnittestContext : public UObject
{
	GENERATED_BODY()

public:
	void SetWorld(UWorld* world);
	

	bool Has(EFunKEventType InType);
	bool HasOnly(FFunKEvent InEvent);

	TArray<FFunKEvent> Events;

	static bool CheckContext(const FFunKEvent& check, const FFunKEvent& in);

	virtual UWorld* GetWorld() const override;
	virtual void BeginDestroy() override;

private:
	UPROPERTY()
	UWorld* World = nullptr;

	FFunKEventBusRegistration Registration;
};
