// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
};
