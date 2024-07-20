// Game Programming Patterns, Eugene Esaulenko, 2024

#include "TestCharacter.h"

ATestCharacter::ATestCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterStateComponent"));
}

void ATestCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATestCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATestCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATestCharacter::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATestCharacter::StopJumping);
    PlayerInputComponent->BindAxis("Turn", this, &ATestCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter::LookUp);
}

void ATestCharacter::MoveForward(float X)
{
    const float Value = X * MoveSpeed;
    const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
    
    CharacterStateComponent->HandleMovementInput(Value);
}

void ATestCharacter::MoveRight(float Y)
{
    const float Value = Y * MoveSpeed;
    const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);

    CharacterStateComponent->HandleMovementInput(Value);
}

void ATestCharacter::Turn(float X)
{
    const float TurnAmount = X * RotationSpeed * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);
}

void ATestCharacter::LookUp(float Y)
{
    const float LookUpAmount = Y * RotationSpeed * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookUpAmount);
}

void ATestCharacter::Jump()
{
    Super::Jump();
    
    CharacterStateComponent->SetState(ETestCharacterState::Jump);
}

void ATestCharacter::SetState(ETestCharacterState TargetState) const
{
    CharacterStateComponent->SetState(TargetState);
}
