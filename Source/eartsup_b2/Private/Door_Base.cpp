// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_Base.h"


// Sets default values
ADoor_Base::ADoor_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	RootComponent = Door;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor_Base::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ADoor_Base::OnOverlapBegin);
	
}

void ADoor_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	couille();
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"OUAIII");
}

// Called every frame
void ADoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

