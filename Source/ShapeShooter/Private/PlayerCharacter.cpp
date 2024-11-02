// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Variables
	MaxHealth = 500.f;
	CurrentHealth = MaxHealth;
	bCanFire = true;
	FireCooldownTime = 0.05f;
	FRotator CameraRotation = FRotator(-90.f, 0.f, 0.f);

	// Set up camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 2500.0f;
	CameraBoom->SocketOffset.X = 2500.0f;
	CameraBoom->SocketOffset.Z = 2500.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeRotation(CameraRotation);
	FollowCamera->bUsePawnControlRotation = false;

	//Initialize the static mesh component
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);

	// Input actions and mapping context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> PlayerMappingContext(TEXT("/Game/Inputs/PlayerInputMapping"));
	if (PlayerMappingContext.Succeeded())
	{
		PlayerInputMappingContext = PlayerMappingContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveForwardActionObject(TEXT("/Game/Inputs/MoveForward"));
	if (MoveForwardActionObject.Succeeded())
	{
		MoveForwardAction = MoveForwardActionObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveRightActionObject(TEXT("/Game/Inputs/MoveRight"));
	if (MoveRightActionObject.Succeeded())
	{
		MoveRightAction = MoveRightActionObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> FireActionObject(TEXT("/Game/Inputs/Fire"));
	if (FireActionObject.Succeeded())
	{
		FireAction = FireActionObject.Object;
	}

	ScoreManagerComponent = CreateDefaultSubobject<UScoreManagerComponent>(TEXT("ScoreManagerComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputMappingContext, 0);
		}
	}

	// Add healthbar widget to viewport
	if (HealthWidgetClass)
	{
		HealthWidget = CreateWidget<UPlayerHealthWidget>(GetWorld(), HealthWidgetClass);
		if (HealthWidget)
		{
			HealthWidget->AddToViewport();
			UpdateHealthWidget();
		}
	}

	if (ScoreManagerComponent)
	{
		ScoreManagerComponent->LoadHighScores();
	}
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToMouseCursor();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Fire);
	}
}

// Move forward function definition
void APlayerCharacter::MoveForward(const FInputActionValue& Value) 
{
	if (Value.Get<float>() != 0.f)
	{
		AddMovementInput(FVector::ForwardVector, Value.Get<float>());
	}
}

// Move right function definition
void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	if (Value.Get<float>() != 0.f)
	{
		AddMovementInput(FVector::RightVector, Value.Get<float>());
	}
}

// Rotate to mouse cursor function definition
void APlayerCharacter::RotateToMouseCursor()
{
	// Get the player's viewport
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FVector MouseLocation, MouseDirection;
		PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		// Calculate the new rotation
		FRotator NewRotation = FRotator(0.f, MouseDirection.Rotation().Yaw, 0.f);
		SetActorRotation(NewRotation);
	}
}

// Fire input function definition
void APlayerCharacter::Fire(const FInputActionValue& Value)
{
	if (bCanFire)
	{
		FireProjectile();
		bCanFire = false;
		GetWorld()->GetTimerManager().SetTimer(FireCooldownTimerHandle, this, &APlayerCharacter::ResetFire, FireCooldownTime, false);
	}
}


// Fire projectile function definition
void APlayerCharacter::FireProjectile()
{
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation() + GetActorForwardVector() * 125.f;
			FRotator Rotation = GetActorRotation();

			World->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
		}
	}
}

// Reset can fire variable
void APlayerCharacter::ResetFire()
{
	bCanFire = true;
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UpdateHealthWidget();

	if (CurrentHealth <= 0)
	{
		HandleDeath();
	}

	return DamageAmount;
}

void APlayerCharacter::UpdateHealth(float DeltaHealth)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + DeltaHealth, 0.0f, MaxHealth);
	UpdateHealthWidget();

	if (CurrentHealth <= 0)
	{
		HandleDeath();
	}
}

void APlayerCharacter::UpdateHealthWidget()
{
	if (HealthWidget)
	{
		HealthWidget->UpdateHealthBar(CurrentHealth / MaxHealth);
	}
}

void APlayerCharacter::HandleDeath()
{
	Destroy();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player has died!"));
	}
}
