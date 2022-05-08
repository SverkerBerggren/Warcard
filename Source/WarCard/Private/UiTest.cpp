// Fill out your copyright notice in the Description page of Project Settings.


#include "UiTest.h"
#include "Styling/SlateBrush.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
//#include "Components/Image.h"

UUiTest* TheHud = nullptr;

void UUiTest::NativeConstruct()
{
//	UE_LOG(LogTemp, Warning, TEXT("Kommer den hit"));
	

	TheHud = this; 
	
//	passTurnSwitch->OnMouseButtonDownEvent(UUiTest::CreateUnitCard());

	UWCUnitInfo* testUnit = NewObject<UWCUnitInfo>();

	UUiTest::CreateUnitCard(testUnit);


//	UUiTest::CreateUnitCard(testUnit);

	buttonAttack->OnClicked.AddDynamic(this, &UUiTest::AttackButtonFunction);
	buttonMove->OnClicked.AddDynamic(this, &UUiTest::MoveButtonFunction);
	buttonAbility->OnClicked.AddDynamic(this, &UUiTest::AbilityButtonFunction);
	passTurnSwitch->OnClicked.AddDynamic(this, &UUiTest::ChangeTurnButtonFunction);
	

//	CanvasUnitCard->SetVisibility(ESlateVisibility::Hidden);

//	SetActivePlayer(2);
//	UpdatePlayerScore(1, 15);
//	SetRoundTimer(45);
//	turnSignifierRight->SetVisibility(ESlateVisibility::Hidden);
//	turnSignifierRight->SetVisibility(ESlateVisibility::Visible);
//	imageChangeTurnRight->SetVisibility(ESlateVisibility::Hidden);

//	SetInitiativ(5);
//	ChangeTurnButtonFunction();

	// SetBottomHud(ESlateVisibility::Hidden);

}
void UUiTest::SetButtonCallback(ButtonCallbacks* inputObject)
{
	
		callBack = inputObject;
	
}


void UUiTest::MoveButtonFunction()
{
	if (callBack != nullptr)
	{
		callBack->OnClick(ButtonType::Move);
	}
}


void UUiTest::AttackButtonFunction()
{
	if (callBack != nullptr)
	{
		callBack->OnClick(ButtonType::Attack);
	}
}


void UUiTest::AbilityButtonFunction()
{
	if (callBack != nullptr)
	{
		callBack->OnClick(ButtonType::Ability);
	}
}

void UUiTest::ChangeTurnButtonFunction()
{
	
	if (callBack != nullptr)
	{
		callBack->OnClick(ButtonType::ChangeTurn);
	}	
	//UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Switch2_2.Switch2_2'"), NULL, LOAD_None, NULL);
//
 //	brushToChange.SetResourceObject(nyBild);
 //
 //	passTurnSwitch->WidgetStyle.SetNormal(brushToChange);

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

void UUiTest::SetCardVisiblity(ESlateVisibility state)
{
	CanvasUnitCard->SetVisibility(state);
}

void UUiTest::CreateBottomHud(UWCUnitInfo* unitReference)
{
	
}

void UUiTest::UpdatePlayerScore(int playerIndex, int scoreToSet)
{
	if (playerIndex == 1)
	{
		leftPlayerScore->SetText(FText::FromString(FString::FString("Left player: ") + FString::FormatAsNumber(scoreToSet) + FString::FString("/30"))); 

		if (10 > scoreToSet && scoreToSet >= 5)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_2.Score_2'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}
		if (15 > scoreToSet && scoreToSet >= 10)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_3.Score_3'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}
		if (20 > scoreToSet && scoreToSet >= 15)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_4.Score_4'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}
		if (25 > scoreToSet && scoreToSet >= 20)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_5.Score_5'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}
		if (30 > scoreToSet && scoreToSet >= 25)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_6.Score_6'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}
		if (scoreToSet >= 30)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_7.Score_7'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageLeft->SetBrushFromTexture(nyBild, false);
		}

	}
	if (playerIndex == 2)
	{
		rightPlayerScore->SetText(FText::FromString(FString::FString("Right player: ") + FString::FormatAsNumber(scoreToSet) + FString::FString("/30")));

		if (10 > scoreToSet && scoreToSet >= 5)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_2.Score_2'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
		if (15 > scoreToSet && scoreToSet >= 10)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_3.Score_3'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
		if (20 > scoreToSet && scoreToSet >= 15)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_4.Score_4'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
		if (25 > scoreToSet && scoreToSet >= 20)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_5.Score_5'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
		if (30 > scoreToSet && scoreToSet >= 25)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_6.Score_6'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
		if (scoreToSet >= 30)
		{
			UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Score_7.Score_7'"), NULL, LOAD_None, NULL);

			if (nyBild == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Den blev inte settad"));

				return;
			}

			scoreImageRight->SetBrushFromTexture(nyBild, false);
		}
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

		isImageSwitchRight = true;
		UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Switch2_2.Switch2_2'"), NULL, LOAD_None, NULL);
		if (nyBild == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nullptr med bild"));
			return;
		}
		imageChangeTurn->SetBrushFromTexture(nyBild,false);
		turnIdentifier->SetBrushFromTexture(nyBild,false);
	}
	if (activePlayer == 2)
	{
	

		isImageSwitchRight = true;
		UTexture2D* nyBild = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/Sprites/Switch2_2.Switch2_2'"), NULL, LOAD_None, NULL);
		if (nyBild == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nullptr med bild"));
			return;
		}
		imageChangeTurn->SetBrushFromTexture(nyBild, false);
		turnIdentifier->SetBrushFromTexture(nyBild);
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

