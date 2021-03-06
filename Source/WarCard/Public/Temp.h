// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Temp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UTemp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTemp();

	UPROPERTY(EditAnywhere)
		TArray<float> Durations;
	UPROPERTY(EditAnywhere)
		TArray<FString> Text;
	UPROPERTY(EditAnywhere)
		TArray<UTexture2D*> Images;
	//TArray<TS
	// Sets default values for this component's properties

	float ElapsedTime = 0;
	int CurrentIndex = 0;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
