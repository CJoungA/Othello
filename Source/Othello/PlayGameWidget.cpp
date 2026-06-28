// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Types/SlateEnums.h"
#include "ButtonWidget.h"
#include "MainMenuWidget.h"
#include "OthelloStateBase.h"
#include "Animation/WidgetAnimation.h"
#include "ServerMenuController.h"


void UPlayGameWidget::NativeConstruct() {
	Super::NativeConstruct();

	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			MapSize = GetMapSize();
			MapHalfSize = MapSize / 2 - 1;

			BtnArrayIndex = 0;

			GameTurn = false;

			SetGameOverText(false);

			//Num = GetNum();

			CountdownTime = GetTime();
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UPlayGameWidget::AdvanceTimer, 1.0f, true);
			UpdateTimerDisplay();

			MakeMap();
			SetMap();
			GameSet();
		}), 0.2f, false);
}

void UPlayGameWidget::MakeMap() {
	if (MapButtonWidget)
	{
		UUniformGridSlot* MapGridSlot;

		for (int32 j = 0; j < MapSize; j++)
		{
			for (int32 i = 0; i < MapSize; i++) {

				BtnArrayIndex = i + j * MapSize;

				UUserWidget* widget = CreateWidget(this, MapButtonWidget);
				MapGridSlot = MapGridPanel->AddChildToUniformGrid(widget, j, i);
				MapGridSlot->SetHorizontalAlignment(HAlign_Fill);
				MapGridSlot->SetVerticalAlignment(VAlign_Fill);

				UButtonWidget* button = Cast<UButtonWidget>(widget);
				button->GetMapButton()->OnClicked.AddDynamic(this, &UPlayGameWidget::PlayGameLogic);
				button->SetData(BtnArrayIndex);
				button->SetVisibility(ESlateVisibility::HitTestInvisible);
				BtnArray.Add(button);
			}
		}
	}
}

void UPlayGameWidget::GameLogic() {
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			ClickData();

			OnClickDropStone();

			CountdownTime = GetTime();

			StoneReverse();

			GameSet();

			PlayAnimation(StoneNumAnimation);

			GameOverSet();
		}), 0.2f, false);
}

void UPlayGameWidget::ClickData() {

	for (int32 j = 0; j < MapSize; j++)
	{
		for (int32 i = 0; i < MapSize; i++) {

			BtnArrayIndex = i + j * MapSize;

			if (BtnArray[BtnArrayIndex]->GetClickData() == true) {
				//UpdateNum(BtnArrayIndex);
				OnStoneClicked(BtnArrayIndex);
				Num = GetNum();
				BtnArray[Num]->IsSetClickData(true);
				BtnArray[Num]->IsSetSelectData(true);

				return;
			}
		}
	}
}

