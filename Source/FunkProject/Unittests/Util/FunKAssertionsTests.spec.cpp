#include "Events/FunKEvent.h"
#include "Util/FunKAssertions.h"
#include "FunkProject/Helpers/FunKTestObject.h"
#include "FunkProject/Helpers/FunKUnittestContext.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

BEGIN_DEFINE_SPEC(FFunKAssertionsTests, "FunKTests.AssertionsTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* World;
	UFunKUnittestContext* Context;
	UFunKTestObject* TestObject;
	FString RandomString;
END_DEFINE_SPEC(FFunKAssertionsTests)

void FFunKAssertionsTests::Define()
{
	Describe("Assertions", [this]() {
		BeforeEach([this]()
		{
			this->World = FAutomationEditorCommonUtils::CreateNewMap();
			this->Context = NewObject<UFunKUnittestContext>(this->World);
			this->Context->SetWorld(this->World);
			
			this->RandomString = FString::FromInt(FMath::RandRange(0, 6400000));
		});

		Describe("AssertTrue", [this]()
		{
			It("Should succeed given true is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertTrue(true, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given false is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertTrue(false, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFalse", [this]()
		{
			It("Should succeed given false is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertFalse(false, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given true is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertFalse(true, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertIsValid", [this]()
		{
			It("Should succeed given a valid object is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertIsValid(this->Context, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given an invalid object is provided", [this]()
			{
				const bool result = UFunKAssertions::AssertIsValid(nullptr, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertInt", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(1, EFunKComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertInt(2, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloat", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(1, EFunKComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertFloat(2, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDouble", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(1, EFunKComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDouble(2, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDateTime", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(1, EFunKComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool result = UFunKAssertions::AssertDateTime(2, EFunKComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertTransformEqual", [this]()
		{
			It("Should succeed given the actual transform equals the expected transform", [this]()
			{
				const FTransform transform = FTransform(FRotator(), FVector(), FVector());
				const bool result = UFunKAssertions::AssertTransformEqual(FTransform(transform), FTransform(transform), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual transform equals the expected transform within tolerance", [this]()
			{
				const FTransform expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform actual = FTransform(expected.GetRotation(), expected.GetTranslation() - 1.e-5f, expected.GetScale3D());
				const bool result = UFunKAssertions::AssertTransformEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual transform does not equal the expected transform", [this]()
			{
				const FTransform expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform actual = FTransform(expected.GetRotation(), expected.GetTranslation() + 50.f, expected.GetScale3D());
				const bool result = UFunKAssertions::AssertTransformEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});
		
		Describe("AssertTransformNotEqual", [this]()
		{
			It("Should succeed given the actual transform does not equal the expected transform", [this]()
			{
				const FTransform expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform actual = FTransform(expected.GetRotation(), expected.GetTranslation() + 50.f, expected.GetScale3D());
				const bool result = UFunKAssertions::AssertTransformNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual transform equals the expected transform", [this]()
			{
				const FTransform transform = FTransform(FRotator(), FVector(), FVector());
				const bool result = UFunKAssertions::AssertTransformNotEqual(FTransform(transform), FTransform(transform), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloatEqual", [this]()
		{
			It("Should succeed given the actual float equals the expected float", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatEqual(1, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual float equals the expected float within tolerance", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual float does not equal the expected float", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloatNotEqual", [this]()
		{
			It("Should succeed given the actual float does not equal the expected float", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatNotEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual float equals the expected float", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatNotEqual(1, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual float equals the expected float within tolerance", [this]()
			{
				const bool result = UFunKAssertions::AssertFloatNotEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDoubleEqual", [this]()
		{
			It("Should succeed given the actual double equals the expected double", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleEqual(1, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual double equals the expected double within tolerance", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual double does not equal the expected double", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDoubleNotEqual", [this]()
		{
			It("Should succeed given the actual double does not equal the expected double", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleNotEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual double equals the expected double", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleNotEqual(1, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual double equals the expected double within tolerance", [this]()
			{
				const bool result = UFunKAssertions::AssertDoubleNotEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertNameEqual", [this]()
		{
			It("Should succeed given the actual name equals the expected name", [this]()
			{
				const bool result = UFunKAssertions::AssertNameEqual("Test", "Test", this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual name does not equal the expected name", [this]()
			{
				const bool result = UFunKAssertions::AssertNameEqual("Not", "Equal", this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertNameNotEqual", [this]()
		{
			It("Should succeed given the actual name does not equal the expected name", [this]()
			{
				const bool result = UFunKAssertions::AssertNameNotEqual("Not", "Equal", this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual name equals the expected name", [this]()
			{
				const bool result = UFunKAssertions::AssertNameNotEqual("Test", "Test", this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertStringEqual", [this]()
		{
			It("Should succeed given the actual string equals the expected string", [this]()
			{
				const bool result = UFunKAssertions::AssertStringEqual("Test", "Test", this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual string does not equal the expected string", [this]()
			{
				const bool result = UFunKAssertions::AssertStringEqual("Not", "Equal", this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertStringNotEqual", [this]()
		{
			It("Should succeed given the actual string does not equal the expected string", [this]()
			{
				const bool result = UFunKAssertions::AssertStringNotEqual("Not", "Equal", this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual string equals the expected string", [this]()
			{
				const bool result = UFunKAssertions::AssertStringNotEqual("Test", "Test", this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertObjectEqual", [this]()
		{
			It("Should succeed given the actual object equals the expected object", [this]()
			{
				const bool result = UFunKAssertions::AssertObjectEqual(this->Context, this->Context, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual object does not equal the expected object", [this]()
			{
				this->TestObject = NewObject<UFunKTestObject>();
				const bool result = UFunKAssertions::AssertObjectEqual(this->Context, this->TestObject, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertObjectNotEqual", [this]()
		{
			It("Should succeed given the actual object does not equal the expected object", [this]()
			{
				this->TestObject = NewObject<UFunKTestObject>();
				const bool result = UFunKAssertions::AssertObjectNotEqual(this->Context, this->TestObject, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});
			
			It("Should fail given the actual object equals the expected object", [this]()
			{
				const bool result = UFunKAssertions::AssertObjectNotEqual(this->Context, this->Context, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertRotatorEqual", [this]()
		{
			It("Should succeed given the actual rotator equals the expected rotator", [this]()
			{
				const FRotator rotator = FRotator();
				const bool result = UFunKAssertions::AssertRotatorEqual(FRotator(rotator), FRotator(rotator), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual rotator equals the expected rotator within tolerance", [this]()
			{
				const FRotator expected = FRotator();
				const FRotator actual = FRotator(expected.Pitch, expected.Roll, expected.Yaw - 1.e-5f);
				const bool result = UFunKAssertions::AssertRotatorEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator does not equal the expected rotator", [this]()
			{
				const FRotator expected = FRotator();
				const FRotator actual = FRotator(expected.Pitch, expected.Roll, expected.Yaw - 1.e-3f);
				const bool result = UFunKAssertions::AssertRotatorEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertRotatorNotEqual", [this]()
		{
			It("Should succeed given the actual rotator does not equal the expected rotator", [this]()
			{
				const FRotator expected = FRotator();
				const FRotator actual = FRotator(expected.Pitch, expected.Roll, expected.Yaw - 1.e-3f);
				const bool result = UFunKAssertions::AssertRotatorNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator equals the expected rotator", [this]()
			{
				const FRotator rotator = FRotator();
				const bool result = UFunKAssertions::AssertRotatorNotEqual(FRotator(rotator), FRotator(rotator), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator equals the expected rotator within tolerance", [this]()
			{
				const FRotator expected = FRotator();
				const FRotator actual = FRotator(expected.Pitch, expected.Roll, expected.Yaw - 1.e-5f);
				const bool result = UFunKAssertions::AssertRotatorNotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVectorEqual", [this]()
		{
			It("Should succeed given the actual vector equals the expected vector", [this]()
			{
				const FVector vector = FVector();
				const bool result = UFunKAssertions::AssertVectorEqual(FVector(vector), FVector(vector), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector equals the expected vector within tolerance", [this]()
			{
				const FVector expected = FVector();
				const FVector actual = expected - 1.e-5f;
				const bool result = UFunKAssertions::AssertVectorEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector does not equal the expected vector", [this]()
			{
				const FVector expected = FVector();
				const FVector actual = expected - 1.e-3f;
				const bool result = UFunKAssertions::AssertVectorEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVectorNotEqual", [this]()
		{
			It("Should succeed given the actual vector does not equal the expected vector", [this]()
			{
				const FVector expected = FVector();
				const FVector actual = expected - 1.e-3f;
				const bool result = UFunKAssertions::AssertVectorNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector equals the expected vector", [this]()
			{
				const FVector vector = FVector();
				const bool result = UFunKAssertions::AssertVectorNotEqual(FVector(vector), FVector(vector), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector equals the expected vector within tolerance", [this]()
			{
				const FVector expected = FVector();
				const FVector actual = expected - 1.e-5f;
				const bool result = UFunKAssertions::AssertVectorNotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector2DEqual", [this]()
		{
			It("Should succeed given the actual vector2D equals the expected vector2D", [this]()
			{
				const FVector2D vector = FVector2D();
				const bool result = UFunKAssertions::AssertVector2DEqual(FVector2D(vector), FVector2D(vector), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector2D equals the expected vector2D within tolerance", [this]()
			{
				const FVector2D expected = FVector2D();
				const FVector2D actual = expected - 1.e-5f;
				const bool result = UFunKAssertions::AssertVector2DEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D does not equal the expected vector2D", [this]()
			{
				const FVector2D expected = FVector2D();
				const FVector2D actual = expected - 1.e-3f;
				const bool result = UFunKAssertions::AssertVector2DEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector2DNotEqual", [this]()
		{
			It("Should succeed given the actual vector2D does not equal the expected vector2D", [this]()
			{
				const FVector2D expected = FVector2D();
				const FVector2D actual = expected - 1.e-3f;
				const bool result = UFunKAssertions::AssertVector2DNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D equals the expected vector2D", [this]()
			{
				const FVector2D vector = FVector2D();
				const bool result = UFunKAssertions::AssertVector2DNotEqual(FVector2D(vector), FVector2D(vector), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D equals the expected vector2D within tolerance", [this]()
			{
				const FVector2D expected = FVector2D();
				const FVector2D actual = expected - 1.e-5f;
				const bool result = UFunKAssertions::AssertVector2DNotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector4Equal", [this]()
		{
			It("Should succeed given the actual vector4 equals the expected vector4", [this]()
			{
				const FVector4 vector = FVector4();
				const bool result = UFunKAssertions::AssertVector4Equal(FVector4(vector), FVector4(vector), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector4 equals the expected vector4 within tolerance", [this]()
			{
				const FVector4 expected = FVector4();
				const FVector4 actual = FVector4(expected.X, expected.Y, expected.Z, expected.W - 1.e-5f);
				const bool result = UFunKAssertions::AssertVector4Equal(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 does not equal the expected vector4", [this]()
			{
				const FVector4 expected = FVector4();
				const FVector4 actual = FVector4(expected.X, expected.Y, expected.Z, expected.W - 1.e-3f);
				const bool result = UFunKAssertions::AssertVector4Equal(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector4NotEqual", [this]()
		{
			It("Should succeed given the actual vector4 does not equal the expected vector4", [this]()
			{
				const FVector4 expected = FVector4();
				const FVector4 actual = FVector4(expected.X, expected.Y, expected.Z, expected.W - 1.e-3f);
				const bool result = UFunKAssertions::AssertVector4NotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 equals the expected vector4", [this]()
			{
				const FVector4 vector = FVector4();
				const bool result = UFunKAssertions::AssertVector4NotEqual(FVector4(vector), FVector4(vector), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 equals the expected vector4 within tolerance", [this]()
			{
				const FVector4 expected = FVector4();
				const FVector4 actual = FVector4(expected.X, expected.Y, expected.Z, expected.W - 1.e-5f);
				const bool result = UFunKAssertions::AssertVector4NotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});
		
		Describe("AsserQuatEqual", [this]()
		{
			It("Should succeed given the actual quat equals the expected quat", [this]()
			{
				const FQuat quat = FQuat();
				const bool result = UFunKAssertions::AsserQuatEqual(FQuat(quat), FQuat(quat), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual quat equals the expected quat within tolerance", [this]()
			{
				const FQuat expected = FQuat();
				const FQuat actual = FQuat(expected.X, expected.Y, expected.Z, expected.W - 1.e-5f);
				const bool result = UFunKAssertions::AsserQuatEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat does not equal the expected quat", [this]()
			{
				const FQuat expected = FQuat();
				const FQuat actual = FQuat(expected.X, expected.Y, expected.Z, expected.W - 1.e-3f);
				const bool result = UFunKAssertions::AsserQuatEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertQuatNotEqual", [this]()
		{
			It("Should succeed given the actual quat does not equal the expected quat", [this]()
			{
				const FQuat expected = FQuat();
				const FQuat actual = FQuat(expected.X, expected.Y, expected.Z, expected.W - 1.e-3f);
				const bool result = UFunKAssertions::AssertQuatNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat equals the expected quat", [this]()
			{
				const FQuat quat = FQuat();
				const bool result = UFunKAssertions::AssertQuatNotEqual(FQuat(quat), FQuat(quat), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat equals the expected quat within tolerance", [this]()
			{
				const FQuat expected = FQuat();
				const FQuat actual = FQuat(expected.X, expected.Y, expected.Z, expected.W - 1.e-5f);
				const bool result = UFunKAssertions::AssertQuatNotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});
		
		Describe("AsserMatrixEqual", [this]()
		{
			It("Should succeed given the actual matrix equals the expected matrix", [this]()
			{
				const FMatrix matrix = FMatrix();
				const bool result = UFunKAssertions::AsserMatrixEqual(FMatrix(matrix), FMatrix(matrix), this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual matrix equals the expected matrix within tolerance", [this]()
			{
				const FMatrix expected = FMatrix();
				FMatrix actual = expected;
				actual.SetColumn(0, actual.GetColumn(0) - 1.e-5f);
				const bool result = UFunKAssertions::AsserMatrixEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix does not equal the expected matrix", [this]()
			{
				const FMatrix expected = FMatrix();
				FMatrix actual = expected;
				actual.SetColumn(0, actual.GetColumn(0) - 1.e-3f);
				const bool result = UFunKAssertions::AsserMatrixEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertMatrixNotEqual", [this]()
		{
			It("Should succeed given the actual matrix does not equal the expected matrix", [this]()
			{
				const FMatrix expected = FMatrix();
				FMatrix actual = expected;
				actual.SetColumn(0, actual.GetColumn(0) - 1.e-3f);
				const bool result = UFunKAssertions::AssertMatrixNotEqual(actual, expected, this->RandomString, this->Context);

				TestTrue("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix equals the expected matrix", [this]()
			{
				const FMatrix matrix = FMatrix();
				const bool result = UFunKAssertions::AssertMatrixNotEqual(FMatrix(matrix), FMatrix(matrix), this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix equals the expected matrix within tolerance", [this]()
			{
				const FMatrix expected = FMatrix();
				FMatrix actual = expected;
				actual.SetColumn(0, actual.GetColumn(0) - 1.e-5f);
				const bool result = UFunKAssertions::AssertMatrixNotEqual(actual, expected, this->RandomString, this->Context);

				TestFalse("Result", result);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});
	});
}
