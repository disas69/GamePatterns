// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "CharacterStateBase.h"
#include "UObject/Object.h"
#include "CharacterJumpState.generated.h"

UCLASS()
class GAMEPATTERNS_API UCharacterJumpState : public UCharacterStateBase
{
    GENERATED_BODY()

public:
    virtual void OnEnter() override;
    virtual void OnExit() override;
    virtual void Update(float DeltaTime) override;
};
