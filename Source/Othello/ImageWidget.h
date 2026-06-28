// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class OTHELLO_API UImageWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FString SetPath();

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTexture2D* WhiteStone;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTexture2D* BlackStone;

	UFUNCTION(BlueprintCallable)
		UTexture2D* LoadTextureFromPath(const FString& Path);

};
