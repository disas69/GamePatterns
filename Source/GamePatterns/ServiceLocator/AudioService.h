// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AudioService.generated.h"

UCLASS()
class GAMEPATTERNS_API UAudioService : public UObject
{
    GENERATED_BODY()

public:
    void PlayAudio(USoundBase* Sound) const;
};
