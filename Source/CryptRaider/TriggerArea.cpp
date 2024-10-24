#include "TriggerArea.h"
#include "Math/UnrealMathUtility.h"

UTriggerArea::UTriggerArea()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UTriggerArea::BeginPlay()
{
	Super::BeginPlay();
	if (!Mover)
	{
		UE_LOG(LogTemp, Display, TEXT("[%s] Mover is nullptr"), *GetOwner()->GetName());
		return;
	}
}

void UTriggerArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		Mover->SetShouldMove(true);
	}
	else 
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerArea::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerArea::GetAcceptableActor()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)

	{
		bool HasAcceptableTag = Actor->ActorHasTag(GargoyleTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			return Actor;
		}
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
			if (Component != nullptr)
			{
					Component->SetSimulatePhysics(false);
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			
			}
			else
			{
				Mover->SetShouldMove(false);
			}
			Mover->SetShouldMove(true);
		}

	}
	return nullptr;
}