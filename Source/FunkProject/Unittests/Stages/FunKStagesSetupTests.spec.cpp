#include "FunkProject/Helpers/FunKStagesSetupTestsTestBaseType.h"
#include "Misc/AutomationTest.h"
#include "Setup/FunKStagesSetup.h"

BEGIN_DEFINE_SPEC(FFunKStagesSetupTests, "FunKTests.StagesSetupTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	AFunKStagesSetupTestsTestBaseType* TestBaseInstance;
	FFunKStages Stages;
	FFunKStagesSetup Setup;
END_DEFINE_SPEC(FFunKStagesSetupTests)

void FFunKStagesSetupTests::Define()
{
	Describe("StagesSetup", [this]()
	{
		BeforeEach([this]()
		{
			TestBaseInstance = NewObject<AFunKStagesSetupTestsTestBaseType>();
			Stages = FFunKStages();
			Setup = FFunKStagesSetup(&Stages, TestBaseInstance);
		});

		It("AddStage should add a stage", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);

			TestEqual("Stage count", Stages.Stages.Num(), 1);
			TestFalse("Not Latent", Stages.Stages[0].IsLatent);
		});

		It("AddNamedStage should use the provided stage name", [this]()
		{
			const FName Expected = FName("MyCustomStageName");
			
			Setup.AddNamedStage<AFunKStagesSetupTestsTestBaseType>(Expected, &AFunKStagesSetupTestsTestBaseType::TestFunction1);

			TestEqual("Stage Name", Stages.Stages[0].Name, Expected);
		});

		It("AddStage should use the function name as stage name", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);

			TestEqual("Stage Name", Stages.Stages[0].Name, FName("TestFunction1"));
		});

		It("AddLatentStage should add a latent stage", [this]()
		{
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);

			TestEqual("Stage count", Stages.Stages.Num(), 1);
			TestTrue("Latent", Stages.Stages[0].IsLatent);
		});

		It("AddLatentStage should use the function name as stage name", [this]()
		{
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);

			TestEqual("Stage Name", Stages.Stages[0].Name, FName("TestFunction1"));
		});

		It("AddNamedLatentStage should use the provided stage name", [this]()
		{
			const FName Expected = FName("MyCustomStageName");
			
			Setup.AddNamedLatentStage<AFunKStagesSetupTestsTestBaseType>(Expected, &AFunKStagesSetupTestsTestBaseType::TestFunction1);

			TestEqual("Stage Name", Stages.Stages[0].Name, Expected);
		});

		It("ThenAddStage should add a stage after the setup handle it has been called on", [this]()
		{
			FFunKStageSetup FirstStage = Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction3);
			FirstStage.ThenAddStage(AFunKStagesSetupTestsTestBaseType, TestFunction2);

			Stages.Stages[1].StartDelegate.Execute();

			TestTrue("2 has been called", TestBaseInstance->TestFunction2HasBeenCalled);
			TestFalse("Not Latent", Stages.Stages[1].IsLatent);
		});

		It("ThenAddLatentStage should add a latent stage after the setup handle it has been called on", [this]()
		{
			FFunKLatentStageSetup FirstStage = Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1);
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction3);
			FirstStage.ThenAddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction2);

			Stages.Stages[1].StartDelegate.Execute();

			TestTrue("2 has been called", TestBaseInstance->TestFunction2HasBeenCalled);
			TestTrue("Latent", Stages.Stages[1].IsLatent);
		});

		It("SetRunOnStandalone should disable the stage for standalone given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnStandalone(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnStandalone);
			TestEqual("Count", Stages.OnStandaloneCount, 0);
		});

		It("SetRunOnStandalone should enable the stage for standalone given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnStandalone(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnStandalone);
			TestEqual("Count", Stages.OnStandaloneCount, 1);
		});

		It("SetRunOnListenServer should disable the stage for listen servers given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListenServer(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnListenServer);
			TestEqual("Count", Stages.OnListenServerCount, 0);
		});

		It("SetRunOnListenServer should enable the stage for listen servers given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListenServer(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnListenServer);
			TestEqual("Count", Stages.OnListenServerCount, 1);
		});

		It("SetRunOnListenServerClient should disable the stage for listen server clients given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListenServerClient(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnListenServerClient);
			TestEqual("Count", Stages.OnListenServerClientCount, 0);
		});

		It("SetRunOnListenServerClient should enable the stage for listen server clients given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListenServerClient(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnListenServerClient);
			TestEqual("Count", Stages.OnListenServerClientCount, 1);
		});

		It("SetRunOnListen should disable the stage for listen servers and listen server clients given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListen(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnListenServer);
			TestEqual("Count", Stages.OnListenServerCount, 0);
			TestFalse("IsOn False", Stages.Stages[0].IsOnListenServerClient);
			TestEqual("Count", Stages.OnListenServerClientCount, 0);
		});

		It("SetRunOnListen should enable the stage for listen servers and listen server clients given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnListen(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnListenServer);
			TestEqual("Count", Stages.OnListenServerCount, 1);
			TestTrue("IsOn True", Stages.Stages[0].IsOnListenServerClient);
			TestEqual("Count", Stages.OnListenServerClientCount, 1);
		});

		It("SetRunOnDedicatedServer should disable the stage for listen servers given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicatedServer(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnDedicatedServer);
			TestEqual("Count", Stages.OnDedicatedServerCount, 0);
		});

		It("SetRunOnDedicatedServer should enable the stage for listen servers given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicatedServer(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnDedicatedServer);
			TestEqual("Count", Stages.OnDedicatedServerCount, 1);
		});

		It("SetRunOnDedicatedServerClient should disable the stage for listen server clients given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicatedServerClient(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnDedicatedServerClient);
			TestEqual("Count", Stages.OnDedicatedServerClientCount, 0);
		});

		It("SetRunOnDedicatedServerClient should enable the stage for listen server clients given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicatedServerClient(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnDedicatedServerClient);
			TestEqual("Count", Stages.OnDedicatedServerClientCount, 1);
		});

		It("SetRunOnDedicated should disable the stage for listen servers and listen server clients given the parameter is set to false", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicated(false);

			TestFalse("IsOn False", Stages.Stages[0].IsOnDedicatedServer);
			TestEqual("Count", Stages.OnDedicatedServerCount, 0);
			TestFalse("IsOn False", Stages.Stages[0].IsOnDedicatedServerClient);
			TestEqual("Count", Stages.OnDedicatedServerClientCount, 0);
		});

		It("SetRunOnDedicated should enable the stage for listen servers and listen server clients given the parameter is set to true", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).SetRunOnDedicated(true);

			TestTrue("IsOn True", Stages.Stages[0].IsOnDedicatedServer);
			TestEqual("Count", Stages.OnDedicatedServerCount, 1);
			TestTrue("IsOn True", Stages.Stages[0].IsOnDedicatedServerClient);
			TestEqual("Count", Stages.OnDedicatedServerClientCount, 1);
		});

		It("MakeLatent should make a stage latent", [this]()
		{
			Setup.AddStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).MakeLatent();

			TestTrue("Latent", Stages.Stages[0].IsLatent);
		});

		It("UpdateTimeLimitTime should update the time limit time", [this]()
		{
			constexpr float ExpectedTime = 123123123.f;
			
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).UpdateTimeLimitTime(ExpectedTime);

			TestEqual("Time", Stages.Stages[0].TimeLimit.Time, ExpectedTime);
		});

		It("UpdateTimeLimitMessage should update the time limit message", [this]()
		{
			const FString ExpectedMessage = TEXT("My timeout message");
			
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).UpdateTimeLimitMessage(ExpectedMessage);

			TestEqual("Message", Stages.Stages[0].TimeLimit.Message.ToString(), ExpectedMessage);
		});

		It("UpdateTimeLimitResult should update the time limit message", [this]()
		{
			constexpr EFunKTestResult ExpectedResult = EFunKTestResult::Skipped;
			
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).UpdateTimeLimitResult(ExpectedResult);

			TestEqual("Result", Stages.Stages[0].TimeLimit.Result, ExpectedResult);
		});

		It("UpdateTimeLimit should update the whole time limit config", [this]()
		{
			constexpr float ExpectedTime = 123123123.f;
			const FString ExpectedMessage = TEXT("My timeout message");
			constexpr EFunKTestResult ExpectedResult = EFunKTestResult::Skipped;
			
			FFunKTimeLimit TimeLimit;
			TimeLimit.Time = ExpectedTime;
			TimeLimit.Message = FText::FromString(ExpectedMessage);
			TimeLimit.Result = ExpectedResult;
			
			Setup.AddLatentStage(AFunKStagesSetupTestsTestBaseType, TestFunction1).UpdateTimeLimit(TimeLimit);

			TestEqual("Time", Stages.Stages[0].TimeLimit.Time, ExpectedTime);
			TestEqual("Message", Stages.Stages[0].TimeLimit.Message.ToString(), ExpectedMessage);
			TestEqual("Result", Stages.Stages[0].TimeLimit.Result, ExpectedResult);
		});
	});
}
