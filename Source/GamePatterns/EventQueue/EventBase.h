// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EventBase.generated.h"

UCLASS()
class GAMEPATTERNS_API UEventBase : public UObject
{
    GENERATED_BODY()

public:
    virtual void Process() {}
};
