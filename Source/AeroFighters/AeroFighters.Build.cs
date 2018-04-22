/* Copyright (C) 2018 Javier Córdoba, Juan José Corroto
* and Iván García - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the XYZ license.
*
* You should have received a copy of the XYZ license with
* this file. If not, please write to: 
*/
using UnrealBuildTool;

public class AeroFighters : ModuleRules
{
	public AeroFighters(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
