// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroWidget.h"

UIntroWidget* G_IntroWidget = nullptr;
void UIntroWidget::NativeConstruct()
{	
	//UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Cutscene3.Cutscene3'"), NULL, LOAD_None, NULL);
	//
	//if (nyBild == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));
	//
	//	return;
	//}
	//
	//backgroundIMage->SetBrushFromTexture(nyBild, false);
	G_IntroWidget = this;
}

UIntroWidget* UIntroWidget::GetWidget()
{
	return(G_IntroWidget);
}