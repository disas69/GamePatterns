// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include "FEventQueue.generated.h"

USTRUCT(BlueprintType)
struct FEventQueue
{
    GENERATED_USTRUCT_BODY()

    void AddEvent(UEventBase* Event);
    void ProcessEvents();

private:
    UPROPERTY()
    TArray<UEventBase*> Events;
};
