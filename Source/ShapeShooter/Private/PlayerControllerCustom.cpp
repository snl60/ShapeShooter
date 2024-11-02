// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerCustom.h"


APlayerControllerCustom::APlayerControllerCustom() 
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("/Game/Widgets/CW_Bullseye.CW_Bullseye_C"));
	if (WidgetClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget class found."))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Widget class not found."))
	}
}


void APlayerControllerCustom::BeginPlay()
{
	Super::BeginPlay();
	
	// Show the mouse cursor and enable events
	bShowMouseCursor = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Create and add the cursor widget
	if (WidgetClass != nullptr)
	{
		CursorWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (CursorWidget != nullptr)
		{
			CursorWidget->AddToViewport();
		}
	}
}

void APlayerControllerCustom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorWidget)
	{
		float MouseX, MouseY;
		if (GetMousePosition(MouseX, MouseY))
		{
			FVector2D WidgetSize = CursorWidget->GetDesiredSize();
			
			FVector2D ScreenPosition(MouseX - (WidgetSize.X / 2), MouseY - (WidgetSize.Y / 2));

			CursorWidget->SetPositionInViewport(ScreenPosition, true);
		}
	}
}
