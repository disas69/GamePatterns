// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GamePatternsTestCharacter.h"
#include "State/CharacterStateComponent.h"

AGamePatternsTestCharacter::AGamePatternsTestCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterStateComponent"));
}

void AGamePatternsTestCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AGamePatternsTestCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGamePatternsTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AGamePatternsTestCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AGamePatternsTestCharacter::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGamePatternsTestCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGamePatternsTestCharacter::StopJumping);
    PlayerInputComponent->BindAxis("Turn", this, &AGamePatternsTestCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AGamePatternsTestCharacter::LookUp);
}

void AGamePatternsTestCharacter::MoveForward(float X)
{
    const float Value = X * MoveSpeed;
    const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
    
    CharacterStateComponent->HandleMovementInput(Value);
}

void AGamePatternsTestCharacter::MoveRight(float Y)
{
    const float Value = Y * MoveSpeed;
    const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);

    CharacterStateComponent->HandleMovementInput(Value);
}

void AGamePatternsTestCharacter::Turn(float X)
{
    const float TurnAmount = X * RotationSpeed * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);
}

void AGamePatternsTestCharacter::LookUp(float Y)
{
    const float LookUpAmount = Y * RotationSpeed * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookUpAmount);
}

void AGamePatternsTestCharacter::Jump()
{
    Super::Jump();
    
    CharacterStateComponent->SetState(ETestCharacterState::Jump);
}

void AGamePatternsTestCharacter::SetState(ETestCharacterState TargetState) const
{
    CharacterStateComponent->SetState(TargetState);
}
