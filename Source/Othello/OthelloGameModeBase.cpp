// Copyright Epic Games, Inc. All Rights Reserved.

#include "OthelloGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "Kismet/GameplayStatics.h"
#include "ServerMenuController.h"


void AOthelloGameModeBase::PostLogin(APlayerController* NewPlayer) {
    Super::PostLogin(NewPlayer);

    //로그인 성공 이후 StartingWidgetClass불러오기

    if (!createServer)
        ServerController = Cast<AServerMenuController>(NewPlayer);

    if (ServerController && !createServer)
    {
        createServer = true;
        ServerController->ChangeMenuWidget(StartingWidgetClass);
    }

    if (createServer)
    {
        ClientController = Cast<AServerMenuController>(NewPlayer);

        if (ClientController)
            ClientController->ChangeMenuWidget(StartingWidgetClass);
    }
}

void AOthelloGameModeBase::ServerChangeWidget()
{
    ServerController->ChangeMenuWidget(PlayGameWidgetClass);
}

void AOthelloGameModeBase::ClientChangeWidget()
{
    ClientController->ChangeMenuWidget(PlayGameWidgetClass);
}

void AOthelloGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
}

