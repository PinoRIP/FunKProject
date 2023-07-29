﻿#include "Misc/AutomationTest.h"
#include "Util/FunKAnonymousBitmask.h"

BEGIN_DEFINE_SPEC(FFunKAnonymousBitmaskTests, "FunKTests.AnonymousBitmaskTestsasd", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	END_DEFINE_SPEC(FFunKAnonymousBitmaskTests)

void FFunKAnonymousBitmaskTests::Define()
{
	Describe("IsClear", [this]()
	{
		It("Should be true by default", [this]()
		{
			const FFunKAnonymousBitmask AnonymousBitmask(1);
			TestTrue("IsClear", AnonymousBitmask.IsClear());
		});

		It("Should be false given a bit has been set", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);

			AnonymousBitmask.Set(0);
			
			TestFalse("IsClear", AnonymousBitmask.IsClear());
		});

		It("Should be false given the bit at the checked index has been set", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);

			AnonymousBitmask.Set(5);
			
			TestFalse("IsClear", AnonymousBitmask.IsClear(5));
		});

		It("Should be true given the bit at the checked index is clear", [this]()
		{
			const FFunKAnonymousBitmask AnonymousBitmask(10);
			TestTrue("IsClear", AnonymousBitmask.IsClear(5));
		});
	});

	Describe("IsSet", [this]()
	{
		It("Should be false by default", [this]()
		{
			const FFunKAnonymousBitmask AnonymousBitmask(1);
			TestFalse("IsSet", AnonymousBitmask.IsSet());
		});

		It("Should be true given all bits have been set", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);

			AnonymousBitmask.SetAll();
			
			TestTrue("IsSet", AnonymousBitmask.IsSet());
		});

		It("Should be false given the bit at the checked index is clear", [this]()
		{
			const FFunKAnonymousBitmask AnonymousBitmask(10);			
			TestFalse("IsSet", AnonymousBitmask.IsSet(5));
		});

		It("Should be true given the bit at the checked index has been set", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);

			AnonymousBitmask.Set(5);
			
			TestTrue("IsSet", AnonymousBitmask.IsSet(5));
		});
	});

	Describe("ClearAll", [this]()
	{
		It("Should clear all set bits", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);
			AnonymousBitmask.Set(1);
			AnonymousBitmask.Set(2);

			AnonymousBitmask.ClearAll();
			
			TestTrue("IsClear", AnonymousBitmask.IsClear());
			TestFalse("IsSet", AnonymousBitmask.IsSet());
		});
	});

	Describe("SetAll", [this]()
	{
		It("Should set all bits", [this]()
		{
			FFunKAnonymousBitmask AnonymousBitmask(10);

			AnonymousBitmask.SetAll();
			
			TestFalse("IsClear", AnonymousBitmask.IsClear());
			TestTrue("IsSet", AnonymousBitmask.IsSet());
		});
	});
}
