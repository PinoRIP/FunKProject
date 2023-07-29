// Fill out your copyright notice in the Description page of Project Settings.


#include "FunKUnittestSink.h"

void UFunKUnittestSink::RaiseEvent(const FFunKEvent& raisedEvent) const
{
	UFunKUnittestSink* mutableThis = const_cast<UFunKUnittestSink*>(this);
	mutableThis->Events.Add(raisedEvent);
}

bool UFunKUnittestSink::Has(EFunKEventType InType)
{
	for (FFunKEvent& Event : Events)
	{
		if(Event.Type == InType)
			return true;
	}

	return false;
}

bool UFunKUnittestSink::HasOnly(FFunKEvent InEvent)
{
	for (FFunKEvent& Event : Events)
	{
		if(!CheckContext(Event, InEvent))
			return false;
	}

	return Events.Num() > 0;
}

bool UFunKUnittestSink::CheckContext(const FFunKEvent& check, const FFunKEvent& in)
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

