// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Manager/EVisualClueType.h"
#include "VisualClue.generated.h"

UCLASS(EditInlineNew, blueprintable)
class SOUNDHORRORGAMEIDEA_API UVisualClue final : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	explicit UVisualClue(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualType)
	EVisualClueType VisualClueType;
	
	// A Material as as a UProperty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterial* Material;
	
};
