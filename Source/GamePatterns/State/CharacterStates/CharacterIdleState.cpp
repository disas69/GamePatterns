// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterIdleState.h"

void UCharacterIdleState::OnEnter()
{
    Super::OnEnter();

    UE_LOG(LogTemp, Warning, TEXT("IdleState: OnEnter"));
}

void UCharacterIdleState::OnExit()
{
    Super::OnExit();

    UE_LOG(LogTemp, Warning, TEXT("IdleState: OnExit"));
}

void UCharacterIdleState::Update(float DeltaTime)
{
    Super::Update(DeltaTime);
}