void UPlayGameWidget::OnClickDropStone() //돌 놓기
{
	Num = GetNum();
	if (BtnArray[Num]->GetClickData() == true) {
		CurrentIndex = BtnArray[Num]->GetData();
		if (GameTurn == false)BtnArray[Num]->OnBtnClickWhite();
		if (GameTurn == true)BtnArray[Num]->OnBtnClickBlack();
		BtnArray[Num]->IsSetClickData(false);
		BtnArray[Num]->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UPlayGameWidget::StoneReverse() { //돌 뒤집기
	int32 x = CurrentIndex % MapSize; //2
	int32 y = CurrentIndex / MapSize; //2

	int32 dx_arr[] = { 0,0,-1,1,-1,1,-1,1 };
	int32 dy_arr[] = { -1,1,0,0,-1,-1,1,1 };


	for (int t = 0; t < 8; t++) {

		int32 dx = dx_arr[t];
		int32 dy = dy_arr[t];

		int32 curr_x = x;
		int32 curr_y = y;

		TArray<int32> arry_x;
		TArray<int32> arry_y;

		while (0 <= curr_x + dx && curr_x + dx < MapSize && 0 <= curr_y + dy && curr_y + dy < MapSize)
		{
			curr_x += dx; curr_y += dy;

			if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 0 || BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 3) {
				arry_x.Empty();
				arry_y.Empty();
				break;
			}

			if (GameTurn == false && BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 2)
			{
				arry_x.Add(curr_x);
				arry_y.Add(curr_y);
				continue;
			}

			if (GameTurn == true && BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 1)
			{
				arry_x.Add(curr_x);
				arry_y.Add(curr_y);
				continue;
			}

			for (int i = 0; i < arry_x.Num(); i++)
			{
				int32 ax, ay;
				ax = arry_x[i];
				ay = arry_y[i];

				if (GameTurn == false) {
					BtnArray[ax + (ay * MapSize)]->OnBtnClickWhite();
					BtnArray[ax + (ay * MapSize)]->IsSetClickData(false);
				}

				else if (GameTurn == true) {
					BtnArray[ax + (ay * MapSize)]->OnBtnClickBlack();
					BtnArray[ax + (ay * MapSize)]->IsSetClickData(false);
				}
			}
			break;
		}
	}

	if (GameTurn == false) {
		GameTurn = true;
	}
	else if (GameTurn == true) {
		GameTurn = false;
	}
}

void UPlayGameWidget::GameSet()
{
	ClearAvailableMoves();

	if (!IsBoardFull() && !HasAnyValidMove(GameTurn))
	{
		GameTurn = !GameTurn;
		CountdownTime = GetTime();
		UpdateTimerDisplay();
	}

	for (int32 j = 0; j < MapSize; j++)
	{
		for (int32 i = 0; i < MapSize; i++) {
			BtnArrayIndex = i + j * MapSize;
			if (BtnArray[BtnArrayIndex]->GetSelectData() == false && IsCheckMakeMap(i, j, GameTurn) == true) {
				BtnArray[BtnArrayIndex]->AvailableBtnClick();
				// 상대 턴에 클릭 입력 안받기
				BtnArray[BtnArrayIndex]->SetVisibility(IsMyTurn() ? ESlateVisibility::Visible : ESlateVisibility::HitTestInvisible);
			}
		}
	}
	WhiteStoneCountText->SetText(FText::AsNumber(GetCountStone(1)));
	BlackStoneCountText->SetText(FText::AsNumber(GetCountStone(2)));
}
void UPlayGameWidget::ClearAvailableMoves()
{
	for (int32 Index = 0; Index < BtnArray.Num(); ++Index)
	{
		if (BtnArray[Index] && BtnArray[Index]->GetSelectData() == false)
		{
			BtnArray[Index]->NotAvailableBtnClick();
			BtnArray[Index]->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}

bool UPlayGameWidget::HasAnyValidMove(bool turn)
{
	// 지정한 색이 현재 보드에서 놓을 수 있는 칸이 존재하는지 확인
	for (int32 j = 0; j < MapSize; j++)
	{
		for (int32 i = 0; i < MapSize; i++)
		{
			const int32 Index = i + j * MapSize;
			if (BtnArray.IsValidIndex(Index) && BtnArray[Index] && BtnArray[Index]->GetSelectData() == false && IsCheckMakeMap(i, j, turn))
			{
				return true;
			}
		}
	}

	return false;
}

bool UPlayGameWidget::IsBoardFull()
{
	for (int32 Index = 0; Index < BtnArray.Num(); ++Index)
	{
		if (BtnArray[Index] && (BtnArray[Index]->GetStoneData() == 0 || BtnArray[Index]->GetStoneData() == 3))
		{
			return false;
		}
	}

	return true;
}
void UPlayGameWidget::GameOverSet()
{
	// 보드가 가득 찼거나 한쪽 돌이 0개일때 승패결정
	const int32 WhiteCount = GetCountStone(1);
	const int32 BlackCount = GetCountStone(2);

	WhiteStoneCountText->SetText(FText::AsNumber(WhiteCount));
	BlackStoneCountText->SetText(FText::AsNumber(BlackCount));

	if (!IsBoardFull() && WhiteCount > 0 && BlackCount > 0)
	{
		return;
	}

	if (WhiteCount > BlackCount)
	{
		GameOverText->SetText(FText::FromString(TEXT("White Win")));
	}
	else if (BlackCount > WhiteCount)
	{
		GameOverText->SetText(FText::FromString(TEXT("Black Win")));
	}
	else
	{
		GameOverText->SetText(FText::FromString(TEXT("Draw")));
	}

	SetGameOverText(true);
	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
}

bool UPlayGameWidget::IsCheckMakeMap(int x, int y, bool turn) {
	int32 dx_arr[] = { 0,0,-1,1,-1,1,-1,1 };
	int32 dy_arr[] = { -1,1,0,0,-1,-1,1,1 };

	for (int t = 0; t < 8; t++) {

		int32 curr_x = x;
		int32 curr_y = y;

		int32 dx = dx_arr[t];
		int32 dy = dy_arr[t];

		if (turn == false) {
			while (0 <= curr_x + dx && curr_x + dx < MapSize && 0 <= curr_y + dy && curr_y + dy < MapSize)
			{
				curr_x += dx;
				curr_y += dy;
				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 0)break;
				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 1)break;
				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 3)break;

				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 2) {
					if (0 <= curr_x + dx && curr_x + dx < MapSize && 0 <= curr_y + dy && curr_y + dy < MapSize) {
						if (BtnArray[curr_x + dx + ((curr_y + dy) * MapSize)]->GetStoneData() == 2)continue;
						if (BtnArray[curr_x + dx + ((curr_y + dy) * MapSize)]->GetStoneData() == 1)
							return true;
					}
				}
			}
		}

		else if (turn == true) {
			while (0 <= curr_x + dx && curr_x + dx < MapSize && 0 <= curr_y + dy && curr_y + dy < MapSize)
			{
				curr_x += dx;
				curr_y += dy;

				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 0)break;
				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 2)break;
				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 3)break;

				if (BtnArray[curr_x + (curr_y * MapSize)]->GetStoneData() == 1) {
					if (0 <= curr_x + dx && curr_x + dx < MapSize && 0 <= curr_y + dy && curr_y + dy < MapSize) {
						if (BtnArray[curr_x + dx + ((curr_y + dy) * MapSize)]->GetStoneData() == 1)continue;
						if (BtnArray[curr_x + dx + ((curr_y + dy) * MapSize)]->GetStoneData() == 2) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int32 UPlayGameWidget::GetCountStone(int32 type)
{
	int32 count = 0;

	for (int32 j = 0; j < MapSize; j++)
	{
		for (int32 i = 0; i < MapSize; i++)
		{
			BtnArrayIndex = i + j * MapSize;

			if (BtnArray[BtnArrayIndex]->GetStoneData() == type)
			{
				count++;
			}
		}
	}
	return count;
}

bool UPlayGameWidget::IsGetGameTurn()
{
	return GameTurn;
}

bool UPlayGameWidget::IsHostPlayer()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return PlayerController && PlayerController->HasAuthority();
}

bool UPlayGameWidget::IsMyTurn()
{
	//호스트가 흰돌
	return IsHostPlayer() ? GameTurn == false : GameTurn == true;
}

void UPlayGameWidget::SetGameOverText(bool boolen)
{
	if (boolen == true)
	{
		GameOverText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GameOverText->SetVisibility(ESlateVisibility::Collapsed);
		GameOverText->SetText(FText::FromString(TEXT("Game Over")));
	}
}

void UPlayGameWidget::SetMap() {
	for (int32 j = 0; j < MapSize; j++)
	{
		for (int32 i = 0; i < MapSize; i++) {

			BtnArrayIndex = i + j * MapSize;

			if ((i == MapHalfSize && j == MapHalfSize) || (i == MapHalfSize + 1 && j == MapHalfSize + 1))
			{
				BtnArray[BtnArrayIndex]->OnBtnClickWhite();
				BtnArray[BtnArrayIndex]->IsSetClickData(false);
				BtnArray[BtnArrayIndex]->SetVisibility(ESlateVisibility::HitTestInvisible);
			}

			if ((i == MapHalfSize + 1 && j == MapHalfSize) || (i == MapHalfSize && j == MapHalfSize + 1))
			{
				BtnArray[BtnArrayIndex]->OnBtnClickBlack();
				BtnArray[BtnArrayIndex]->IsSetClickData(false);
				BtnArray[BtnArrayIndex]->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
	}
}

int32 UPlayGameWidget::GetMapSize()
{
	return Cast<AOthelloStateBase>(GetWorld()->GetGameState())->GMBGetMapSize();
}

int32 UPlayGameWidget::GetTime()
{
	return Cast<AOthelloStateBase>(GetWorld()->GetGameState())->GMBGetTimer();
}

void UPlayGameWidget::UpdateTimeCount(int32 Count)
{
	Cast<AOthelloStateBase>(GetWorld()->GetGameState())->OnSetTimeCount(Count);
}

int32 UPlayGameWidget::GetTimeCount()
{
	return Cast<AOthelloStateBase>(GetWorld()->GetGameState())->GMBGetTimeCount();
}

void UPlayGameWidget::UpdateTimerDisplay()
{
	UpdateTimeCount(CountdownTime);
	TurnTimeText->SetText(FText::AsNumber(GetTimeCount()));
}

void UPlayGameWidget::AdvanceTimer(){
	// 제한 시간이 끝나면 턴을 넘김
	--CountdownTime;
	UpdateTimerDisplay();

	if (CountdownTime < 1)
	{
		CountdownTime = GetTime();
		GameTurn = !GameTurn;
		GameSet();
		GameOverSet();
	}
}

void UPlayGameWidget::PlayGameLogic() {
	// 본인턴이 아니면 클릭무시
	if (!IsMyTurn())
	{
		return;
	}

	for (int32 Index = 0; Index < BtnArray.Num(); ++Index)
	{
		if (BtnArray[Index] && BtnArray[Index]->GetClickData())
		{
			OnStoneClicked(Index);
			return;
		}
	}

}
void UPlayGameWidget::ApplyNetworkMove(int32 index){
	// 서버에서 전달된 위치를 모든 클라이언트가 같은 순서로 적용
	if (!BtnArray.IsValidIndex(index) || BtnArray[index] == nullptr)
	{
		return;
	}

	Num = index;
	UpdateNum(index);

	BtnArray[index]->IsSetClickData(true);
	BtnArray[index]->IsSetSelectData(true);

	CurrentIndex = index;
	OnClickDropStone();

	CountdownTime = GetTime();

	StoneReverse();

	GameSet();

	PlayAnimation(StoneNumAnimation);

	GameOverSet();
}


/*
void UPlayGameWidget::TestWidget(int a, int b) {
	Cast<AServerMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->WTestServer(a,b);
}
*/

void UPlayGameWidget::OnStoneClicked(int32 index) {
	Cast<AServerMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->BTest(index);
}

void UPlayGameWidget::UpdateNum(int32 value)
{
	Cast<AOthelloStateBase>(GetWorld()->GetGameState())->OnSetNum(value);
}

int32 UPlayGameWidget::GetNum()
{
	return Cast<AOthelloStateBase>(GetWorld()->GetGameState())->GMBGetNum();
}