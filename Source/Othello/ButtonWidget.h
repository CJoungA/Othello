// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnBtnClickWhite();

	UFUNCTION()
		void OnBtnClickBlack();

	UFUNCTION()
		void AvailableBtnClick();

	UFUNCTION()
		void NotAvailableBtnClick();

	UFUNCTION()
		UButton* GetMapButton();

	UFUNCTION()
		int32 GetData();

	UFUNCTION()
		void SetStoneData(int32 value);

	UFUNCTION()
		int32 GetStoneData();

	UFUNCTION()
		void SetData(int32 value);

	UFUNCTION()
		void IsSetClickData(bool bValue);

	UFUNCTION()
		bool GetClickData();

	UFUNCTION()
		void IsSetSelectData(bool bValue);

	UFUNCTION()
		bool GetSelectData();

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* MapButton;

	UPROPERTY(EditAnywhere)
		class UTexture2D* WhiteStone;

	UPROPERTY(EditAnywhere)
		class UTexture2D* BlackStone;

	UPROPERTY(EditAnywhere)
		class UTexture2D* GreenGround;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* ButtonStone;

	int32 ButtonOrder;

	int32 StoneData;

	bool ClickData;

	bool SelectData;
};
