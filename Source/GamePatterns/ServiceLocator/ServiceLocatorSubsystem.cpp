// Game Programming Patterns, Eugene Esaulenko, 2024

#include "ServiceLocatorSubsystem.h"

UServiceLocatorSubsystem* UServiceLocatorSubsystem::GetInstance()
{
    const FWorldContext* WorldContextObject = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
    return WorldContextObject->World()->GetGameInstance()->GetSubsystem<UServiceLocatorSubsystem>();
}

void UServiceLocatorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UServiceLocatorSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UServiceLocatorSubsystem::UnregisterAllServices()
{
    GetInstance()->Services.Empty();
    UE_LOG(LogTemp, Warning, TEXT("All services unregistered"));
}