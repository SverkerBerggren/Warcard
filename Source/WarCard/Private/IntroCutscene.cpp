// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroCutscene.h"
#include "Components/TextBlock.h" 
#include "IntroWidget.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values for this component's properties
UIntroCutscene::UIntroCutscene()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIntroCutscene::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIntroCutscene::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("Kommer hit"));

	if (UIntroWidget::GetWidget())
	{
		DeltaTime = 1.0f / 60.0f;
		ElapsedTime += DeltaTime;
		if (CurrentIndex >= Text.Num())
		{
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("World'/Game/Levels/TestGrid.TestGrid'"), TRAVEL_Absolute);
			return;
		}
		if (ElapsedTime > Durations[CurrentIndex])
		{
			CurrentIndex += 1;
			if (CurrentIndex < Durations.Num())
			{
				UIntroWidget::GetWidget()->firstTextBlock->SetText(FText::FromString(Text[CurrentIndex]));
				UIntroWidget::GetWidget()->backgroundIMage->SetBrushFromTexture(Images[CurrentIndex]);
			}
			ElapsedTime = 0;
		}
		UE_LOG(LogTemp, Warning, TEXT("Kommer hit"));
		//UIntroWidget::GetWidget()->firstTextBlock->SetText(FText::FromString("ASDASDASDASD"));
	}
	// ...
}

