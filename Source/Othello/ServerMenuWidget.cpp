// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMenuWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ServerMenuController.h"

void UServerMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HostGameButton->OnClicked.AddDynamic(this, &UServerMenuWidget::HostServerHandler);
	JoinGameButton->OnClicked.AddDynamic(this, &UServerMenuWidget::JoinServerHandler);
	QuitGameButton->OnClicked.AddDynamic(this, &UServerMenuWidget::QuitButtonClicked);

}

void UServerMenuWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UServerMenuWidget::HostServerHandler()
{
	AServerMenuController* ServerMenuPC = Cast<AServerMenuController>(GetOwningPlayer());
	if (ServerMenuPC)
	{
		ServerMenuPC->HostServer();
	}
}

void UServerMenuWidget::JoinServerHandler()
{
	AServerMenuController* ServerMenuPC = Cast<AServerMenuController>(GetOwningPlayer());
	if (ServerMenuPC)
	{
		ServerMenuPC->JoinServer(GetIpAddress());
	}
}

FString UServerMenuWidget::GetIpAddress()
{
	return *IpAddressText->GetText().ToString();
}

