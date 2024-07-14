// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "State.h"

template <typename T>
struct TStateController
{
    static_assert(TIsEnum<T>::Value, "T must be an enum");

    TStateController() = default;

    void AddState(T StateType, UState* State)
    {
        States.Add(StateType, State);
    }

    T GetCurrentStateType() const
    {
        return CurrentStateType;
    }

    void SetState(T NewStateType)
    {
        if (CurrentStateType == NewStateType)
        {
            return;
        }

        UState* CurrentState = GetState(CurrentStateType);
        if (CurrentState != nullptr)
        {
            CurrentState->OnExit();
        }
        
        CurrentStateType = NewStateType;

        UState* NewState = GetState(NewStateType);
        if (NewState != nullptr)
        {
            NewState->OnEnter();
        }
    }

    void Update(float DeltaTime)
    {
        UState* CurrentState = GetState(CurrentStateType);
        if (CurrentState != nullptr)
        {
            CurrentState->Update(DeltaTime);
        }
    }

private:
    T CurrentStateType;
    TMap<T, UState*> States;

    UState* GetState(T StateType)
    {
        auto State = States.Find(StateType);
        if (State != nullptr)
        {
            return *State;
        }
        
        UE_LOG(LogTemp, Warning, TEXT("State %s not found"), *UEnum::GetValueAsString(StateType));
        return nullptr;
    }
};
