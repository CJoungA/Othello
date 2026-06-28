// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ServerMenuController.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API AServerMenuController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer(FString IpAddress);

	UFUNCTION(Client, Reliable)
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
		void ChangeMenuWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass);

	void SetPlayGameLogic();

	UFUNCTION(Server, Reliable)
		void SetPlayGameLogicServer();
		void SetPlayGameLogicServer_Implementation();

	UFUNCTION(Client, Reliable)
		void SetPlayGameLogicClient();
		void SetPlayGameLogicClient_Implementation();

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

		void WTest(int a, int b);

	UFUNCTION(Server, Reliable)
		void WTestServer(int a, int b);
		void WTestServer_Implementation(int a, int b);

	UFUNCTION(Client, Reliable)
		void WTestClient(int a, int b);
		void WTestClient_Implementation(int a, int b);


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

	void BTest(int32 index);

	UFUNCTION(Server, Reliable)
		void BTestServer(int32 index);
		void BTestServer_Implementation(int32 index);

	UFUNCTION(Client, Reliable)
		void BTestClient(int32 index);
		void BTestClient_Implementation(int32 index);


		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------


	UFUNCTION()
		UUserWidget* GetWidget();


protected:

	UPROPERTY()
		UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> PlayGameWidgetClass;


};

