// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

UENUM(BlueprintType)
enum class ETestCharacterState : uint8
{
    Idle = 0,
    Move = 1,
    Jump = 2,
};