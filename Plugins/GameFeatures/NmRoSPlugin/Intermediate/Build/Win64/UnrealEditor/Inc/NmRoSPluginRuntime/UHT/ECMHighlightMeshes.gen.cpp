// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NmRoSPluginRuntime/Character/ECMHighlightMeshes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeECMHighlightMeshes() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UMeshComponent_NoRegister();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHighlightMeshes();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHighlightMeshes_NoRegister();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHightlightInterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_NmRoSPluginRuntime();
// End Cross Module References
	void UECMHighlightMeshes::StaticRegisterNativesUECMHighlightMeshes()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UECMHighlightMeshes);
	UClass* Z_Construct_UClass_UECMHighlightMeshes_NoRegister()
	{
		return UECMHighlightMeshes::StaticClass();
	}
	struct Z_Construct_UClass_UECMHighlightMeshes_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_MeshComponents_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshComponents_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MeshComponents;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UECMHighlightMeshes_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_NmRoSPluginRuntime,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UECMHighlightMeshes_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Character/ECMHighlightMeshes.h" },
		{ "ModuleRelativePath", "Character/ECMHighlightMeshes.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents_Inner = { "MeshComponents", nullptr, (EPropertyFlags)0x0004000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Character/ECMHighlightMeshes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents = { "MeshComponents", nullptr, (EPropertyFlags)0x0044008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UECMHighlightMeshes, MeshComponents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents_MetaData), Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UECMHighlightMeshes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UECMHighlightMeshes_Statics::NewProp_MeshComponents,
	};
		const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UECMHighlightMeshes_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UECMHightlightInterface_NoRegister, (int32)VTABLE_OFFSET(UECMHighlightMeshes, IECMHightlightInterface), false },  // 1356048116
		};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::InterfaceParams) < 64);
	const FCppClassTypeInfoStatic Z_Construct_UClass_UECMHighlightMeshes_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UECMHighlightMeshes>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UECMHighlightMeshes_Statics::ClassParams = {
		&UECMHighlightMeshes::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UECMHighlightMeshes_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::Class_MetaDataParams), Z_Construct_UClass_UECMHighlightMeshes_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightMeshes_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UECMHighlightMeshes()
	{
		if (!Z_Registration_Info_UClass_UECMHighlightMeshes.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UECMHighlightMeshes.OuterSingleton, Z_Construct_UClass_UECMHighlightMeshes_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UECMHighlightMeshes.OuterSingleton;
	}
	template<> NMROSPLUGINRUNTIME_API UClass* StaticClass<UECMHighlightMeshes>()
	{
		return UECMHighlightMeshes::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UECMHighlightMeshes);
	UECMHighlightMeshes::~UECMHighlightMeshes() {}
	struct Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Character_ECMHighlightMeshes_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Character_ECMHighlightMeshes_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UECMHighlightMeshes, UECMHighlightMeshes::StaticClass, TEXT("UECMHighlightMeshes"), &Z_Registration_Info_UClass_UECMHighlightMeshes, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UECMHighlightMeshes), 3847436058U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Character_ECMHighlightMeshes_h_2235170797(TEXT("/Script/NmRoSPluginRuntime"),
		Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Character_ECMHighlightMeshes_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Character_ECMHighlightMeshes_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
