// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_Training_Project : ModuleRules
{
	public UE5_Training_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG","VRM4U", "UE5_Training_Project_Setting" });



        //PrivateDependencyModuleNames.AddRange(new string[] {"UE5_Training_Project_Setting" });


    }
}
