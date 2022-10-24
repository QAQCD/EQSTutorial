// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CSEQS : ModuleRules
{
	public CSEQS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "AIModule", "InputCore", "HeadMountedDisplay" });
	}
}
