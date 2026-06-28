// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayGameWidget.generated.h"

/**
 *
 */
UCLASS()
class OTHELLO_API UPlayGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void GameLogic();

	UFUNCTION()
		void MakeMap();
	
	UFUNCTION()
		void ClickData();
	
	UFUNCTION()
		void OnClickDropStone();

	UFUNCTION()
		bool IsGetGameTurn();

	UFUNCTION()
		bool IsHostPlayer();

	UFUNCTION()
		bool IsMyTurn();

	UFUNCTION()
		void SetGameOverText(bool boolen);

	UFUNCTION()
		void StoneReverse();

	UFUNCTION()
		void SetMap();

	UFUNCTION()
		int32 GetMapSize();

	UFUNCTION()
		int32 GetTime();

	UFUNCTION()
		void GameSet();

	UFUNCTION()
		void ClearAvailableMoves();

	UFUNCTION()
		bool HasAnyValidMove(bool turn);

	UFUNCTION()
		bool IsBoardFull();

	UFUNCTION()
		void GameOverSet();

	UFUNCTION()
		bool IsCheckMakeMap(int x, int y, bool turn);

	UFUNCTION()
		int32 GetCountStone(int32 type);

	UFUNCTION()
		void UpdateTimeCount(int32 Count);

	UFUNCTION()
		int32 GetTimeCount();

	UFUNCTION()
		void UpdateTimerDisplay();

	UFUNCTION()
		void AdvanceTimer();

	UFUNCTION()
		void PlayGameLogic();

	UFUNCTION()
		void ApplyNetworkMove(int32 index);

/*	UFUNCTION()
		void TestWidget(int a, int b);*/

	UFUNCTION()
		void OnStoneClicked(int32 index);

	UFUNCTION()
		void UpdateNum(int32 value);

	UFUNCTION()
		int32 GetNum();

	FTimerHandle CountdownTimerHandle;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UButtonWidget> MapButtonWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UUniformGridPanel* MapGridPanel;

	UPROPERTY(EditAnywhere)
		class UImage* WhiteStone;

	UPROPERTY(EditAnywhere)
		class UImage* BlackStone;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* GameOverText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* WhiteStoneCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* BlackStoneCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TArray< UButtonWidget*> BtnArray;

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* StoneNumAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TurnTimeText;

	UPROPERTY()
		int32 BtnArrayIndex;

	UPROPERTY()
		int32 MapSize;

	UPROPERTY()
		bool GameTurn;

	UPROPERTY()
		int32 MapHalfSize;

	UPROPERTY()
		int32 CurrentIndex;

	UPROPERTY()
		int32 CountdownTime;

	UPROPERTY()
		int32 Num;
};
