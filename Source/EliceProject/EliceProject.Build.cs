// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EliceProject : ModuleRules
{
	public EliceProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("EliceProject");
		PublicIncludePaths.Add("EliceProject");

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UnrealEd", "NavigationSystem" });
	}
}
