// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallItemBase.h"

// Sets default values
ARollABallItemBase::ARollABallItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollABallItemBase::OverlapBegin);
}

// Called when the game starts or when spawned
void ARollABallItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARollABallItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
}

void ARollABallItemBase::Collected_Implementation()
{
	
}
