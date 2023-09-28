// Copyright Electronic CAD Monkey [ECM]


#include "ECMPlayerCameraManager.h"
#include "ECMPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

AECMPlayerCameraManager::AECMPlayerCameraManager()
{
}

void AECMPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void AECMPlayerCameraManager::InitCamera()
{
	Controller = CastChecked<AECMPlayerController>(GetOwningPlayerController());

	if(Controller) 
	{
		ControlledPawn = Controller->GetPawn<APawn>();
	}

	// Assign default view and rotation based on view mode
	if (Controller->ViewMode == EViewMode::FPV)
	{
		VOffset = FPVOffset;
		ROffset = FPVRotation;
	}
	else if(Controller->ViewMode  == EViewMode::TPV)
	{
		VOffset = TPVOffset;
		ROffset = TPVRotation;
	}
	else if(Controller->ViewMode  == EViewMode::TDV)
	{
		VOffset = TDVOffset;
		ROffset = TDVRotation;
	}
}

// Called in BP on camera update
FVector AECMPlayerCameraManager::GetUpdatedLocation() const
{
	if(!Controller) return VOffset;

	if (Controller)
	{
		const FVector OffsetX = VOffset.X * GetCameraVector(EVectorDirection::Fwd);
	//	const FVector OffsetY = VOffset.Y * GetCameraVector(EVectorDirection::Right);
	//	const FVector OffsetZ = VOffset.Z * GetCameraVector(EVectorDirection::Up);

		if (ControlledPawn)
		{
			const FVector NewLocation = ControlledPawn->GetActorLocation() + OffsetX;// + OffsetY + OffsetZ;
			//Test = OffsetX;
			return NewLocation;
		}
	}
	return VOffset;
}
FRotator AECMPlayerCameraManager::GetUpdatedRotation() const
{
	if(!Controller) return ROffset;

	if(Controller->ViewMode  == EViewMode::FPV)
	{
		return GetOwningPlayerController()->GetControlRotation();
	}
	else if(Controller->ViewMode  == EViewMode::TPV)
	{
		return GetOwningPlayerController()->GetControlRotation();
	}
	else if(Controller->ViewMode  == EViewMode::TDV)
	{
		return ROffset;
	}
	return ROffset;
}

// Bound to Action in Player Controller
void AECMPlayerCameraManager::UpdateZoom(const float valve)
{
	if(!ZoomCurve) return ;

	const float CurveValve = -(ZoomCurve->GetFloatValue(valve));
	const FVector Adjustment = GetCameraVector(EVectorDirection::Fwd) * CurveValve;
	VOffset = ClampVector(VOffset + Adjustment,ZoomMIN,ZoomMAX);
}

// Gets forward, right or Up vector from camera rotation
FVector AECMPlayerCameraManager::GetCameraVector(const EVectorDirection Direction) const
{
	FVector Vector;
	if(Direction == EVectorDirection::Fwd)
	{
		Vector = UKismetMathLibrary::GetForwardVector(GetCameraRotation());
	}
	else if(Direction == EVectorDirection::Right)
	{
		Vector = UKismetMathLibrary::GetRightVector(GetCameraRotation());
	}
	else if(Direction == EVectorDirection::Up)
	{
		Vector = UKismetMathLibrary::GetUpVector(GetCameraRotation());
	}
	else
	{
		Vector = FVector(0,0,0);
	}
	return Vector;
}
