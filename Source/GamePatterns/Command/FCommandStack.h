// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "FCommandStack.generated.h"

USTRUCT(BlueprintType)
struct FCommandStack
{
    GENERATED_USTRUCT_BODY()

    FCommandStack() = default;
    ~FCommandStack();

    int32 GetPendingCommandsNum() const { return PendingCommands.Num(); }
    int32 GetExecutedCommandsNum() const { return ExecutedCommands.Num(); }

    void AddCommand(UCommand* Command);
    void ProcessCommands();
    void UndoLastCommand();

private:
    UPROPERTY()
    TArray<UCommand*> PendingCommands;

    UPROPERTY()
    TArray<UCommand*> ExecutedCommands;
};
