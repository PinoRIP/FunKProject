#include "FunKSerializerServiceTestTypes.h"
#include "Misc/AutomationTest.h"
#include "Net/FunKSerializerService.h"

BEGIN_DEFINE_SPEC(FFunKSerializerServiceTest, "FunKTests.FunKSerializerServiceTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UFunKSerializerService* Service;
END_DEFINE_SPEC(FFunKSerializerServiceTest)

void FFunKSerializerServiceTest::Define()
{
	Describe("FunKSerializerService", [this]()
	{
		BeforeEach([this]()
		{
			Service = NewObject<UFunKSerializerService>();
		});

		It("Should be able to serialize simple USTRUCTS", [this]()
		{
			FMyStruct Source;
			Source.A = "Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 ";
			Source.B = 123;
			Source.C = true;

			FFunKSerialization Serialization;
			bool result = Service->NetSerializeStruct<FMyStruct>(Serialization, Source);

			TestTrue("Return true", result);
			TestEqual("Data length", Serialization.Data.Num(), 1692);
		});

		It("Should be able to serialize nested Transport USTRUCTS", [this]()
		{
			FMyStruct SourceInner;
			SourceInner.A = "Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 ";
			SourceInner.B = 123;
			SourceInner.C = true;

			FMyAdvancedStruct Source;
			Source.A = "AAA";
			Source.Transport = FFunKTransport::Pack(SourceInner);

			FFunKSerialization Serialization;
			bool result = Service->NetSerializeStruct<FMyAdvancedStruct>(Serialization, Source);

			TestTrue("Return true", result);
			TestEqual("Data length", Serialization.Data.Num(), 1716);
		});

		It("Should be able to deserialize serialized simple USTRUCTS", [this]()
		{
			FMyStruct Source;
			Source.A = "Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 ";
			Source.B = 123;
			Source.C = true;

			FFunKSerialization Serialization;
			Service->NetSerializeStruct<FMyStruct>(Serialization, Source);

			FMyStruct Target;
			bool result = Service->NetDeserializeStruct<FMyStruct>(Serialization, Target);

			TestTrue("Return true", result);
			TestEqual("Property A", Target.A, Source.A);
			TestEqual("Property B", Target.B, Source.B);
			TestEqual("Property C", Target.C, Source.C);
		});

		It("Should be able to deserialize serialized nested Transport USTRUCTS", [this]()
		{
			FMyStruct SourceInner;
			SourceInner.A = "Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 Test 123 ";
			SourceInner.B = 123;
			SourceInner.C = true;

			FMyAdvancedStruct Source;
			Source.A = "AAA";
			Source.Transport = FFunKTransport::Pack(SourceInner);

			FFunKSerialization Serialization;
			Service->NetSerializeStruct<FMyAdvancedStruct>(Serialization, Source);

			FMyAdvancedStruct Target;
			bool result = Service->NetDeserializeStruct<FMyAdvancedStruct>(Serialization, Target);
			
			FMyStruct TargetInner;
			Target.Transport.Unpack(TargetInner);

			TestTrue("Return true", result);
			TestEqual("Property A", Target.A, Source.A);
			TestEqual("Nested Property A", TargetInner.A, TargetInner.A);
			TestEqual("Nested Property B", TargetInner.B, TargetInner.B);
			TestEqual("Nested Property C", TargetInner.C, TargetInner.C);
		});
	});
}
