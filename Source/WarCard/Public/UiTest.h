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
UCLASS()
class WARCARD_API UUiTest : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		class UTextBlock* Texten; 
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* ForstaKnappen;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* KnappAktivera;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* KnappAktiveraAnnanUi;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UHorizontalBox* BoxAttAktivera;

	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UButton* ChangeImages;
	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UImage* BildAttForandra;

	 UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		 class UVerticalBox* BoxToDisplayIMage;

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
		 void CreateUnitCard(const UWCUnitInfo* unitReference);
};
