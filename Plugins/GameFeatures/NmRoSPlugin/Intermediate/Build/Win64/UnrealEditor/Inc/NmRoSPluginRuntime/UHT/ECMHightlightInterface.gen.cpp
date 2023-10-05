// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NmRoSPluginRuntime/Interaction/ECMHightlightInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeECMHightlightInterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHightlightInterface();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHightlightInterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_NmRoSPluginRuntime();
// End Cross Module References
	void UECMHightlightInterface::StaticRegisterNativesUECMHightlightInterface()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UECMHightlightInterface);
	UClass* Z_Construct_UClass_UECMHightlightInterface_NoRegister()
	{
		return UECMHightlightInterface::StaticClass();
	}
	struct Z_Construct_UClass_UECMHightlightInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UECMHightlightInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_NmRoSPluginRuntime,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHightlightInterface_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UECMHightlightInterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Interaction/ECMHightlightInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UECMHightlightInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IECMHightlightInterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UECMHightlightInterface_Statics::ClassParams = {
		&UECMHightlightInterface::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000840A1u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHightlightInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UECMHightlightInterface_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UECMHightlightInterface()
	{
		if (!Z_Registration_Info_UClass_UECMHightlightInterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UECMHightlightInterface.OuterSingleton, Z_Construct_UClass_UECMHightlightInterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UECMHightlightInterface.OuterSingleton;
	}
	template<> NMROSPLUGINRUNTIME_API UClass* StaticClass<UECMHightlightInterface>()
	{
		return UECMHightlightInterface::StaticClass();
	}
	UECMHightlightInterface::UECMHightlightInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UECMHightlightInterface);
	UECMHightlightInterface::~UECMHightlightInterface() {}
	struct Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Interaction_ECMHightlightInterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Interaction_ECMHightlightInterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UECMHightlightInterface, UECMHightlightInterface::StaticClass, TEXT("UECMHightlightInterface"), &Z_Registration_Info_UClass_UECMHightlightInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UECMHightlightInterface), 1356048116U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Interaction_ECMHightlightInterface_h_3386339715(TEXT("/Script/NmRoSPluginRuntime"),
		Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Interaction_ECMHightlightInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Interaction_ECMHightlightInterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
