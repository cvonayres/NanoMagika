// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NmRoSPluginRuntime/Player/ECMHighlightPC.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeECMHighlightPC() {}
// Cross Module References
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	MODULARGAMEPLAY_API UClass* Z_Construct_UClass_UControllerComponent();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHighlightPC();
	NMROSPLUGINRUNTIME_API UClass* Z_Construct_UClass_UECMHighlightPC_NoRegister();
	UPackage* Z_Construct_UPackage__Script_NmRoSPluginRuntime();
// End Cross Module References
	DEFINE_FUNCTION(UECMHighlightPC::execCursorTrace)
	{
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_CursorHit);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CursorTrace(Z_Param_Out_CursorHit);
		P_NATIVE_END;
	}
	void UECMHighlightPC::StaticRegisterNativesUECMHighlightPC()
	{
		UClass* Class = UECMHighlightPC::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CursorTrace", &UECMHighlightPC::execCursorTrace },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics
	{
		struct ECMHighlightPC_eventCursorTrace_Parms
		{
			FHitResult CursorHit;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CursorHit_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CursorHit;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::NewProp_CursorHit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::NewProp_CursorHit = { "CursorHit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ECMHighlightPC_eventCursorTrace_Parms, CursorHit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::NewProp_CursorHit_MetaData), Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::NewProp_CursorHit_MetaData) }; // 1891709922
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::NewProp_CursorHit,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Player/ECMHighlightPC.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UECMHighlightPC, nullptr, "CursorTrace", nullptr, nullptr, Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::PropPointers), sizeof(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::ECMHighlightPC_eventCursorTrace_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::Function_MetaDataParams), Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::ECMHighlightPC_eventCursorTrace_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UECMHighlightPC_CursorTrace()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UECMHighlightPC_CursorTrace_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UECMHighlightPC);
	UClass* Z_Construct_UClass_UECMHighlightPC_NoRegister()
	{
		return UECMHighlightPC::StaticClass();
	}
	struct Z_Construct_UClass_UECMHighlightPC_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UECMHighlightPC_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UControllerComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_NmRoSPluginRuntime,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightPC_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UECMHighlightPC_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UECMHighlightPC_CursorTrace, "CursorTrace" }, // 2170732112
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightPC_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UECMHighlightPC_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Player/ECMHighlightPC.h" },
		{ "ModuleRelativePath", "Player/ECMHighlightPC.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UECMHighlightPC_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UECMHighlightPC>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UECMHighlightPC_Statics::ClassParams = {
		&UECMHighlightPC::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UECMHighlightPC_Statics::Class_MetaDataParams), Z_Construct_UClass_UECMHighlightPC_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UECMHighlightPC()
	{
		if (!Z_Registration_Info_UClass_UECMHighlightPC.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UECMHighlightPC.OuterSingleton, Z_Construct_UClass_UECMHighlightPC_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UECMHighlightPC.OuterSingleton;
	}
	template<> NMROSPLUGINRUNTIME_API UClass* StaticClass<UECMHighlightPC>()
	{
		return UECMHighlightPC::StaticClass();
	}
	UECMHighlightPC::UECMHighlightPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UECMHighlightPC);
	UECMHighlightPC::~UECMHighlightPC() {}
	struct Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_ECMHighlightPC_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_ECMHighlightPC_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UECMHighlightPC, UECMHighlightPC::StaticClass, TEXT("UECMHighlightPC"), &Z_Registration_Info_UClass_UECMHighlightPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UECMHighlightPC), 1859377509U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_ECMHighlightPC_h_32935865(TEXT("/Script/NmRoSPluginRuntime"),
		Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_ECMHighlightPC_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GameDev_GAS_NanoMagika_Plugins_GameFeatures_NmRoSPlugin_Source_NmRoSPluginRuntime_Player_ECMHighlightPC_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
