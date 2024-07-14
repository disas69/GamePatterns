// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterMoveState.h"

void UCharacterMoveState::OnEnter()
{
    Super::OnEnter();

    UE_LOG(LogTemp, Warning, TEXT("MoveState: OnEnter"));
}

void UCharacterMoveState::OnExit()
{
    Super::OnExit();

    UE_LOG(LogTemp, Warning, TEXT("MoveState: OnExit"));
}

void UCharacterMoveState::Update(float DeltaTime)
{
    Super::Update(DeltaTime);
}