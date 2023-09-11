// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoundHorrorGameIdea : ModuleRules
{
	public SoundHorrorGameIdea(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AnimationBlueprintLibrary" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput"});
    }
}
