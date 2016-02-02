// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class OpenDDLParser : ModuleRules
	{		
		public OpenDDLParser(TargetInfo Target)
		{
			Type = ModuleType.External;

			var bPlatformAllowed = (Target.Platform == UnrealTargetPlatform.Win64);

			if (bPlatformAllowed)
			{
				Definitions.Add("OPENDDL_STATIC_LIBARY=1");

				string OpenDDLParserPath = ModulePath + "/openddl-parser/";
				PublicIncludePaths.Add(OpenDDLParserPath + "include");

				if (Target.Platform == UnrealTargetPlatform.Win64)
				{
					if (WindowsPlatform.Compiler == WindowsCompiler.VisualStudio2015)
					{
						if (Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT)
						{
							PublicLibraryPaths.Add(OpenDDLParserPath + "lib/Debug/");
						}
						else
						{
							PublicLibraryPaths.Add(OpenDDLParserPath + "lib/Release/");
						}
						
						PublicAdditionalLibraries.Add("openddl_parser.lib");
					}
				}
			}
		}
		
		private string ModulePath
		{
			get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
		}	
	}

}