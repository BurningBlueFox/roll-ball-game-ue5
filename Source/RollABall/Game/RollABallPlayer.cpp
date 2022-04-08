// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollABallPlayer::ARollABallPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	//Set up physics
	Mesh->SetSimulatePhysics(true);

	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Mesh->OnComponentHit.AddDynamic(this, &ARollABallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Bindings
	InputComponent->BindAxis("MoveForward", this, &ARollABallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollABallPlayer::MoveRight);
	//Custom Action Binding
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollABallPlayer::Jump);
}

void ARollABallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollABallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollABallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount) return;

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount++;
}

void ARollABallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	if (const float HitDirection = Hit.Normal.Z; HitDirection > 0)
		JumpCount = 0;
}
