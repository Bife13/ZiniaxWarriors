// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_CustomizationWidget.h"

void UCpp_CustomizationWidget::SetAbility(int number, int index)
{
	switch (number)
	{
	case 1:
		Ability1ID = index;
		break;
	case 2:
		Ability2ID = index;
		break;
	case 3:
		Ability3ID = index;
		break;
		default:
			break;
	}
}

int UCpp_CustomizationWidget::GetAbility(int number)
{
	int i =-1;
	switch (number)
	{
	case 1:
		i =Ability1ID;
		break;
	case 2:
		i= Ability2ID;
		break;
	case 3:
		i = Ability3ID;
		break;
	default:
		break;
	}
	return i;
}

FString UCpp_CustomizationWidget::GetConfigInString()
{
	FString result;
	
	result = "?Warrior="+WarriorIndexToString(WarriorID)+"?Ability1="+AbilityIndexToString(Ability1ID)
			+"?Ability2="+AbilityIndexToString(Ability2ID)+"?Ability3="+AbilityIndexToString(Ability3ID);
	return result;
}


FString UCpp_CustomizationWidget::WarriorIndexToString(int index)
{
	FString Name;
	switch (index)
	{
	case 0:
		Name ="Drex";
		break;
	case 1:
		Name ="Nyax";
		break;

	case 2:
		Name ="Zerher";
		break;
	default:
		break;
	}
	return Name;
}
FString UCpp_CustomizationWidget::AbilityIndexToString(int index)
{
	FString abilityName;

	switch (index)
	{
	case 0:
		abilityName ="SmallHeal";
		break;
	case 1:
		abilityName ="Roar";
		break;
	case 2:
		abilityName ="EletroGate";
		break;
	case 3:
		abilityName ="Anchor";
		break;
	case 4:
		abilityName ="DarkSwarm";
		break;
	case 5:
		abilityName ="SingleShot";
		break;
	default: break;
	}
	return abilityName;
}



void UCpp_CustomizationWidget::SetWarrior(int index)
{
	WarriorID =index;
	UE_LOG(LogTemp, Log, TEXT("WarriorIDSetted as: '%d'"), WarriorID)
	
}


bool UCpp_CustomizationWidget::IsWarriorSetUp()
{
	if(WarriorID !=-1 && Ability1ID!=-1 && Ability2ID!=-1&& Ability3ID!=-1)
	{
		return true;
	}
	else
	{
		return false;
	}

}
