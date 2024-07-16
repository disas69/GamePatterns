// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "State/TestCharacterState.h"
#include "GamePatternsTestCharacter.generated.h"

class UCharacterStateComponent;

UCLASS()
class GAMEPATTERNS_API AGamePatternsTestCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AGamePatternsTestCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    UCharacterStateComponent* CharacterStateComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement")
    float MoveSpeed = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement")
    float RotationSpeed = 100.0f;

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float X);
    void MoveRight(float Y);
    void Turn(float X);
    void LookUp(float Y);
    virtual void Jump() override;

    void SetState(ETestCharacterState TargetState) const;

protected:
    virtual void BeginPlay() override;
};
