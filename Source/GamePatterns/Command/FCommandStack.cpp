// Game Programming Patterns, Eugene Esaulenko, 2024

#include "FCommandStack.h"

FCommandStack::~FCommandStack()
{
    PendingCommands.Empty();
    ExecutedCommands.Empty();
}

void FCommandStack::AddCommand(UCommand* Command)
{
    if (Command != nullptr)
    {
        PendingCommands.Add(Command);
        UE_LOG(LogTemp, Warning, TEXT("Command added to the stack. Pending commands: %d"), PendingCommands.Num());
    }
}

void FCommandStack::ProcessCommands()
{
    while (PendingCommands.Num() > 0)
    {
        UCommand* Command = PendingCommands[0];
        if (Command != nullptr)
        {
            Command->Execute();
            ExecutedCommands.Add(Command);
            PendingCommands.RemoveAt(0);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("All pending commands have been executed. Executed commands: %d"), ExecutedCommands.Num());
}

void FCommandStack::UndoLastCommand()
{
    if (ExecutedCommands.IsEmpty())
    {
        return;
    }

    UCommand* LastCommand = ExecutedCommands.Last();
    if (LastCommand != nullptr)
    {
        LastCommand->Undo();
        ExecutedCommands.RemoveAt(ExecutedCommands.Num() - 1);
        UE_LOG(LogTemp, Warning, TEXT("Last command has been undone. Executed commands: %d"), ExecutedCommands.Num());
    }
}
