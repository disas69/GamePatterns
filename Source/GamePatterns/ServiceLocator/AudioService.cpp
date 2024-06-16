// Game Programming Patterns, Eugene Esaulenko, 2024

#include "AudioService.h"
#include "Kismet/GameplayStatics.h"

void UAudioService::PlayAudio(USoundBase* Sound) const
{
    if (Sound != nullptr)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), Sound);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sound is null"));
    }
}