// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterJumpState.h"

void UCharacterJumpState::OnEnter()
{
    Super::OnEnter();

    UE_LOG(LogTemp, Warning, TEXT("JumpState: OnEnter"));
}

void UCharacterJumpState::OnExit()
{
    Super::OnExit();

    UE_LOG(LogTemp, Warning, TEXT("JumpState: OnExit"));
}

void UCharacterJumpState::Update(float DeltaTime)
{
    Super::Update(DeltaTime);
}