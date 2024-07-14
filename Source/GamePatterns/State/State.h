// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "State.generated.h"

UCLASS()
class GAMEPATTERNS_API UState : public UObject
{
    GENERATED_BODY()

public:
    UState() = default;

    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float DeltaTime);
};
