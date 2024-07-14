// Game Programming Patterns, Eugene Esaulenko, 2024

#include "CharacterStateBase.h"

void UCharacterStateBase::Initialize(AActor* Owner)
{
    OwnerCharacter = Owner;
}