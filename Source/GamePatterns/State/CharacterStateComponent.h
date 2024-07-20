// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "StateController.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"

class UCharacterState;

UENUM(BlueprintType)
enum class ETestCharacterState : uint8
{
    Idle = 0,
    Move = 1,
    Jump = 2,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEPATTERNS_API UCharacterStateComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterStateComponent();

    UFUNCTION(BlueprintCallable, Category = "Character State")
    void SetState(ETestCharacterState State);

    UFUNCTION(BlueprintCallable, Category = "Character State")
    ETestCharacterState GetState() const;

    UFUNCTION(BlueprintCallable, Category = "Character State")
    void HandleMovementInput(float Value);

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void BeginPlay() override;

private:
    TStateController<ETestCharacterState> Controller;

    // UPROPERTY container to ensure that the states UObjects are not garbage collected
    UPROPERTY()
    TArray<UCharacterState*> States;

    void AddState(ETestCharacterState StateType, UCharacterState* State);
};
