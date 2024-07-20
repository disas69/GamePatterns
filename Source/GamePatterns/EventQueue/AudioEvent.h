// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include "UObject/Object.h"
#include "AudioEvent.generated.h"

UCLASS()
class GAMEPATTERNS_API UAudioEvent : public UEventBase
{
    GENERATED_BODY()

public:
    UAudioEvent() : SoundID(0) {}

    static UAudioEvent* Create(int32 InSoundID)
    {
        UAudioEvent* Event = NewObject<UAudioEvent>();
        Event->Initialize(InSoundID);
        return Event;
    }
    
    void Initialize(int32 InSoundID);
    virtual void Process() override;

private:
    int32 SoundID;
};
