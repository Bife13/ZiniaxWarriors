// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidget.h"

void UWorldWidget::WW_SetHPSystem(UHealthSystem* Hp)
{
	
	WW_HPSystem=Hp;
	WW_HPSystem->OnDamageTakenEvent.AddUFunction(this,"GetDamageNumber");
	WW_HPSystem->OnDamageTakenEvent.AddUFunction(this,"OnDamage");
}

void UWorldWidget::OnDamage_Implementation()
{
	
}

float UWorldWidget::GetDamageNumber_Implementation(float damage)
{
	return  damage;
}


