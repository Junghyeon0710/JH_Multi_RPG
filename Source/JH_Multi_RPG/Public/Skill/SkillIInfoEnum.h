#pragma once

UENUM(BlueprintType)
enum class ESkillName : uint8
{
	ESN_Default UMETA(DisplayName = "Default"),
	ESN_Skill1 UMETA(DisplayName = "Skill1"),
	ESN_Skill2 UMETA(DisplayName = "Skill2"),
	ESN_Skill3 UMETA(DisplayName = "Skill3"),
	ESN_Skill4 UMETA(DisplayName = "Skill4"),
	ESN_Skill5 UMETA(DisplayName = "Skill5"),
	ESN_Skill6 UMETA(DisplayName = "Skill6"),
	ESN_Skill7 UMETA(DisplayName = "Skill7"),
	ESN_Skill8 UMETA(DisplayName = "Skill8"),
};


UENUM(BlueprintType)
enum class ESkillInput : uint8
{
	ESI_Default UMETA(DisplayName = "Default"),
	ESI_InputQ UMETA(DisplayName = "InputQ"),
	ESI_InputW UMETA(DisplayName = "InputW"),
	ESI_InputE UMETA(DisplayName = "InputE"),
	ESI_InputR UMETA(DisplayName = "InputR"),
	ESI_InputA UMETA(DisplayName = "InputA"),
	ESI_InputS UMETA(DisplayName = "InputS"),
	ESI_InputD UMETA(DisplayName = "InputD"),
	ESI_InputF UMETA(DisplayName = "InputF")
};