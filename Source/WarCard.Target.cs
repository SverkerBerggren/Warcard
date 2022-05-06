// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WarCardTarget : TargetRules
{
	public WarCardTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		CppStandard = CppStandardVersion.Cpp17;
		//CppStandard = CppStandardVersion.Cpp17;
		ExtraModuleNames.AddRange( new string[] { "WarCard" } );
	}
}
