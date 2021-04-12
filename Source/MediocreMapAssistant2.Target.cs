// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MediocreMapAssistant2Target : TargetRules
{
	public MediocreMapAssistant2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        
        ExtraModuleNames.AddRange( new string[] { "MediocreMapAssistant2" } );
	}
}
