// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"

#include "FunKWorldSubsystem.h"
#include "Internal/EventBus/FunKEventBusSubsystem.h"


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
		Subsystem->On<FTestEvent>([](const FTestEvent& test)
		{
			UE_LOG(LogTemp, Error, TEXT("MY EVENT SAYS: %s"), *test.MyMessage);

			if(test.ActorPointerTest)
			{
				UE_LOG(LogTemp, Error, TEXT("MY EVENT HAS POINTER"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("MY EVENT MISSES THE POINTER"));
			}
		});
		
		Subsystem->At<FFunKEventBusControllerEvent>([](const FFunKEventBusControllerEvent& eve)
		{
			UE_LOG(LogTemp, Error, TEXT("Constroller stats: %d/%d"), eve.ControllersReady, eve.Controllers);
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

void ATestPawn::ServerEventCallback_Implementation(FTestEvent callbackId)
{
}

void ATestPawn::ClientEventCallback_Implementation(FTestEvent callbackId)
{
}

void ATestPawn::TestEvent()
{
	if(UFunKEventBusSubsystem* Subsystem = GetWorld()->GetSubsystem<UFunKEventBusSubsystem>())
	{
		FTestEvent eve;
		eve.MyMessage = "This is my super cool test message!";
		eve.ActorPointerTest = this;
		
		Subsystem->Raise(eve, [this]()
		{
			const UFunKWorldSubsystem* FunKWorldSubsystem = GetWorld()->GetSubsystem<UFunKWorldSubsystem>();
			UE_LOG(LogTemp, Error, TEXT("CALLBACK IS IN %s"), *FString::FromInt(FunKWorldSubsystem->GetPeerIndex()));
		});
	}
}

void ATestPawn::TestDisableInput()
{
	UGameInstance* GameInst = GetWorld()->GetGameInstance();
	UGameViewportClient* ViewportClient = GameInst->GetGameViewportClient();

	ViewportClient->SetIgnoreInput(true);
}

