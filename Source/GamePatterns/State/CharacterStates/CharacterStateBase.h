// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GamePatterns/State/State.h"
#include "UObject/Object.h"
#include "CharacterStateBase.generated.h"

UCLASS()
class GAMEPATTERNS_API UCharacterStateBase : public UState
{
    GENERATED_BODY()

public:
    UCharacterStateBase() = default;
    
    virtual void Initialize(AActor* Owner);

    template <typename T>
    static T* Create(UObject* Outer, AActor* Owner)
    {
        T* State = NewObject<T>(Outer);
        State->Initialize(Owner);
        return State;
    }

private:
    UPROPERTY()
    AActor* OwnerCharacter = nullptr;
};
