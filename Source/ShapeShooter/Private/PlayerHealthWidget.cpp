// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthWidget.h"

void UPlayerHealthWidget::UpdateHealthBar(float HealthPercentage)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(HealthPercentage);
	}
}
