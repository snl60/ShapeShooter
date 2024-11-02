// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHealthWidget.generated.h"


UCLASS()
class SHAPESHOOTER_API UPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealthBar(float HealthPercentage);

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;
};
