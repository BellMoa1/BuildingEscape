// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

#define OUT



//#include "Engine/World.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysics();
	SetupInput();
}




// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	GetFirstPhysicsBodyInReach();
}

void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab release"));

}

void UGrabber::SetupInput()
{
	Component = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("Good"));
		Component->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Component->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing component"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Getting Player ViewPoint

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get Player view point in this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);


	///

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine
	(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0, 10.f
	);

	///Line Tracing Aka ray-tracing

	FHitResult Hit;
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit
		, PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		QueryParams
	);

	///See result 

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line tracing  %s "), *(ActorHit->GetName()))
	}
	return FHitResult();
}

void UGrabber::FindPhysics()
{
	Phisic = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Phisic)
	{
		///Phisic handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s mising phisic handle "), *GetOwner()->GetName());
	}
}