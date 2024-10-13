// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EventBusTestEvent.generated.h"

USTRUCT()
struct FEventBusTestEvent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Property = 0;
};
