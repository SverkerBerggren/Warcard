// Fill out your copyright notice in the Description page of Project Settings.

#include "TileManager.h"
#include "UnityInput.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
//#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"

// Sets default values for this component's properties
UTileManager::UTileManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTileManager::BeginPlay()
{
	Super::BeginPlay();

	double CurrentY = 0;
	double CurrentX = 0;
	double SpriteWidth = 0;
	m_Grid.Reserve(Width);
	for (int i = 0; i < Height; i++)
	{
		TArray<AActor*> NewRow;
		for (int j = 0; j < Width; j++)
		{
			FVector Position = { CurrentX,CurrentY,0 };
			FTransform NewTransform;
			NewTransform.SetLocation(Position);
			AActor* NewActor = GetWorld()->SpawnActor<AActor>(TileObject, NewTransform);
			UPaperSpriteComponent* SpriteComponent = NewActor->FindComponentByClass<UPaperSpriteComponent>();
			if(SpriteComponent)
			{
				SpriteWidth = SpriteComponent->GetSprite()->GetBakedTexture()->GetSizeX();
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("No sprite component for tiles"));
			}
			UWCTile* TileComponent = NewActor->FindComponentByClass<UWCTile>();
			if (TileComponent)
			{
				TileComponent->X = j;
				TileComponent->Y = i;
				TileComponent->AssociatedGrid = this;
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("No tile component for tiles"));
			}
			CurrentX += SpriteWidth;
			NewRow.Add(NewActor);
		}
		CurrentX = 0;
		CurrentY += SpriteWidth;
		m_Grid.Add(NewRow);
	}
	m_RuleEngine = WCE::RuleEngine(Width, Height);
	m_GridStartPosition = FVector2D( 0,0 );
	m_TileWidth = SpriteWidth;
	// ...
	//Blue
}

void UTileManager::p_ClearSelectedTiles()
{
	for (size_t i = 0; i < m_HighlightTiles.Num(); i++)
	{
		m_HighlightTiles[i]->Destroy();
	}
	m_HighlightTiles.Empty();
}
void UTileManager::GridClick(int X, int Y) 
{
	//UE_LOG(LogTemp, Warning, TEXT("Grid clickelick"));
	if (m_HighlightTiles.Num() > 0)
	{
		p_ClearSelectedTiles();
	}
	UE_LOG(LogTemp, Warning, TEXT("Highlighting"));
	FVector Position = FVector(m_GridStartPosition.X+X*m_TileWidth,m_GridStartPosition.Y+Y*m_TileWidth,20);
	FTransform NewTransform;
	NewTransform.SetLocation(Position);
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(SelectTile, NewTransform);
	m_HighlightTiles.Add(NewActor);
}

// Called every frame
void UTileManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UnityInput::GetKeyDown(EKeys::SpaceBar))
	{
		//FActorSpawnParameters Parameters = FActorSpawnParameters();
		UE_LOG(LogTemp, Warning, TEXT("Spawn Tile"));
		if (TileObject)
		{
			FVector Position = { 0,0,0 };
			FTransform NewTransform;
			NewTransform.SetLocation(FVector3d(0, 0, 0));
			GetWorld()->SpawnActor<AActor>(TileObject, NewTransform);
			//Parameters.Template = TileObject;
			//FVector NewPosition = -TileObject->GetTransform().GetLocation();
			//AActor* NewActor =GetWorld()->SpawnActor<AActor>(NewPosition, FRotator());
			//UEngine::CopyPropertiesForUnrelatedObjects(TileObject, NewActor);
		}
	}
	// ...
}

