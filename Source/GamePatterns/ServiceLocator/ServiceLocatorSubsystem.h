// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServiceLocatorSubsystem.generated.h"

UCLASS()
class GAMEPATTERNS_API UServiceLocatorSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    template <typename T>
    static void RegisterService(T* Service)
    {
        static_assert(TIsDerivedFrom<T, UObject>::Value, "Service must be derived from UObject");

        if (Service == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Service is nullptr, cannot register: %s"), *T::StaticClass()->GetName());
            return;
        }
        
        UServiceLocatorSubsystem* Instance = GetInstance();
        const uint32 HashCode = GetTypeHash(T::StaticClass());

        if (Instance->Services.Contains(HashCode))
        {
            UE_LOG(LogTemp, Warning, TEXT("Service already registered: %s"), *T::StaticClass()->GetName());
            return;
        }

        Instance->Services.Add(HashCode, Service);
        UE_LOG(LogTemp, Warning, TEXT("Service registered: %s"), *T::StaticClass()->GetName());
    }

    template <typename T>
    static T* ResolveService()
    {
        static_assert(TIsDerivedFrom<T, UObject>::Value, "Service must be derived from UObject");
        
        UServiceLocatorSubsystem* Instance = GetInstance();
        const uint32 HashCode = GetTypeHash(T::StaticClass());

        if (!Instance->Services.Contains(HashCode))
        {
            UE_LOG(LogTemp, Warning, TEXT("Service not found: %s"), *T::StaticClass()->GetName());
            return nullptr;
        }

        return Cast<T>(Instance->Services[HashCode]);
    }

    template <typename T>
    static void UnregisterService()
    {
        static_assert(TIsDerivedFrom<T, UObject>::Value, "Service must be derived from UObject");
        
        UServiceLocatorSubsystem* Instance = GetInstance();
        const uint32 HashCode = GetTypeHash(T::StaticClass());

        if (!Instance->Services.Contains(HashCode))
        {
            UE_LOG(LogTemp, Warning, TEXT("Service not found: %s"), *T::StaticClass()->GetName());
            return;
        }

        Instance->Services.Remove(HashCode);
        UE_LOG(LogTemp, Warning, TEXT("Service unregistered: %s"), *T::StaticClass()->GetName());
    }

    static void UnregisterAllServices();

private:
    UPROPERTY()
    TMap<uint32, UObject*> Services;

    static UServiceLocatorSubsystem* GetInstance();
};
