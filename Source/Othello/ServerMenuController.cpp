// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Blueprint/UserWidget.h>
#include "PlayGameWidget.h"
#include "ButtonWidget.h"
#include "OthelloStateBase.h"

void AServerMenuController::BeginPlay()
{
    Super::BeginPlay();
    
    SetShowMouseCursor(true);
    SetInputMode(FInputModeGameAndUI());
}


void AServerMenuController::HostServer()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("GameMap"), true, ((FString)(L"Listen")));
    //ChangeMenuWidget(대기화면);

}

void AServerMenuController::JoinServer(FString IpAddress)
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(IpAddress), true); // Level 이름 대신 IP 주소.
}

void AServerMenuController::ChangeMenuWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void AServerMenuController::SetPlayGameLogic()
{
    SetPlayGameLogicServer();
}

void AServerMenuController::SetPlayGameLogicServer_Implementation()
{
    //Cast<AServerMenuController>(GetWorld()->GetFirstPlayerController())->SetPlayGameLogicClient();

    for (auto Iter = GetWorld()->GetControllerIterator(); Iter; ++Iter) {
        if (AServerMenuController* Controller = Cast<AServerMenuController>(Iter->Get()))
        {
            Controller->SetPlayGameLogicClient();
        }
    }
}

void AServerMenuController::SetPlayGameLogicClient_Implementation()
{
    class UPlayGameWidget* PlayWidget = Cast<UPlayGameWidget>(CurrentWidget);

    if (PlayWidget)
    {
        PlayWidget->GameLogic();
    }
}


void AServerMenuController::WTest(int a, int b)
{
    WTestServer(a,b);
}

void AServerMenuController::WTestServer_Implementation(int a, int b)
{
    for (auto Iter = GetWorld()->GetControllerIterator(); Iter; ++Iter) {
        if (AServerMenuController* Controller = Cast<AServerMenuController>(Iter->Get()))
        {
            Controller->WTestClient(a,b);
        }
    }
}

void AServerMenuController::WTestClient_Implementation(int a, int b)
{
    class UPlayGameWidget* PlayWidget = Cast<UPlayGameWidget>(CurrentWidget);
    if (PlayWidget)
    {
        PlayWidget->ClickData();
    }
}

void AServerMenuController::BTest(int32 index)
{
    BTestServer(index);
}

void AServerMenuController::BTestServer_Implementation(int32 index)
{
        //플레이어가 둔 칸 번호를 모든 플레이어 컨트롤러에 보내기
    for (auto Iter = GetWorld()->GetControllerIterator(); Iter; ++Iter)
    {
        if (AServerMenuController* Controller = Cast<AServerMenuController>(Iter->Get()))
        {
            Controller->BTestClient(index);
        }
    }
}

void AServerMenuController::BTestClient_Implementation(int32 index)
{
        //각 클라이언트가 받은 칸 번호로 자신의 보드 위젯을 갱신
    class UPlayGameWidget* PlayWidget = Cast<UPlayGameWidget>(CurrentWidget);
    if (PlayWidget)
    {
        PlayWidget->ApplyNetworkMove(index);
    }
}


//현재 위젯
UUserWidget* AServerMenuController::GetWidget()
{
    return CurrentWidget;
}

