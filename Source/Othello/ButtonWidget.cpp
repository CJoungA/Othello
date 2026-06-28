// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ImageWidget.h"

void UButtonWidget::NativeConstruct() {
	Super::NativeConstruct();
	SetStoneData(0);
	IsSetClickData(false);
	IsSetSelectData(false);
	MapButton->OnClicked.AddDynamic(this, &UButtonWidget::OnBtnClickWhite);
}

void UButtonWidget::SetData(int32 value) {
	ButtonOrder = value;
}

int32 UButtonWidget::GetData() {
	return ButtonOrder;
}

void UButtonWidget::SetStoneData(int32 value)
{
	StoneData=value;
}

int32 UButtonWidget::GetStoneData() {
	return StoneData;
}

void UButtonWidget::OnBtnClickWhite()
{
	ButtonStone->SetBrushFromTexture(WhiteStone);
	SetStoneData(1);
	IsSetClickData(true);
	IsSetSelectData(true);
}

void UButtonWidget::OnBtnClickBlack()
{
	ButtonStone->SetBrushFromTexture(BlackStone);
	SetStoneData(2);
	IsSetClickData(true);
	IsSetSelectData(true);
}

void UButtonWidget::AvailableBtnClick()
{
	ButtonStone->SetBrushFromTexture(GreenGround);
	SetStoneData(3);
}

void UButtonWidget::NotAvailableBtnClick()
{
	ButtonStone->SetBrushFromTexture(NULL);
	SetStoneData(0);
}

UButton* UButtonWidget::GetMapButton()
{
	return MapButton;
}

void UButtonWidget::IsSetClickData(bool bValue) {
	ClickData = bValue;
}

bool UButtonWidget::GetClickData() {
	return ClickData;
}

void UButtonWidget::IsSetSelectData(bool bValue) {
	SelectData = bValue;
}

bool UButtonWidget::GetSelectData() {
	return SelectData;
}