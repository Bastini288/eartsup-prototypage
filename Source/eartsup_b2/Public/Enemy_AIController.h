// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

UCLASS()
class EARTSUP_B2_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void QueueMoveRetry();

private:
	FTimerHandle MoveRetryTimerHandle;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MoveRetryDelay = 0.3f;

	
public:
	UFUNCTION(BlueprintCallable)
	void MoveToPlayer();
	
	
};
