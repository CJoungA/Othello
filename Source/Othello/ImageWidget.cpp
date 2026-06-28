// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageWidget.h"

FString UImageWidget::SetPath() {
    FString Path = FString("/Game/Image/WhiteStone");
    return Path;
}

UTexture2D* UImageWidget::LoadTextureFromPath(const FString& Path)
{
    UTexture2D* sprite = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *Path));
    return sprite;
}

