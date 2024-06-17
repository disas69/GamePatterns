// Game Programming Patterns, Eugene Esaulenko, 2024

#include "AudioEvent.h"

void UAudioEvent::Initialize(int32 InSoundID)
{
    SoundID = InSoundID;
}

void UAudioEvent::Process()
{
    Super::Process();
    UE_LOG(LogTemp, Warning, TEXT("Playing sound with ID: %d"), SoundID);
}