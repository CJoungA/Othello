// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API UServerMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;


	UFUNCTION()
		void QuitButtonClicked();

	UFUNCTION()
		void HostServerHandler();

	UFUNCTION()
		void JoinServerHandler();

	UFUNCTION()
		FString GetIpAddress();


protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString TransferLevelName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* HostGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* JoinGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* IpAddressText;

};
