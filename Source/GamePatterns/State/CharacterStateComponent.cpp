// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterStateComponent.h"
#include "CharacterStates/CharacterIdleState.h"
#include "CharacterStates/CharacterJumpState.h"
#include "CharacterStates/CharacterMoveState.h"
#include "GameFramework/Character.h"

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

    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (Owner != nullptr)
    {
        AddState(ETestCharacterState::Idle, UCharacterState::Create<UCharacterIdleState>(this, Owner));
        AddState(ETestCharacterState::Move, UCharacterState::Create<UCharacterMoveState>(this, Owner));
        AddState(ETestCharacterState::Jump, UCharacterState::Create<UCharacterJumpState>(this, Owner));

        SetState(ETestCharacterState::Idle);
    }
}

void UCharacterStateComponent::AddState(ETestCharacterState StateType, UCharacterState* State)
{
    Controller.AddState(StateType, State);
    States.Add(State);
}

void UCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Controller.Update(DeltaTime);
}
