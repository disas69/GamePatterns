// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterStateComponent.h"
#include "CharacterStates/CharacterIdleState.h"
#include "CharacterStates/CharacterJumpState.h"
#include "CharacterStates/CharacterMoveState.h"

UCharacterStateComponent::UCharacterStateComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    Controller = TStateController<ETestCharacterState>();
}

void UCharacterStateComponent::SetState(ETestCharacterState State)
{
    Controller.SetState(State);
}

ETestCharacterState UCharacterStateComponent::GetState() const
{
    return Controller.GetCurrentStateType();
}

void UCharacterStateComponent::BeginPlay()
{
    Super::BeginPlay();

    AddState(ETestCharacterState::Idle, UCharacterStateBase::Create<UCharacterIdleState>(this, GetOwner()));
    AddState(ETestCharacterState::Move, UCharacterStateBase::Create<UCharacterMoveState>(this, GetOwner()));
    AddState(ETestCharacterState::Jump, UCharacterStateBase::Create<UCharacterJumpState>(this, GetOwner()));

    SetState(ETestCharacterState::Idle);
}

void UCharacterStateComponent::AddState(ETestCharacterState StateType, UCharacterStateBase* State)
{
    Controller.AddState(StateType, State);
    States.Add(State);
}

void UCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Controller.Update(DeltaTime);
}
