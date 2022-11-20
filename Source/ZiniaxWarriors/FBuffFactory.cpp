// Fill out your copyright notice in the Description page of Project Settings.


#include "FBuffFactory.h"
#include "PowerBuff.h"

FBuffFactory::FBuffFactory()
{
}

FBuffFactory::~FBuffFactory()
{
}

template <typename T>
static IBuff* CreateBuff()
{
	T* NewBuff = NewObject<T>();
	return Cast<IBuff>(NewBuff);
}
