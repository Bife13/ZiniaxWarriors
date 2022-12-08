// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ZiniaxWarriorsServerTarget : TargetRules
{
	public ZiniaxWarriorsServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bUseLoggingInShipping = true; // If you want logging in shipping build
		ExtraModuleNames.AddRange( new string[] { "ZiniaxWarriors" } );
	}
}
