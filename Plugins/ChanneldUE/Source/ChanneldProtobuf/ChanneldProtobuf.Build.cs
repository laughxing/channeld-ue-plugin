﻿using UnrealBuildTool;
using System.IO;

public class ChanneldProtobuf : ModuleRules
{
	public ChanneldProtobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});

		PublicSystemIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "ThirdParty"),
		});

		if (Target.bForceEnableRTTI)
		{
			bUseRTTI = true;
			PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=0");
		}
		else
		{
			bUseRTTI = false;
			PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
		}

		PublicDefinitions.AddRange(
			new string[]
			{
				"LANG_CXX11",
				"PROTOBUF_USE_DLLS", // Basically for ThreadCache
			}
		);
		
		ShadowVariableWarningLevel = WarningLevel.Off;
		bEnableUndefinedIdentifierWarnings = false;
	}
}