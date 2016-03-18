// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

static void printOnScreen(FString msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, msg);
}