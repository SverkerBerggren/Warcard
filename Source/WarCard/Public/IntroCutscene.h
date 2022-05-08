// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IntroCutscene.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UIntroCutscene : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere)
	TArray<float> Durations;
	UPROPERTY(EditAnywhere)
	TArray<FString> Text;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> Images;
	//TArray<TS
	// Sets default values for this component's properties
	UIntroCutscene();

	float ElapsedTime = 0;
	int CurrentIndex = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
