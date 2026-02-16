// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_AIController.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
	QueueMoveRetry();
}

void AEnemy_AIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	QueueMoveRetry();
}

void AEnemy_AIController::MoveToPlayer()
{
	if (AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		MoveToActor(PlayerActor);
	}

	QueueMoveRetry();
}

void AEnemy_AIController::QueueMoveRetry()
{
	if (UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		if (!TimerManager.IsTimerActive(MoveRetryTimerHandle))
		{
			TimerManager.SetTimer(
				MoveRetryTimerHandle,
				this,
				&AEnemy_AIController::MoveToPlayer,
				MoveRetryDelay,
				false);
		}
	}
}
