# Unreal Game Programming Patterns

A collection of the most common game programming patterns adapted for Unreal Engine.

- Command
```
  FCommandStack CommandStack;

  // Create action commands
  UActionCommand* MoveCommand = UActionCommand::Create([this]()
  {
      UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Execute"));
  }, [this]()
  {
      UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Undo"));
  });

  UActionCommand* JumpCommand = UActionCommand::Create([this]()
  {
      UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Execute"));
  }, [this]()
  {
      UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Undo"));
  });

  // Add 2 commands to the stack
  CommandStack.AddCommand(MoveCommand);
  CommandStack.AddCommand(JumpCommand);

  // Process commands
  CommandStack.ProcessCommands();

  // Undo all commands
  while (CommandStack.GetExecutedCommandsNum() > 0)
  {
      CommandStack.UndoLastCommand();
  }
```
- Object Pool
```
  // Create actor pool
  UActorPool* ActorPool = UActorPool::CreatePool(this, ActorPoolParams);
  
  // Get an object from the pool
  APooledActor* Actor = ActorPool->GetActor();
  
  // Return the object to the pool
  Actor->Return();
```
- Singleton
```
  // UGameStateSubsystem is a singleton based on UGameInstanceSubsystem
  UGameStateSubsystem::GetInstance()->SetState(ETestGameState::MainMenu);
  UGameStateSubsystem::GetInstance()->SetState(ETestGameState::InGame);
  UGameStateSubsystem::GetInstance()->SetState(ETestGameState::GameOver);
```
- ServiceLocator
```
  // Register new audio service instance
  UServiceLocatorSubsystem::RegisterService<UAudioService>(NewObject<UAudioService>());

  // Resolve audio service instance and play audio
  AudioService = UServiceLocatorSubsystem::ResolveService<UAudioService>();
  if (AudioService != nullptr)
  {
      AudioService->PlayAudio(nullptr);
  }

  // Unregister audio service instance
  UServiceLocatorSubsystem::UnregisterService<UAudioService>();
```
- State
```
  // Create a new state controller and add all the states
  TStateController<ETestCharacterState> Controller = TStateController<ETestCharacterState>();
  Controller.AddState(ETestCharacterState::Idle, UCharacterState::Create<UCharacterIdleState>(this, Owner));
  Controller.AddState(ETestCharacterState::Move, UCharacterState::Create<UCharacterMoveState>(this, Owner));
  Controller.AddState(ETestCharacterState::Jump, UCharacterState::Create<UCharacterJumpState>(this, Owner));

  // Set the initial state
  Controller.SetState(CharacterState::Idle);

  // Update the current state
  Controller.Update(DeltaTime);
```
- State Machine
```
  // Create a state machine
  TStateMachine<ETestGameState> GameStateMachine;
  
  // Add transitions
  GameStateMachine.AddTransition(ETestGameState::None, ETestGameState::MainMenu, [this]() { UE_LOG(LogTemp, Warning, TEXT("Opening menu")); });
  GameStateMachine.AddTransition(ETestGameState::MainMenu, ETestGameState::InGame, [this]() { UE_LOG(LogTemp, Warning, TEXT("Starting game")); });
  GameStateMachine.AddTransition(ETestGameState::InGame, ETestGameState::GameOver, [this]() { UE_LOG(LogTemp, Warning, TEXT("Ending game")); });
  
  // Set target state
  GameStateMachine.SetState(ETestGameState);
```
