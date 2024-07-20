// Game Programming Patterns, Eugene Esaulenko, 2024

#include "ActionCommand.h"

void UActionCommand::Initialize(TFunction<void()> OnExecute, TFunction<void()> OnUndo)
{
    ExecuteFunc = OnExecute;
    UndoFunc = OnUndo;
}

void UActionCommand::Execute()
{
    Super::Execute();

    if (ExecuteFunc != nullptr)
    {
        ExecuteFunc();
    }
}

void UActionCommand::Undo()
{
    Super::Undo();

    if (UndoFunc != nullptr)
    {
        UndoFunc();
    }
}