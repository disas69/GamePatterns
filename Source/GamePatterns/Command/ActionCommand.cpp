// Game Programming Patterns, Eugene Esaulenko, 2024

#include "ActionCommand.h"

void UActionCommand::Initialize(const TFunction<void()>& InExecute, const TFunction<void()>& InUndo)
{
    ExecuteFunc = InExecute;
    UndoFunc = InUndo;
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