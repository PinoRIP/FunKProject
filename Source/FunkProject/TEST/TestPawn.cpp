// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"

#include "Old/FunKWorldSubsystem.h"
#include "Old/EventBus/FunKEventBusSubsystem.h"


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

	if (UFunKEventBusSubsystem* Subsystem = GetWorld()->GetSubsystem<UFunKEventBusSubsystem>())
	{
		Subsystem->On<FTestEvent>([](const FTestEvent& Test)
		{
			UE_LOG(LogTemp, Error, TEXT("MY EVENT SAYS: %s"), *Test.MyMessage);

			if(Test.ActorPointerTest)
			{
				UE_LOG(LogTemp, Error, TEXT("MY EVENT HAS POINTER"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("MY EVENT MISSES THE POINTER"));
			}
		});
		
		Subsystem->At<FFunKEventBusControllerEvent>([](const FFunKEventBusControllerEvent& Eve)
		{
			UE_LOG(LogTemp, Error, TEXT("Constroller stats: %d/%d"), Eve.ControllersReady, Eve.Controllers);
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

void ATestPawn::ServerEventCallback_Implementation(FTestEvent CallbackId)
{
}

void ATestPawn::ClientEventCallback_Implementation(FTestEvent CallbackId)
{
}

void ATestPawn::TestEvent()
{
	if (UFunKEventBusSubsystem* Subsystem = GetWorld()->GetSubsystem<UFunKEventBusSubsystem>())
	{
		FTestEvent Eve;
		Eve.MyMessage = "This is my super cool test message!";
		Eve.ActorPointerTest = this;
		
		Subsystem->Raise(Eve, [this]()
		{
			const UFunKWorldSubsystem* FunKWorldSubsystem = GetWorld()->GetSubsystem<UFunKWorldSubsystem>();
			UE_LOG(LogTemp, Error, TEXT("CALLBACK IS IN %s"), *FString::FromInt(FunKWorldSubsystem->GetPeerIndex()));
		});
	}
}

void ATestPawn::TestDisableInput()
{
	const UGameInstance* GameInst = GetWorld()->GetGameInstance();
	UGameViewportClient* ViewportClient = GameInst->GetGameViewportClient();

	ViewportClient->SetIgnoreInput(true);
}

