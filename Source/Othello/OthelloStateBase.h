// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OthelloStateBase.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API AOthelloStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
    AOthelloStateBase();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    UFUNCTION()
        void SetMapSize(int32 size);

    UFUNCTION()
        void OnMapSizeUpdate(int32 size);

    UFUNCTION()
        int32 GMBGetMapSize();

    UFUNCTION()
        void OnRep_SetMapSize();


    UFUNCTION()
        void SetTimer(int32 size);

    UFUNCTION()
        void OnSetTimerUpdate(int32 size);

    UFUNCTION()
        int32 GMBGetTimer();

    UFUNCTION()
        void OnRep_SetTimer();


    UFUNCTION()
        void OnSetTimeCount(int32 size);

    UFUNCTION()
        int32 GMBGetTimeCount();

    UFUNCTION()
        void OnRep_SetTimeCount();


    UFUNCTION()
        void OnSetNum(int32 value);

    UFUNCTION()
        int32 GMBGetNum();

    UFUNCTION()
        void OnRep_SetNum();


protected:
    UPROPERTY(ReplicatedUsing = OnRep_SetMapSize)
        int32 MapSize;

    UPROPERTY(ReplicatedUsing = OnRep_SetTimer)
        int32 GameTimer;

    UPROPERTY(ReplicatedUsing = OnRep_SetTimeCount)
        int32 GameTimeCount;

    UPROPERTY(ReplicatedUsing = OnRep_SetNum)
        int32 Num;
};
