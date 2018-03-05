// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArKDown : ModuleRules
{
	public ArKDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "AIModule",
            "GameplayTasks",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay"
        });


	}
}
