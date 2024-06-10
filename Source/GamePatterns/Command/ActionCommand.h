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
    
    virtual void Initialize(const TFunction<void()>& InExecute, const TFunction<void()>& InUndo);
    virtual void Execute() override;
    virtual void Undo() override;

private:
    TFunction<void()> ExecuteFunc;
    TFunction<void()> UndoFunc;
};
