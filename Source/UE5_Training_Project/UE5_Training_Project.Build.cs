// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_Training_Project : ModuleRules
{
	public UE5_Training_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
