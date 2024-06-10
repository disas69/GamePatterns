// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Command.generated.h"

UCLASS()
class UCommand : public UObject
{
    GENERATED_BODY()

public:
    virtual void Execute();
    virtual void Undo();
};
