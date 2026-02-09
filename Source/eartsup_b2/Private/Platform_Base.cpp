// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform_Base.h"

#include "BaseCharacter.h"


// Sets default values
APlatform_Base::APlatform_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	RootComponent = Platform;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
	MaxTiltAngle = 15.0f;
	MaxTiltDistance = 200.0f;
	TiltSpeed = 4.0f;
}

// Called when the game starts or when spawned
void APlatform_Base::BeginPlay()
{
	Super::BeginPlay();
	OnPlatform = false;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APlatform_Base::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &APlatform_Base::OnOverlapEnd);
	
}

void APlatform_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// On tente de transformer OtherActor en ton type de personnage
		ABaseCharacter* MyPlayer = Cast<ABaseCharacter>(OtherActor);

		if (MyPlayer)
		{
			OnPlatform = true;
			actorOnPlatform = MyPlayer;
		}
	}
	
}

void APlatform_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor == actorOnPlatform)
	{
		OnPlatform = false;
		actorOnPlatform = nullptr;
	}
}

// Called every frame
void APlatform_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (OnPlatform && actorOnPlatform)
	{
		const FVector ActorLocation = GetActorLocation();
		const FVector PlayerLocation = actorOnPlatform->GetActorLocation();
		const FVector ToPlayer = PlayerLocation - ActorLocation;
		const float SideDot = FVector::DotProduct(GetActorRightVector(), ToPlayer);
		const float ForwardDot = FVector::DotProduct(GetActorForwardVector(), ToPlayer);
		const float NormalizedSide = FMath::Clamp(SideDot / MaxTiltDistance, -1.0f, 1.0f);
		const float NormalizedForward = FMath::Clamp(ForwardDot / MaxTiltDistance, -1.0f, 1.0f);
		const float TargetRoll = NormalizedSide * MaxTiltAngle;
		const float TargetPitch = -NormalizedForward * MaxTiltAngle;
		const FRotator CurrentRotation = GetActorRotation();
		const float NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, TargetPitch, DeltaTime, TiltSpeed);
		const float NewRoll = FMath::FInterpTo(CurrentRotation.Roll, TargetRoll, DeltaTime, TiltSpeed);
		SetActorRotation(FRotator(NewPitch, CurrentRotation.Yaw, NewRoll));
	}
	else
	{
		const FRotator CurrentRotation = GetActorRotation();
		const float NewPitch = FMath::FInterpTo(CurrentRotation.Pitch, 0.0f, DeltaTime, TiltSpeed);
		const float NewRoll = FMath::FInterpTo(CurrentRotation.Roll, 0.0f, DeltaTime, TiltSpeed);
		SetActorRotation(FRotator(NewPitch, CurrentRotation.Yaw, NewRoll));
	}
}

