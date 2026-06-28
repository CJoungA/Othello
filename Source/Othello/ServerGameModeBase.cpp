// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ServerMenuController.h"
#include "Kismet/GameplayStatics.h"

void AServerGameModeBase::PostLogin(APlayerController* NewPlayer) {
    Super::PostLogin(NewPlayer);

    auto PlayerController = Cast<AServerMenuController>(NewPlayer);
    PlayerController->ChangeMenuWidget(StartingWidgetClass);
}

void AServerGameModeBase::BeginPlay()
{
    Super::BeginPlay();

}