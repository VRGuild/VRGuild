// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VRGuildServerTarget : TargetRules
{
	public VRGuildServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("VRGuild");

        // This instructs UBT to build an additional executable with the CONSOLE subsystem
        bBuildAdditionalConsoleApp = true;

    }
}
