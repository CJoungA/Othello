// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ServerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API AServerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void InitGame();

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
};
