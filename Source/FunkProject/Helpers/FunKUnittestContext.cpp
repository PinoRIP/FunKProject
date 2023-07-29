// Fill out your copyright notice in the Description page of Project Settings.


#include "FunKUnittestContext.h"

#include "EventBus/FunKEventBusSubsystem.h"

void UFunKUnittestContext::SetWorld(UWorld* world)
{
	auto eventBus = world->GetSubsystem<UFunKEventBusSubsystem>();
	Registration = eventBus->On<FFunKEvent>([this](const FFunKEvent& eve)
	{
		Events.Add(eve);
	});
}

bool UFunKUnittestContext::Has(EFunKEventType InType)
{
	for (FFunKEvent& Event : Events)
	{
		if(Event.Type == InType)
			return true;
	}

	return false;
}

bool UFunKUnittestContext::HasOnly(FFunKEvent InEvent)
{
	for (FFunKEvent& Event : Events)
	{
		if(!CheckContext(Event, InEvent))
			return false;
	}

	return Events.Num() > 0;
}

bool UFunKUnittestContext::CheckContext(const FFunKEvent& check, const FFunKEvent& in)
{
	if(check.Type != in.Type || !check.Message.Contains(in.Message))
		return false;

	for (const FString& InContext : in.Context)
	{
		bool found = false;
		for (const FString& CheckContext : check.Context)
		{
			found = CheckContext.Contains(InContext);
			if(found) break;
		}

		if(!found)
			return false;
	}

	return true;
}

UWorld* UFunKUnittestContext::GetWorld() const
{
	return World;
}

void UFunKUnittestContext::BeginDestroy()
{
	Registration.Unregister();
	
	UObject::BeginDestroy();
}

