// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"

template <typename T>
struct TFStateMachine
{
    static_assert(TIsEnum<T>::Value, "T must be an enum");

    TFStateMachine() = default;
    explicit TFStateMachine(T InitialState) : CurrentState(InitialState) {}

    ~TFStateMachine()
    {
        Transitions.Empty();
    }

    T GetCurrentState() const
    {
        return CurrentState;
    }

    void AddTransition(T From, T To, TFunction<void()> Transition)
    {
        for (const auto& Pair : Transitions)
        {
            if (Pair.Key.Key == From && Pair.Key.Value == To)
            {
                UE_LOG(LogTemp, Warning, TEXT("Transition from %s to %s already exists"), *UEnum::GetValueAsString(From), *UEnum::GetValueAsString(To));
                return;
            }
        }
        
        Transitions.Add(TPair<T, T>(From, To), Transition);
    }

    void SetState(T NewState)
    {
        if (CurrentState == NewState)
        {
            return;
        }

        for (const auto& Pair : Transitions)
        {
            if (Pair.Key.Key == CurrentState && Pair.Key.Value == NewState)
            {
                if (Pair.Value != nullptr)
                {
                    CurrentState = NewState;
                    Pair.Value();
                    return;
                }
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Transition from %s to %s not found"), *UEnum::GetValueAsString(CurrentState), *UEnum::GetValueAsString(NewState));
    }

private:
    T CurrentState;
    TMap<TPair<T, T>, TFunction<void()>> Transitions;
};
