#include "Misc/AutomationTest.h"
#include "EventBusTestEvent.h"
#include "EventBus/FunKEventBusSubsystem.h"
#include "Tests/AutomationEditorCommon.h"

BEGIN_DEFINE_SPEC(FFunKEventBusSubsystemTests, "FFunKTests.EventBus.FunKEventBusSubsystemTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
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
				FEventBusRegistration registration = this->EventBusSubsystem->On<FEventBusTestEvent>([](const FEventBusTestEvent& test) { });
				TestTrue("IsValid", registration.IsValid());
			});

			It("Should receive events", [this]()
			{
				bool eventReceived = false;
				FEventBusRegistration registration = this->EventBusSubsystem->On<FEventBusTestEvent>([&eventReceived](const FEventBusTestEvent& test)
				{
					eventReceived = true;
				});

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				TestTrue("Received", eventReceived);
			});
		});

		Describe("At", [this]()
		{
			It("Should register events", [this]()
			{
				FEventBusRegistration registration = this->EventBusSubsystem->At<FEventBusTestEvent>([](const FEventBusTestEvent& test) { });
				TestTrue("IsValid", registration.IsValid());
			});

			It("Should receive events", [this]()
			{
				bool eventReceived = false;
				FEventBusRegistration registration = this->EventBusSubsystem->At<FEventBusTestEvent>([&eventReceived](const FEventBusTestEvent& test)
				{
					eventReceived = true;
				});

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				TestTrue("Received", eventReceived);
			});

			It("Should replay the last event version", [this]()
			{
				bool eventReceived = false;

				this->EventBusSubsystem->Raise(FEventBusTestEvent());
				
				FEventBusRegistration registration = this->EventBusSubsystem->At<FEventBusTestEvent>([&eventReceived](const FEventBusTestEvent& test)
				{
					eventReceived = true;
				});
				
				TestTrue("Received", eventReceived);
			});
		});

		Describe("Has", [this]()
		{
			It("Should return true given an event handler has been registered", [this]()
			{
				FEventBusRegistration registration = this->EventBusSubsystem->At<FEventBusTestEvent>([](const FEventBusTestEvent& test) { });
				TestTrue("Has", this->EventBusSubsystem->Has<FEventBusTestEvent>());
			});
			
			It("Should return false given no event handler has been registered", [this]()
			{
				TestFalse("Has", this->EventBusSubsystem->Has<FEventBusTestEvent>());
			});
		});

		Describe("Registration", [this]()
		{
			Describe("Unregister", [this]()
			{
				It("Should unregister events", [this]()
				{
					FEventBusRegistration registration = this->EventBusSubsystem->On<FEventBusTestEvent>([](const FEventBusTestEvent& test) { });

					registration.Unregister();
					
					TestFalse("IsValid", registration.IsValid());
					TestFalse("EventBusSubsystem has", this->EventBusSubsystem->Has<FEventBusTestEvent>());
				});
			});
		});
	});
}