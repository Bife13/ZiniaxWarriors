// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ZiniaxWarriorsClientTarget : TargetRules
{
	public ZiniaxWarriorsClientTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//bUseLoggingInShipping = true; // If you want logging in shipping build
		ExtraModuleNames.AddRange( new string[] { "ZiniaxWarriors" } );
	}
}
