// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WCUnitInfo.h"
#include "Components/Image.h" 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IntroWidget.generated.h"

/**
 * 
 */
UCLASS()
class WARCARD_API UIntroWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		class UTextBlock* firstTextBlock;
		UPROPERTY(BlueprintReadwrite, meta = (BindWidget))
		class UImage* backgroundIMage;

		static UIntroWidget* GetWidget();

		virtual void NativeConstruct() override;
	
};
