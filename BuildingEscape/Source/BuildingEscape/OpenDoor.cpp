// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	//Get Owner of Actor
	AActor* Owner = GetOwner();

	//Get Rotation 

	FRotator NewRotator = FRotator(0.0f, -90.0f, 0.0f);

	//Move Object

	Owner->SetActorRotation(NewRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if trigger volume
	//then 
	if (PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor();
	}
	// ...
}

