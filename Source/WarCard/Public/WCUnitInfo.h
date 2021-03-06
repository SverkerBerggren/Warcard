// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WCUnitInfo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UWCUnitInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWCUnitInfo();

	UPROPERTY(EditAnywhere);
	int UnitID = 0;
	UPROPERTY(EditAnywhere);
	int Movement = 0;
	UPROPERTY(EditAnywhere);
	int HP = 0;
	UPROPERTY(EditAnywhere);
	int Range = 0;
	UPROPERTY(EditAnywhere);
	int Damage = 0;
	UPROPERTY(EditAnywhere);
	int ActivationCost = 0;

	UPROPERTY(EditAnywhere);
	FText description = FText::AsNumber(420);

	UPROPERTY(EditAnywhere);
	UPaperSprite* IdleSprite1 = nullptr;

	UPROPERTY(EditAnywhere);
	UPaperSprite* DamageSprite1 = nullptr;

	UPROPERTY(EditAnywhere);
	UPaperSprite* IdleSprite2 = nullptr;

	UPROPERTY(EditAnywhere);
	UPaperSprite* DamageSprite2 = nullptr;

	UPROPERTY(EditAnywhere);
	UTexture2D* cardImage;




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
