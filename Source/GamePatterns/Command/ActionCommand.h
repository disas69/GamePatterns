// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "ActionCommand.generated.h"

UCLASS()
class GAMEPATTERNS_API UActionCommand : public UCommand
{
    GENERATED_BODY()

public:
    UActionCommand() : ExecuteFunc(nullptr), UndoFunc(nullptr) {}

    static UActionCommand* Create(TFunction<void()> OnExecute, TFunction<void()> OnUndo)
    {
        UActionCommand* Command = NewObject<UActionCommand>();
        Command->Initialize(OnExecute, OnUndo);
        return Command;
    }
    
    virtual void Initialize(TFunction<void()> OnExecute, TFunction<void()> OnUndo);
    virtual void Execute() override;
    virtual void Undo() override;

private:
    TFunction<void()> ExecuteFunc;
    TFunction<void()> UndoFunc;
};
