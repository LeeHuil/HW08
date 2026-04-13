// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameMode.h"
#include "PPawn.h"
#include "PPlayerController.h"

APGameMode::APGameMode()
{
	DefaultPawnClass = APPawn::StaticClass();
	PlayerControllerClass = APPlayerController::StaticClass();
}