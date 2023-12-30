// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JH_Multi_RPG : ModuleRules
{
	public JH_Multi_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem","UMG" });
	}
}
