// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameOff : ModuleRules
{
	public GameOff(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem", "GameplayTasks" });
	}
}
