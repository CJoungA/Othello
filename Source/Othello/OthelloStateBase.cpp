// Fill out your copyright notice in the Description page of Project Settings.


#include "OthelloStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "MainMenuWidget.h"
#include "ServerMenuController.h"

AOthelloStateBase::AOthelloStateBase() {
    bReplicates = true;
    MapSize = 6;
    GameTimer = 10;
    GameTimeCount = 10;
    Num = 0;
}

void AOthelloStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AOthelloStateBase, MapSize);
    DOREPLIFETIME(AOthelloStateBase, GameTimer);
    DOREPLIFETIME(AOthelloStateBase, GameTimeCount);
    DOREPLIFETIME(AOthelloStateBase, Num);

}

void AOthelloStateBase::SetMapSize(int32 size)
{
    OnMapSizeUpdate(size);
}

void AOthelloStateBase::OnMapSizeUpdate(int32 size)
{
    MapSize = size;
}

int32 AOthelloStateBase::GMBGetMapSize()
{
    return MapSize;
}

void AOthelloStateBase::OnRep_SetMapSize()
{
    OnMapSizeUpdate(MapSize);
}


void AOthelloStateBase::SetTimer(int32 size)
{
    OnSetTimerUpdate(size);
}

void AOthelloStateBase::OnSetTimerUpdate(int32 size)
{
    GameTimer = size;
}

int32 AOthelloStateBase::GMBGetTimer()
{
    return GameTimer;
}

void AOthelloStateBase::OnRep_SetTimer()
{
    OnSetTimerUpdate(GameTimer);
}

void AOthelloStateBase::OnSetTimeCount(int32 size)
{
    GameTimeCount = size;
}

int32 AOthelloStateBase::GMBGetTimeCount()
{
    return GameTimeCount;
}

void AOthelloStateBase::OnRep_SetTimeCount()
{
    OnSetTimeCount(GameTimeCount);
}

void AOthelloStateBase::OnSetNum(int32 value)
{
    Num = value;
}

int32 AOthelloStateBase::GMBGetNum()
{
    return Num;
}

void AOthelloStateBase::OnRep_SetNum()
{
    //Cast<AServerMenuController>(GetWorld()->GetFirstPlayerController())->SetPlayGameLogicClient();

    OnSetNum(Num);
}