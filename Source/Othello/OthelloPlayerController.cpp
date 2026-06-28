// Fill out your copyright notice in the Description page of Project Settings.


#include "OthelloPlayerController.h"

void AOthelloPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}

