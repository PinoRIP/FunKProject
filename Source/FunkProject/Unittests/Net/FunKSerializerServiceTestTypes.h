// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/FunKSerializerService.h"
#include "UObject/Object.h"
#include "FunKSerializerServiceTestTypes.generated.h"

USTRUCT(meta=(FunK))
struct FUNKPROJECT_API FMyStruct
{
	GENERATED_BODY()

	FMyStruct()
		: A("")
		, B(0)
		, C(false)
	{  }

	UPROPERTY()
	FString A;
	
	UPROPERTY()
	int64 B;
	
	UPROPERTY()
	bool C;
};

USTRUCT(meta=(FunK))
struct FUNKPROJECT_API FMyAdvancedStruct
{
	GENERATED_BODY()

	FMyAdvancedStruct()
		: A("")
	{  }

	UPROPERTY()
	FString A;
	
	UPROPERTY()
	FFunKTransport Transport;
};
