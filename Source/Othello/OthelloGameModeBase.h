// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OthelloGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API AOthelloGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    /** Called when the game starts. */
    virtual void BeginPlay() override;

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION()
        void ServerChangeWidget();

    UFUNCTION()
        void ClientChangeWidget();

protected:

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu. */
    UPROPERTY()
        UUserWidget* CurrentWidget;

    UPROPERTY(BlueprintReadWrite)
        int32 MapSize;

    UPROPERTY(BlueprintReadWrite)
        int32 GameTimer;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
        TSubclassOf<UUserWidget> PlayGameWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
        TSubclassOf<UUserWidget> WaitGameWidgetClass;

    UPROPERTY()
        class AServerMenuController* ClientController;

    UPROPERTY()
        class AServerMenuController* ServerController;

    UPROPERTY()
        bool createServer;
};
