// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OpenGEXImporter : ModuleRules
	{
		public OpenGEXImporter(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
                    "MainFrame"
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Core",
				    "CoreUObject",
				    "Engine",
				    "Slate",
					"SlateCore",
                    "EditorStyle",
                    "InputCore",
				    "RawMesh",
                    "UnrealEd",
                    "MainFrame"
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
				}
				);
				
			PrivateDependencyModuleNames.Add("OpenDDLParser");

            PrivateDependencyModuleNames.Add("OpenGEXParser");
		}
	}
}