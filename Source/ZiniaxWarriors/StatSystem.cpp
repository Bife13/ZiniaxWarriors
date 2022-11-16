#include "StatSystem.h"


UStatSystem::UStatSystem()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}

void UStatSystem::DefenseUp(float Percentage,float Time)
{
	Resistance *= BaseResistance;
	
}


void UStatSystem::BeginPlay()
{
	Super::BeginPlay();


	
}



void UStatSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

}


