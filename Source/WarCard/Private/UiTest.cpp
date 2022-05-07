// Fill out your copyright notice in the Description page of Project Settings.



#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
//#include "Components/Image.h"
#include "UiTest.h"

UUiTest* TheHud = nullptr;

void UUiTest::NativeConstruct()
{
//	UE_LOG(LogTemp, Warning, TEXT("Kommer den hit"));
	

	TheHud = this; 


	UWCUnitInfo* testUnit = NewObject<UWCUnitInfo>();

	UUiTest::CreateUnitCard(testUnit);

//	CanvasUnitCard->SetVisibility(ESlateVisibility::Hidden);

	SetActivePlayer(2);
	UpdatePlayerScore(1, 10);
	SetRoundTimer(45);

	SetInitiativ(5);

	// SetBottomHud(ESlateVisibility::Hidden);

}
void UUiTest::SetButtonCallback(ButtonCallbacks* inputObject)
{
	callBack = inputObject; 
}


void UUiTest::MoveButtonFunction()
{
	callBack->OnClick(ButtonType::Move);
}


void UUiTest::AttackButtonFunction()
{
	callBack->OnClick(ButtonType::Attack);
}


void UUiTest::AbilityButtonFunction()
{
	callBack->OnClick(ButtonType::Ability);
}

void UUiTest::ChangeTurnButtonFunction()
{
	callBack->OnClick(ButtonType::ChangeTurn);
}



void UUiTest::SetBottomButton(ButtonType whichButton, bool state)
{
	if (whichButton == ButtonType::Move)
	{
		buttonMove->SetIsEnabled(state);
	}
	if (whichButton == ButtonType::Attack)
	{
		buttonAttack->SetIsEnabled(state);
	}
	if (whichButton == ButtonType::Ability)
	{
		buttonAbility->SetIsEnabled(state);
	}
}

void UUiTest::ForstaKnappenKlick()
{
//	Texten->SetText(FText::AsNumber(17));
	UE_LOG(LogTemp, Warning, TEXT("Funktionen kan printa"));
}


void UUiTest::KnappAktiveraKlick()
{
//	ForstaKnappen->SetIsEnabled(false);

//	ESlateVisibility testVisibility = ESlateVisibility.hidd
//	KnappAktiveraAnnanUi->SetVisibility(ESlateVisibility::Visible);
}

void UUiTest::TestKlick()
{ 
	UE_LOG(LogTemp, Warning, TEXT("Man kan klicka pa knappen"));
//	Texten->SetText(FText::AsNumber(20));

	CanvasUnitCard->SetVisibility(ESlateVisibility::Visible);
}

void UUiTest::HideUnitCard()
{
	CanvasUnitCard->SetVisibility(ESlateVisibility::Visible);
}

void UUiTest::CreateUnitCard( UWCUnitInfo* unitToConstruct)
{
	textMovement->SetText(FText::AsNumber(unitToConstruct->Movement));
	textDamage->SetText(FText::AsNumber(unitToConstruct->Damage));
	textHP->SetText(FText::AsNumber(unitToConstruct->HP));
	textRange->SetText(FText::AsNumber(unitToConstruct->Range));
	initiativText->SetText(FText::AsNumber(unitToConstruct->ActivationCost));
	textDescription->SetText(unitToConstruct->description);

	UTexture2D* nyBild = unitToConstruct->cardImage;

	if (nyBild == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

		return;
	}

	unitImage->SetBrushFromTexture(nyBild, false);

	
}

void UUiTest::CreateBottomHud(UWCUnitInfo* unitReference)
{
	
}

void UUiTest::UpdatePlayerScore(int playerIndex, int scoreToSet)
{
	if (playerIndex == 1)
	{
		leftPlayerScore->SetText(FText::FromString(FString::FString("Left player: ") + FString::FormatAsNumber(scoreToSet) + FString::FString("/30")));

	}
	if (playerIndex == 2)
	{
		leftPlayerScore->SetText(FText::FromString(FString::FString("Right player: ") + FString::FormatAsNumber(scoreToSet) + FString::FString("/30")));

	}
}

void UUiTest::SetRoundTimer(int round)
{
	battleRoundText->SetText(FText::FromString(FString::FString("Round: ") + FString::FormatAsNumber(round)));
}
void UUiTest::SetActivePlayer(int activePlayer)
{
	if (activePlayer == 1)
	{
		UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Switch2.Switch2'"), NULL, LOAD_None, NULL);

		if (nyBild == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

			return;
		}

		turnIdentifier->SetBrushFromTexture(nyBild, false);
	}
	if (activePlayer == 2)
	{
		UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Switch2_2.Switch2_2'"), NULL, LOAD_None, NULL);

		if (nyBild == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

			return;
		}
		turnIdentifier->SetBrushFromTexture(nyBild, false);
	}
}


UUiTest* UUiTest::GetHud()
{
	return TheHud; 
}

void UUiTest::SetInitiativ(int intitativ)
{
	initiativTextCorner->SetText(FText::FromString(FString::FormatAsNumber(intitativ) + FString::FString("/10"))) ;
}

void UUiTest::SetBottomHud(ESlateVisibility state)
{
	buttonMove->SetVisibility(ESlateVisibility::Hidden);
	buttonAttack->SetVisibility(ESlateVisibility::Hidden);
	buttonAbility->SetVisibility(ESlateVisibility::Hidden);
}

void UUiTest::ChangeImageClick()
{
//	FSlateBrush testBild = FSlateBrush();
// 
	UE_LOG(LogTemp, Warning, TEXT("Den forsoke andra bild"));
	UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/OskarTexture.OskarTexture'"), NULL, LOAD_None, NULL);
//	BildAttForandra->SetBrushSize(FVector2D(5, 19));


	if (nyBild == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

		return; 
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Storleken av bilden %d"), nyBild->GetSizeX());

//	UE_LOG(LogTemp, Warning, TEXT("Den forsoke andra bild"));
	

//	BildAttForandra->Brush.SetImageSize(FVector2D(5, 5));

//	BildAttForandra->SetBrush(FSlateBrush())

//	UE_LOG(LogTemp, Warning, TEXT("hallo %f"),BildAttForandra->Brush.GetImageSize().X );
//	BildAttForandra->Brush.SetImageSize(FVector2D(4, 20));
//	BildAttForandra->SynchronizeProperties();
	
	

//	BildAttForandra->SetColorAndOpacity(FLinearColor(1, 4, 5, 6));
	
	//BildAttForandra->SetVisibility(ESlateVisibility::Hidden);
 //	BildAttForandra->SetBrushFromTexture(nyBild, true);
}

