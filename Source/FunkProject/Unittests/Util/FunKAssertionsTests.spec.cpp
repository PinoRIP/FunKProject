#include "Old/Events/FunKEvent.h"
#include "Old/Util/FunKAssertionBlueprintFunctionLibrary.h"
#include "FunkProject/Helpers/FunKTestObject.h"
#include "FunkProject/Helpers/FunKUnittestContext.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FFunKAssertionsTests, "FunKTests.AssertionsTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	AFunKUnittestContext* Context;
	UFunKTestObject* TestObject;
	FString RandomString;
END_DEFINE_SPEC(FFunKAssertionsTests)

void FFunKAssertionsTests::Define()
{
	Describe("Assertions", [this]()
	{
		BeforeEach([this]()
		{
			this->Context = NewObject<AFunKUnittestContext>();

			this->RandomString = FString::FromInt(FMath::RandRange(0, 6400000));
		});

		Describe("AssertTrue", [this]()
		{
			It("Should succeed given true is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTrue(true, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given false is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTrue(false, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFalse", [this]()
		{
			It("Should succeed given false is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFalse(false, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given true is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFalse(true, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertIsValid", [this]()
		{
			It("Should succeed given a valid object is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertIsValid(this->Context, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given an invalid object is provided", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertIsValid(nullptr, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertInt", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertInt(2, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloat", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloat(2, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDouble", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDouble(2, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDateTime", [this]()
		{
			It("EqualTo should succeed given actual equals expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::EqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("EqualTo should fail given actual does not equal expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::EqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::GreaterThan, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThan should fail given actual is not greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::GreaterThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThan should fail given actual is not less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::LessThan, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should succeed given actual is not equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("NotEqualTo should fail given actual equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::NotEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should succeed given actual is greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("GreaterThanOrEqualTo should fail given actual less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::GreaterThanOrEqualTo, 2, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is equal to expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should succeed given actual is less than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(1, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 2, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("LessThanOrEqualTo should fail given actual greater than expected", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDateTime(2, EFunKAssertionComparisonMethod::LessThanOrEqualTo, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertTransformEqual", [this]()
		{
			It("Should succeed given the actual transform equals the expected transform", [this]()
			{
				const FTransform Transform = FTransform(FRotator(), FVector(), FVector());
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTransformEqual(FTransform(Transform), FTransform(Transform), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual transform equals the expected transform within tolerance", [this]()
			{
				const FTransform Expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform Actual = FTransform(Expected.GetRotation(), Expected.GetTranslation() - 1.e-5f, Expected.GetScale3D());
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTransformEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual transform does not equal the expected transform", [this]()
			{
				const FTransform Expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform Actual = FTransform(Expected.GetRotation(), Expected.GetTranslation() + 50.f, Expected.GetScale3D());
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTransformEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertTransformNotEqual", [this]()
		{
			It("Should succeed given the actual transform does not equal the expected transform", [this]()
			{
				const FTransform Expected = FTransform(FRotator(), FVector(), FVector());
				const FTransform Actual = FTransform(Expected.GetRotation(), Expected.GetTranslation() + 50.f, Expected.GetScale3D());
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTransformNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual transform equals the expected transform", [this]()
			{
				const FTransform Transform = FTransform(FRotator(), FVector(), FVector());
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertTransformNotEqual(FTransform(Transform), FTransform(Transform), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloatEqual", [this]()
		{
			It("Should succeed given the actual float equals the expected float", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatEqual(1, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual float equals the expected float within tolerance", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual float does not equal the expected float", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertFloatNotEqual", [this]()
		{
			It("Should succeed given the actual float does not equal the expected float", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatNotEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual float equals the expected float", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatNotEqual(1, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual float equals the expected float within tolerance", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertFloatNotEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDoubleEqual", [this]()
		{
			It("Should succeed given the actual double equals the expected double", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleEqual(1, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual double equals the expected double within tolerance", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual double does not equal the expected double", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertDoubleNotEqual", [this]()
		{
			It("Should succeed given the actual double does not equal the expected double", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleNotEqual(1 - 1.e-3f, 1, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual double equals the expected double", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleNotEqual(1, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual double equals the expected double within tolerance", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertDoubleNotEqual(1 - 1.e-5f, 1, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertNameEqual", [this]()
		{
			It("Should succeed given the actual name equals the expected name", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertNameEqual("Test", "Test", this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual name does not equal the expected name", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertNameEqual("Not", "Equal", this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertNameNotEqual", [this]()
		{
			It("Should succeed given the actual name does not equal the expected name", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertNameNotEqual("Not", "Equal", this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual name equals the expected name", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertNameNotEqual("Test", "Test", this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertStringEqual", [this]()
		{
			It("Should succeed given the actual string equals the expected string", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertStringEqual("Test", "Test", this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual string does not equal the expected string", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertStringEqual("Not", "Equal", this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertStringNotEqual", [this]()
		{
			It("Should succeed given the actual string does not equal the expected string", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertStringNotEqual("Not", "Equal", this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual string equals the expected string", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertStringNotEqual("Test", "Test", this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertObjectEqual", [this]()
		{
			It("Should succeed given the actual object equals the expected object", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertObjectEqual(this->Context, this->Context, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual object does not equal the expected object", [this]()
			{
				this->TestObject = NewObject<UFunKTestObject>();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertObjectEqual(this->Context, this->TestObject, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertObjectNotEqual", [this]()
		{
			It("Should succeed given the actual object does not equal the expected object", [this]()
			{
				this->TestObject = NewObject<UFunKTestObject>();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertObjectNotEqual(this->Context, this->TestObject, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual object equals the expected object", [this]()
			{
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertObjectNotEqual(this->Context, this->Context, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertRotatorEqual", [this]()
		{
			It("Should succeed given the actual rotator equals the expected rotator", [this]()
			{
				const FRotator Rotator = FRotator();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorEqual(FRotator(Rotator), FRotator(Rotator), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual rotator equals the expected rotator within tolerance", [this]()
			{
				const FRotator Expected = FRotator();
				const FRotator Actual = FRotator(Expected.Pitch, Expected.Roll, Expected.Yaw - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator does not equal the expected rotator", [this]()
			{
				const FRotator Expected = FRotator();
				const FRotator Actual = FRotator(Expected.Pitch, Expected.Roll, Expected.Yaw - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertRotatorNotEqual", [this]()
		{
			It("Should succeed given the actual rotator does not equal the expected rotator", [this]()
			{
				const FRotator Expected = FRotator();
				const FRotator Actual = FRotator(Expected.Pitch, Expected.Roll, Expected.Yaw - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator equals the expected rotator", [this]()
			{
				const FRotator Rotator = FRotator();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorNotEqual(FRotator(Rotator), FRotator(Rotator), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual rotator equals the expected rotator within tolerance", [this]()
			{
				const FRotator Expected = FRotator();
				const FRotator Actual = FRotator(Expected.Pitch, Expected.Roll, Expected.Yaw - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertRotatorNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVectorEqual", [this]()
		{
			It("Should succeed given the actual vector equals the expected vector", [this]()
			{
				const FVector Vector = FVector();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorEqual(FVector(Vector), FVector(Vector), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector equals the expected vector within tolerance", [this]()
			{
				const FVector Expected = FVector();
				const FVector Actual = Expected - 1.e-5f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector does not equal the expected vector", [this]()
			{
				const FVector Expected = FVector();
				const FVector Actual = Expected - 1.e-3f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVectorNotEqual", [this]()
		{
			It("Should succeed given the actual vector does not equal the expected vector", [this]()
			{
				const FVector Expected = FVector();
				const FVector Actual = Expected - 1.e-3f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector equals the expected vector", [this]()
			{
				const FVector Vector = FVector();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorNotEqual(FVector(Vector), FVector(Vector), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector equals the expected vector within tolerance", [this]()
			{
				const FVector Expected = FVector();
				const FVector Actual = Expected - 1.e-5f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVectorNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector2DEqual", [this]()
		{
			It("Should succeed given the actual vector2D equals the expected vector2D", [this]()
			{
				const FVector2D Vector = FVector2D();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DEqual(FVector2D(Vector), FVector2D(Vector), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector2D equals the expected vector2D within tolerance", [this]()
			{
				const FVector2D Expected = FVector2D();
				const FVector2D Actual = Expected - 1.e-5f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D does not equal the expected vector2D", [this]()
			{
				const FVector2D Expected = FVector2D();
				const FVector2D Actual = Expected - 1.e-3f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector2DNotEqual", [this]()
		{
			It("Should succeed given the actual vector2D does not equal the expected vector2D", [this]()
			{
				const FVector2D Expected = FVector2D();
				const FVector2D Actual = Expected - 1.e-3f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D equals the expected vector2D", [this]()
			{
				const FVector2D Vector = FVector2D();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DNotEqual(FVector2D(Vector), FVector2D(Vector), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector2D equals the expected vector2D within tolerance", [this]()
			{
				const FVector2D Expected = FVector2D();
				const FVector2D Actual = Expected - 1.e-5f;
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector2DNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector4Equal", [this]()
		{
			It("Should succeed given the actual vector4 equals the expected vector4", [this]()
			{
				const FVector4 Vector = FVector4();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4Equal(FVector4(Vector), FVector4(Vector), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual vector4 equals the expected vector4 within tolerance", [this]()
			{
				const FVector4 Expected = FVector4();
				const FVector4 Actual = FVector4(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4Equal(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 does not equal the expected vector4", [this]()
			{
				const FVector4 Expected = FVector4();
				const FVector4 Actual = FVector4(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4Equal(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertVector4NotEqual", [this]()
		{
			It("Should succeed given the actual vector4 does not equal the expected vector4", [this]()
			{
				const FVector4 Expected = FVector4();
				const FVector4 Actual = FVector4(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4NotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 equals the expected vector4", [this]()
			{
				const FVector4 Vector = FVector4();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4NotEqual(FVector4(Vector), FVector4(Vector), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual vector4 equals the expected vector4 within tolerance", [this]()
			{
				const FVector4 Expected = FVector4();
				const FVector4 Actual = FVector4(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertVector4NotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AsserQuatEqual", [this]()
		{
			It("Should succeed given the actual quat equals the expected quat", [this]()
			{
				const FQuat Quat = FQuat();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatEqual(FQuat(Quat), FQuat(Quat), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual quat equals the expected quat within tolerance", [this]()
			{
				const FQuat Expected = FQuat();
				const FQuat Actual = FQuat(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat does not equal the expected quat", [this]()
			{
				const FQuat Expected = FQuat();
				const FQuat Actual = FQuat(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertQuatNotEqual", [this]()
		{
			It("Should succeed given the actual quat does not equal the expected quat", [this]()
			{
				const FQuat Expected = FQuat();
				const FQuat Actual = FQuat(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat equals the expected quat", [this]()
			{
				const FQuat Quat = FQuat();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatNotEqual(FQuat(Quat), FQuat(Quat), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual quat equals the expected quat within tolerance", [this]()
			{
				const FQuat Expected = FQuat();
				const FQuat Actual = FQuat(Expected.X, Expected.Y, Expected.Z, Expected.W - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertQuatNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AsserMatrixEqual", [this]()
		{
			It("Should succeed given the actual matrix equals the expected matrix", [this]()
			{
				const FMatrix Matrix = FMatrix();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AsserMatrixEqual(FMatrix(Matrix), FMatrix(Matrix), this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should succeed given the actual matrix equals the expected matrix within tolerance", [this]()
			{
				const FMatrix Expected = FMatrix();
				FMatrix Actual = Expected;
				Actual.SetColumn(0, Actual.GetColumn(0) - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AsserMatrixEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix does not equal the expected matrix", [this]()
			{
				const FMatrix Expected = FMatrix();
				FMatrix Actual = Expected;
				Actual.SetColumn(0, Actual.GetColumn(0) - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AsserMatrixEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});

		Describe("AssertMatrixNotEqual", [this]()
		{
			It("Should succeed given the actual matrix does not equal the expected matrix", [this]()
			{
				const FMatrix Expected = FMatrix();
				FMatrix Actual = Expected;
				Actual.SetColumn(0, Actual.GetColumn(0) - 1.e-3f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertMatrixNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestTrue("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Info(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix equals the expected matrix", [this]()
			{
				const FMatrix Matrix = FMatrix();
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertMatrixNotEqual(FMatrix(Matrix), FMatrix(Matrix), this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});

			It("Should fail given the actual matrix equals the expected matrix within tolerance", [this]()
			{
				const FMatrix Expected = FMatrix();
				FMatrix Actual = Expected;
				Actual.SetColumn(0, Actual.GetColumn(0) - 1.e-5f);
				const bool bResult = UFunKAssertionBlueprintFunctionLibrary::AssertMatrixNotEqual(Actual, Expected, this->RandomString, this->Context);

				TestFalse("Result", bResult);
				TestTrue("Sink Valid", this->Context->HasOnly(FFunKEvent::Error(this->RandomString, this->Context->GetName())));
			});
		});
	});
}
