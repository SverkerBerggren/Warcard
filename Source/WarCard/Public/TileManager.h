// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UTileManager : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TileObject;

	UPROPERTY(EditAnywhere)
	int Height = 20;
	UPROPERTY(EditAnywhere)
	int Width = 20;
	TArray<TArray<AActor*>> m_Grid;
	//UPROPERTY(EditAnywhere)
	//A
	//AActor
	
	
	// Sets default values for this component's properties
	UTileManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
