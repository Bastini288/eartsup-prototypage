// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Platform_Base.generated.h"

UCLASS()
class EARTSUP_B2_API APlatform_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatform_Base();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Platform;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool OnPlatform;
	ABaseCharacter* actorOnPlatform;
	
	UPROPERTY(EditDefaultsOnly, Category="Tilt")
	float MaxTiltAngle;
	
	UPROPERTY(EditDefaultsOnly, Category="Tilt")
	float MaxTiltDistance;
	
	UPROPERTY(EditDefaultsOnly, Category="Tilt")
	float TiltSpeed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
