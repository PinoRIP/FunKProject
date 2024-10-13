// Fill out your copyright notice in the Description page of Project Settings.


#include "FunKUnittestContext.h"

#include "Old/EventBus/FunKEventBusSubsystem.h"

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
	AFunKUnittestContext* That = const_cast<AFunKUnittestContext*>(this);
	That->Events.Add(FFunKEvent(Event));
}

bool AFunKUnittestContext::CheckContext(const FFunKEvent& Check, const FFunKEvent& In)
{
	if(Check.Type != In.Type || !Check.Message.Contains(In.Message))
		return false;

	for (const FString& InContext : In.Context)
	{
		bool bFound = false;
		for (const FString& CheckContext : Check.Context)
		{
			bFound = CheckContext.Contains(InContext);
			if(bFound) break;
		}

		if(!bFound)
			return false;
	}

	return true;
}

void AFunKUnittestContext::BeginDestroy()
{
	Registration.Unregister();
	
	UObject::BeginDestroy();
}

