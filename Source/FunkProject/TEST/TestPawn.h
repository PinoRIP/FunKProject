﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

class ATestPawn;

USTRUCT()
struct FUNKPROJECT_API FTestEvent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString MyMessage;

	UPROPERTY()
	ATestPawn* ActorPointerTest = nullptr;
};

UCLASS()
class FUNKPROJECT_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable)
	void ServerEventCallback(FTestEvent CallbackId);

	UFUNCTION(Client, Reliable)
	void ClientEventCallback(FTestEvent CallbackId);

	UFUNCTION(BlueprintCallable)
	void TestEvent();

	UFUNCTION(BlueprintCallable)
	void TestDisableInput();
	
};
