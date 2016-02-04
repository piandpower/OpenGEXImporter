// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class OpenGEXParser : ModuleRules
	{		
		public OpenGEXParser(TargetInfo Target)
		{
			Type = ModuleType.External;

			var bPlatformAllowed = (Target.Platform == UnrealTargetPlatform.Win64);

			if (bPlatformAllowed)
			{
				string OpenGEXParserPath = ModulePath + "/opengex-parser/";
				PublicIncludePaths.Add(OpenGEXParserPath + "include");
				
				string ThirdPartyBinariesPath = ModulePath + "/bin/";

				if (Target.Platform == UnrealTargetPlatform.Win64)
				{
					if (WindowsPlatform.Compiler == WindowsCompiler.VisualStudio2015)
					{
						if (Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT)
						{
							PublicLibraryPaths.Add(OpenGEXParserPath + "lib/x64/VS2015/Debug/");
							
							PublicAdditionalLibraries.Add("opengex-parser_Debug.lib");
						}
						else
						{
							PublicLibraryPaths.Add(OpenGEXParserPath + "lib/x64/VS2015/Release/");

							PublicAdditionalLibraries.Add("opengex-parser_Release.lib");
						}
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