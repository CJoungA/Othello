// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ServerMenuController.h"
#include "OthelloStateBase.h"
#include "OthelloGameModeBase.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayGameText->SetText(FText::FromString(TEXT("PlayGame")));
	QuitGameText->SetText(FText::FromString(TEXT("Quit")));

	GetMapSizeText->SetText(FText::FromString(TEXT("Input map size")));
	TurnTimeGetText->SetText(FText::FromString(TEXT("Input turn time")));

	PlayGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGameButtonClicked);
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitButtonClicked);
}

bool UMainMenuWidget::Initialize() {
	Super::Initialize();

	PlayGameButton->bIsEnabledDelegate.BindUFunction(this, "IsGetPlayGameButtonEnabled");

	return true;
}

void UMainMenuWidget::PlayGameButtonClicked()
{
	Cast<AOthelloStateBase>(GetWorld()->GetGameState())->SetMapSize(GetTextMapSize());

	Cast<AOthelloStateBase>(GetWorld()->GetGameState())->SetTimer(GetTextTimer());

	Cast<AServerMenuController>(UGameplayStatics::GetPlayerController(GetWorld(),0))->ChangeMenuWidget(PlayGameWidgetClass);
	//Cast<AOthelloGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ServerChangeWidget();

	Cast<AOthelloGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ClientChangeWidget(); //클라이언트
}

void UMainMenuWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

int32 UMainMenuWidget::GetTextMapSize()
{
	return FCString::Atoi(*GetMapSizeTextBox->GetText().ToString());
}

int32 UMainMenuWidget::GetTextTimer()
{
	return FCString::Atoi(*TimerGetTextBox->GetText().ToString());
}

bool UMainMenuWidget::IsGetPlayGameButtonEnabled() {
	if (GetMapSizeTextBox->GetText().ToString().Len() <= 0)
		return false;
	if (TimerGetTextBox->GetText().ToString().Len() <= 0)
		return false;

	return true;
}

bool UMainMenuWidget::IsCheckMakeBoard(FString Name) {//숫자만 
	const FRegexPattern pattern(TEXT("^[0-9]$"));

	FRegexMatcher matcher(pattern, Name);

	if (matcher.FindNext()) {
		return true;
	}
	return false;
}