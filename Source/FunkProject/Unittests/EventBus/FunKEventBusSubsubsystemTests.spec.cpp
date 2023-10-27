#include "Misc/AutomationTest.h"
#include "EventBusTestEvent.h"
#include "EventBus/FunKEventBusSubsystem.h"
#include "Tests/AutomationEditorCommon.h"

BEGIN_DEFINE_SPEC(FFunKEventBusSubsystemTests, "FunKTests.EventBus.FunKEventBusSubsystemTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* World;
	UFunKEventBusSubsystem* EventBusSubsystem;
END_DEFINE_SPEC(FFunKEventBusSubsystemTests)

void FFunKEventBusSubsystemTests::Define()
{
	Describe("EventBusSystem", [this]()
	{
		BeforeEach([this]()
		{
			this->World = FAutomationEditorCommonUtils::CreateNewMap();
			this->EventBusSubsystem = this->World->GetSubsystem<UFunKEventBusSubsystem>();
		});

		Describe("On", [this]()
		{
			It("Should register events", [this]()
			{
				const FFunKEventBusRegistration Registration = this->EventBusSubsystem->On<FEventBusTestEvent>([](const FEventBusTestEvent&) { });
				TestTrue("IsValid", Registration.IsValid());
			});

			It("Should receive events", [this]()
			{
				bool bEventReceived = false;
				FFunKEventBusRegistration Registration = this->EventBusSubsystem->On<FEventBusTestEvent>([&bEventReceived](const FEventBusTestEvent&)
				{
					bEventReceived = true;
				});

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				TestTrue("Received", bEventReceived);
			});
		});

		Describe("At", [this]()
		{
			It("Should register events", [this]()
			{
				const FFunKEventBusRegistration Registration = this->EventBusSubsystem->At<FEventBusTestEvent>([](const FEventBusTestEvent&) { });
				TestTrue("IsValid", Registration.IsValid());
			});

			It("Should receive events", [this]()
			{
				bool bEventReceived = false;
				FFunKEventBusRegistration Registration = this->EventBusSubsystem->At<FEventBusTestEvent>([&bEventReceived](const FEventBusTestEvent&)
				{
					bEventReceived = true;
				});

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				TestTrue("Received", bEventReceived);
			});

			It("Should replay the last event version", [this]()
			{
				bool bEventReceived = false;

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				FFunKEventBusRegistration Registration = this->EventBusSubsystem->At<FEventBusTestEvent>([&bEventReceived](const FEventBusTestEvent&)
				{
					bEventReceived = true;
				});
				
				TestTrue("Received", bEventReceived);
			});
		});

		Describe("Has", [this]()
		{
			It("Should return true given an event of the type has been triggered", [this]()
			{
				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				TestTrue("Has", this->EventBusSubsystem->Has<FEventBusTestEvent>());
			});
			
			It("Should return false given no event of the type has been triggered", [this]()
			{
				TestFalse("Has", this->EventBusSubsystem->Has<FEventBusTestEvent>());
			});
		});

		Describe("AnyHandler", [this]()
		{
			It("Should return true given an event handler has been registered", [this]()
			{
				FFunKEventBusRegistration Registration = this->EventBusSubsystem->At<FEventBusTestEvent>([](const FEventBusTestEvent&) { });
				TestTrue("AnyHandler", this->EventBusSubsystem->AnyHandler());
			});
			
			It("Should return false given no event handler has been registered", [this]()
			{
				TestFalse("AnyHandler", this->EventBusSubsystem->AnyHandler());
			});
		});

		Describe("Registration", [this]()
		{
			Describe("Unregister", [this]()
			{
				It("Should unregister events", [this]()
				{
					FFunKEventBusRegistration Registration = this->EventBusSubsystem->On<FEventBusTestEvent>([](const FEventBusTestEvent&) { });

					Registration.Unregister();
					
					TestFalse("IsValid", Registration.IsValid());
					TestFalse("EventBusSubsystem has", this->EventBusSubsystem->AnyHandler());
				});
			});
		});
	});
}