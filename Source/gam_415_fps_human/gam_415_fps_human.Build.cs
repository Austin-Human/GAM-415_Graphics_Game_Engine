// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class gam_415_fps_human : ModuleRules
{
	public gam_415_fps_human(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
