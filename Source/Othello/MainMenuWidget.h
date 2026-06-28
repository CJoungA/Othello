// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	bool Initialize();

	UFUNCTION()
		void PlayGameButtonClicked();

	UFUNCTION()
		void QuitButtonClicked();

	UFUNCTION()
		int32 GetTextMapSize();

	UFUNCTION()
		int32 GetTextTimer();

	UFUNCTION()
		bool IsGetPlayGameButtonEnabled();

	UFUNCTION()
		bool IsCheckMakeBoard(FString Name);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* PlayGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* GetMapSizeTextBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* TimerGetTextBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PlayGameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* QuitGameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* GetMapSizeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TurnTimeGetText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> PlayGameWidgetClass;

};
