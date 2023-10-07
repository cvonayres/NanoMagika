// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NmRoSPluginRuntime/Player/NmRoSPlayerController.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNmRoSPlayerController() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	NANOMAGIKA_API UClass* Z_Construct_UClass_AECMPlayerController();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_ANmRoSPlayerController();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_ANmRoSPlayerController_NoRegister();
	UPackage* Z_Construct_UPackage__Script_NmRoSPluginRuntime();
// End Cross Module References
	void ANmRoSPlayerController::StaticRegisterNativesANmRoSPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANmRoSPlayerController);
	UClass* Z_Construct_UClass_ANmRoSPlayerController_NoRegister()
	{
		return ANmRoSPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ANmRoSPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CursorHit_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CursorHit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_MoveAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ShortPressThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ShortPressThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AutoRunAcceptanceRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AutoRunAcceptanceRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Spline_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Spline;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANmRoSPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AECMPlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_NmRoSPluginRuntime,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/NmRoSPlayerController.h" },
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_CursorHit_MetaData[] = {
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_CursorHit = { "CursorHit", nullptr, (EPropertyFlags)0x0040008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANmRoSPlayerController, CursorHit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_CursorHit_MetaData), Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_CursorHit_MetaData) }; // 1891709922
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANmRoSPlayerController, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_MoveAction_MetaData), Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_MoveAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_ShortPressThreshold_MetaData[] = {
		{ "Category", "MoveByCick" },
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_ShortPressThreshold = { "ShortPressThreshold", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANmRoSPlayerController, ShortPressThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_ShortPressThreshold_MetaData), Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_ShortPressThreshold_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_AutoRunAcceptanceRadius_MetaData[] = {
		{ "Category", "MoveByCick" },
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_AutoRunAcceptanceRadius = { "AutoRunAcceptanceRadius", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANmRoSPlayerController, AutoRunAcceptanceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_AutoRunAcceptanceRadius_MetaData), Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_AutoRunAcceptanceRadius_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_Spline_MetaData[] = {
		{ "Category", "MoveByCick" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/NmRoSPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_Spline = { "Spline", nullptr, (EPropertyFlags)0x00440000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANmRoSPlayerController, Spline), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_Spline_MetaData), Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_Spline_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANmRoSPlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_CursorHit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_MoveAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_ShortPressThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_AutoRunAcceptanceRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANmRoSPlayerController_Statics::NewProp_Spline,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANmRoSPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANmRoSPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ANmRoSPlayerController_Statics::ClassParams = {
		&ANmRoSPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ANmRoSPlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ANmRoSPlayerController_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANmRoSPlayerController_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ANmRoSPlayerController()
	{
		if (!Z_Registration_Info_UClass_ANmRoSPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANmRoSPlayerController.OuterSingleton, Z_Construct_UClass_ANmRoSPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ANmRoSPlayerController.OuterSingleton;
	}
	template<> NMROSPLUGINRUNTIME_API UClass* StaticClass<ANmRoSPlayerController>()
	{
		return ANmRoSPlayerController::StaticClass();
	}
	ANmRoSPlayerController::ANmRoSPlayerController() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANmRoSPlayerController);
	ANmRoSPlayerController::~ANmRoSPlayerController() {}
	struct Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ANmRoSPlayerController, ANmRoSPlayerController::StaticClass, TEXT("ANmRoSPlayerController"), &Z_Registration_Info_UClass_ANmRoSPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANmRoSPlayerController), 3198530159U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSPlayerController_h_3375784413(TEXT("/Script/NmRoSPluginRuntime"),
		Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_NmRoSPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
