// Game Programming Patterns, Eugene Esaulenko, 2024

#include "FEventQueue.h"

void FEventQueue::AddEvent(UEventBase* Event)
{
    if (Event != nullptr)
    {
        Events.Push(Event);
    }
}

void FEventQueue::ProcessEvents()
{
    while (!Events.IsEmpty())
    {
        UEventBase* Event = Events[0];
        Events.RemoveAt(0);

        if (Event != nullptr)
        {
            Event->Process();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to precess Event Queue: Event is nullptr"));
        }
    }
}