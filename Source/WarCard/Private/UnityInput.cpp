// Fill out your copyright notice in the Description page of Project Settings.


#include "UnityInput.h"



APlayerController* G_Player1Controller = nullptr;


const char* i_KeyCodeStringMap[]
{
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    "Space",
    "Enter",
};



const char* KeyCodeToString(UnityKeyCode CodeToConvert)
{
    return(i_KeyCodeStringMap[uint64_t(CodeToConvert)]);
}


bool UnityInput::GetKeyDown(UnityKeyCode CodeToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    return(G_Player1Controller->IsInputKeyDown(KeyCodeToString(CodeToCheck)));
}
bool UnityInput::GetKeyUp(UnityKeyCode CodeToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        //G_Player1Controller->
        return false;
    }
    return(G_Player1Controller->WasInputKeyJustReleased(KeyCodeToString(CodeToCheck)));
}
bool UnityInput::GetKeyPressed(UnityKeyCode CodeToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    return(G_Player1Controller->WasInputKeyJustReleased(KeyCodeToString(CodeToCheck)));
}

bool UnityInput::GetKeyDown(FKey KeyToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    return(G_Player1Controller->IsInputKeyDown(KeyToCheck));
}
bool UnityInput::GetKeyUp(FKey KeyToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    return(G_Player1Controller->WasInputKeyJustReleased(KeyToCheck));
}
bool UnityInput::GetKeyPressed(FKey KeyToCheck)
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    return(G_Player1Controller->WasInputKeyJustReleased(KeyToCheck));
}
FVector2D UnityInput::GetMousePosition()
{
    if (G_Player1Controller == nullptr)
    {
        return false;
    }
    
    double x = 0;
    double y = 0;
    bool Result = G_Player1Controller->GetMousePosition(x, y);
    return(FVector2D(x, y));
}




// Sets default values for this component's properties
UUnityInput::UUnityInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnityInput::BeginPlay()
{
	Super::BeginPlay();

	G_Player1Controller = GetWorld()->GetFirstPlayerController();
	// ...
	
}


// Called every frame
void UUnityInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    G_Player1Controller = GetWorld()->GetFirstPlayerController();
    // ...
}

