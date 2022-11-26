// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidget.h"




void UWorldWidget::WorldWigetSetUp(UProgressBar* Bar, UUI_Observer* Obs){
	Observer= Obs;
	HPBAr= Bar;

	

	HealthSystem=Observer->GetHealthSystem();
	
}

void UWorldWidget::UpdateHPBar()
{
	HPBAr->Percent = HealthSystem->GetHealthAsPercentage();
	
}
