// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"
#include "EventBus/FunKEventBusSubsystem.h"


// Sets default values
ATestPawn::ATestPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();

	if(UFunKEventBusSubsystem* Subsystem = GetWorld()->GetSubsystem<UFunKEventBusSubsystem>())
	{
		FTestEvent eve;
		eve.MyMessage = "This is my super cool test message!";
		
		Subsystem->On<FTestEvent>([](const FTestEvent& test)
		{
			UE_LOG(LogTemp, Error, TEXT("MY EVENT SAYS: %s"), *test.MyMessage);
		});
	}
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestPawn::TestEvent()
{
	if(UFunKEventBusSubsystem* Subsystem = GetWorld()->GetSubsystem<UFunKEventBusSubsystem>())
	{
		FTestEvent eve;
		eve.MyMessage = "This is my super cool test message!";
		
		Subsystem->Raise(eve);
	}
}

