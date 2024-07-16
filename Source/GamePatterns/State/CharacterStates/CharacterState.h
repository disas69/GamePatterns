// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GamePatterns/State/State.h"
#include "UObject/Object.h"
#include "CharacterState.generated.h"

UCLASS()
class GAMEPATTERNS_API UCharacterState : public UState
{
    GENERATED_BODY()

public:
    UCharacterState() = default;
    
    virtual void Initialize(ACharacter* Owner);

    template <typename T>
    static T* Create(UObject* Outer, ACharacter* Owner)
    {
        T* State = NewObject<T>(Outer);
        State->Initialize(Owner);
        return State;
    }

protected:
    UPROPERTY()
    ACharacter* OwnerCharacter = nullptr;
};
