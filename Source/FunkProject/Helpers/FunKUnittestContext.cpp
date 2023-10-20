// Fill out your copyright notice in the Description page of Project Settings.


#include "FunKUnittestContext.h"

#include "EventBus/FunKEventBusSubsystem.h"

bool AFunKUnittestContext::Has(EFunKEventType InType)
{
	for (FFunKEvent& Event : Events)
	{
		if(Event.Type == InType)
			return true;
	}

	return false;
}

bool AFunKUnittestContext::HasOnly(FFunKEvent InEvent)
{
	for (FFunKEvent& Event : Events)
	{
		if(!CheckContext(Event, InEvent))
			return false;
	}

	return Events.Num() > 0;
}

void AFunKUnittestContext::RaiseEvent(FFunKEvent& Event) const
{
	AFunKUnittestContext* that = const_cast<AFunKUnittestContext*>(this);
	that->Events.Add(FFunKEvent(Event));
}

bool AFunKUnittestContext::CheckContext(const FFunKEvent& check, const FFunKEvent& in)
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

void AFunKUnittestContext::BeginDestroy()
{
	Registration.Unregister();
	
	UObject::BeginDestroy();
}

