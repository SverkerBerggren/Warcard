// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WCUnitInfo.h"
#include "Components/Image.h" 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UiTest.generated.h"



/**
 * 
 */


enum class ButtonType
{
	Move,
	Attack, 
	Ability,
	ChangeTurn, 
};

class ButtonCallbacks
{	public: 
	virtual void OnClick(ButtonType button)
	{

	}
	
};


UCLASS()
class WARCARD_API UUiTest : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UImage* unitImage;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UCanvasPanel* CanvasUnitCard;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* textDescription;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* textMovement;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* textDamage;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* textRange;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* initiativText;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* textHP;






	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* leftPlayerScore;

	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* rightPlayerScore;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* battleRoundText;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UTextBlock* initiativTextCorner;


	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UImage* turnIdentifier;


	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* buttonMove;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* buttonAttack;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* buttonAbility;


	 virtual void NativeConstruct() override;

	 

//	 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SoftObject", meta = (AllowedClasses = "Texture2D"))
//		 FSoftObjectPath hej TEXT("Texture2D'/Game/Sprites/1_2_2.1_2_2'");

	 UFUNCTION()
	  void ForstaKnappenKlick();
	 UFUNCTION()
	  void KnappAktiveraKlick();
	 UFUNCTION()
	  void TestKlick();
	 UFUNCTION()
		 void ChangeImageClick();
	 UFUNCTION()
		 void CreateUnitCard(UWCUnitInfo* unitReference);

	 UFUNCTION()
		 void CreateBottomHud(UWCUnitInfo* unitReference);

	 UFUNCTION()
		 void HideUnitCard();

	 UFUNCTION()
		 void MoveButtonFunction();
	 UFUNCTION()
		 void AttackButtonFunction();
	 UFUNCTION()
		 void AbilityButtonFunction();
	 UFUNCTION()
		 void ChangeTurnButtonFunction();


public: 
	void UpdatePlayerScore(int playerIndex, int scoreToSet);
	void SetRoundTimer(int round);
	void SetActivePlayer(int playerIndex);
	void SetInitiativ(int intitativ);
	void HideAll(); 
	

	void SetBottomHud(ESlateVisibility hej);
	// bvoid HideBottomHud();
	void SetBottomButton(ButtonType, bool);
//	void EnableBottomButton(ButtonType);


	ButtonCallbacks* callBack = nullptr; 




	void SetButtonCallback(ButtonCallbacks* );

	static UUiTest* GetHud();
	

//	void ChangeTurn();
//	void SetButtonCallbacks()


};
