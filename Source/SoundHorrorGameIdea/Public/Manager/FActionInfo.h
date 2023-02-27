#pragma once
#include "CoreMinimal.h"
#include "EAIActionType.h"
#include "FActionInfo.generated.h"


USTRUCT(BlueprintType)
struct FActionInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "ActionInfo")
	bool bIsWaiting;

	UPROPERTY(BlueprintReadWrite, Category = "ActionInfo")
	EAIActionType ActionType;
};
