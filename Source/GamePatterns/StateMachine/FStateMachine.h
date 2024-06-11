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
        Transitions.FindOrAdd(From).Add(To, Transition);
    }

    void SetState(T NewState)
    {
        if (CurrentState == NewState)
        {
            return;
        }

        auto MapFrom = Transitions.Find(CurrentState);
        if (MapFrom != nullptr)
        {
            auto Transition = MapFrom->Find(NewState);
            if (Transition != nullptr)
            {
                CurrentState = NewState;
                (*Transition)();
                return;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Transition from %s to %s not found"), *UEnum::GetValueAsString(CurrentState), *UEnum::GetValueAsString(NewState));
    }

private:
    T CurrentState;
    TMap<T, TMap<T, TFunction<void()>>> Transitions;
};
