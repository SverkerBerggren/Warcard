// Fill out your copyright notice in the Description page of Project Settings.



#include "Components/Button.h"
#include "Components/TextBlock.h"
//#include "Components/Image.h"
#include "UiTest.h"


void UUiTest::NativeConstruct()
{
	UE_LOG(LogTemp, Warning, TEXT("Kommer den hit"));
	if (ForstaKnappen)
	{
		ForstaKnappen->OnClicked.AddDynamic(this, &UUiTest::ForstaKnappenKlick);
	}
	
	if (KnappAktivera)
	{
		UE_LOG(LogTemp, Warning, TEXT("kommer den sen "));
		KnappAktivera->OnClicked.AddDynamic(this, &UUiTest::KnappAktiveraKlick);
	}
	if (KnappAktiveraAnnanUi)
	{
		KnappAktiveraAnnanUi->OnClicked.AddDynamic(this, &UUiTest::TestKlick);
	}

	if (ChangeImages)
	{
		ChangeImages->OnClicked.AddDynamic(this, &UUiTest::ChangeImageClick); 
	}
}

void UUiTest::ForstaKnappenKlick()
{
	Texten->SetText(FText::AsNumber(17));
	UE_LOG(LogTemp, Warning, TEXT("Funktionen kan printa"));
}


void UUiTest::KnappAktiveraKlick()
{
	ForstaKnappen->SetIsEnabled(false);

//	ESlateVisibility testVisibility = ESlateVisibility.hidd
	KnappAktiveraAnnanUi->SetVisibility(ESlateVisibility::Visible);
}

void UUiTest::TestKlick()
{
	UE_LOG(LogTemp, Warning, TEXT("Man kan klicka pa knappen"));
	Texten->SetText(FText::AsNumber(20));
}


void UUiTest::ChangeImageClick()
{
//	FSlateBrush testBild = FSlateBrush();
// 
	UE_LOG(LogTemp, Warning, TEXT("Den forsoke andra bild"));
	UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/1_2_2.1_2_2'"), NULL, LOAD_None, NULL);
	BildAttForandra->SetBrushSize(FVector2D(5, 19));

	BildAttForandra->Brush.SetImageSize(FVector2D(5, 5));

	UE_LOG(LogTemp, Warning, TEXT("hallo %f"),BildAttForandra->Brush.GetImageSize().X );
//	BildAttForandra->Brush.SetImageSize(FVector2D(4, 20));
//	BildAttForandra->SynchronizeProperties();
	
	
	BildAttForandra->SetColorAndOpacity(FLinearColor(1, 4, 5, 6));
	
	//BildAttForandra->SetVisibility(ESlateVisibility::Hidden);
 	//BildAttForandra->SetBrushFromTexture(nyBild, true);
}

