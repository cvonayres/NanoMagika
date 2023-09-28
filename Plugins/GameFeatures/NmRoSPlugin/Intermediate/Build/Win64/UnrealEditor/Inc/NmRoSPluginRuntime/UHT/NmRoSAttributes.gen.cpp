// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NmRoSPluginRuntime/Player/NmRoSAttributes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNmRoSAttributes() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UNmRoSAttributes();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UNmRoSAttributes_NoRegister();
	UPackage* Z_Construct_UPackage__Script_NmRoSPluginRuntime();
// End Cross Module References
	void UNmRoSAttributes::StaticRegisterNativesUNmRoSAttributes()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNmRoSAttributes);
	UClass* Z_Construct_UClass_UNmRoSAttributes_NoRegister()
	{
		return UNmRoSAttributes::StaticClass();
	}
	struct Z_Construct_UClass_UNmRoSAttributes_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNmRoSAttributes_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_NmRoSPluginRuntime,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNmRoSAttributes_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNmRoSAttributes_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Player/NmRoSAttributes.h" },
		{ "ModuleRelativePath", "Player/NmRoSAttributes.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNmRoSAttributes_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNmRoSAttributes>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UNmRoSAttributes_Statics::ClassParams = {
		&UNmRoSAttributes::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNmRoSAttributes_Statics::Class_MetaDataParams), Z_Construct_UClass_UNmRoSAttributes_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UNmRoSAttributes()
	{
		if (!Z_Registration_Info_UClass_UNmRoSAttributes.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNmRoSAttributes.OuterSingleton, Z_Construct_UClass_UNmRoSAttributes_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UNmRoSAttributes.OuterSingleton;
	}
	template<> NMROSPLUGINRUNTIME_API UClass* StaticClass<UNmRoSAttributes>()
	{
		return UNmRoSAttributes::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNmRoSAttributes);
	UNmRoSAttributes::~UNmRoSAttributes() {}
	struct Z_CompiledInDeferFile_FID_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSAttributes_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSAttributes_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UNmRoSAttributes, UNmRoSAttributes::StaticClass, TEXT("UNmRoSAttributes"), &Z_Registration_Info_UClass_UNmRoSAttributes, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNmRoSAttributes), 2279622980U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSAttributes_h_3307607037(TEXT("/Script/NmRoSPluginRuntime"),
		Z_CompiledInDeferFile_FID_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSAttributes_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSAttributes_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
