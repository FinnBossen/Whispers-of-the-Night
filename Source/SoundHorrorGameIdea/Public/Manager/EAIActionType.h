#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAIActionType: uint8
{
	Walk,
	Door,
	Wait
};
