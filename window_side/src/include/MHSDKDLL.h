#include "MHDLL.h"
#include "MHTelemetryInfoInterface.h"

#define DLLExport  __declspec(dllexport)

extern "C"
{
	DLLExport int MHRun();
	DLLExport void MHStop();
	DLLExport int GetMHSDKVersion();

	DLLExport int GetDeviceVersion(int index);
	DLLExport int GetConnectedDeviceCount();
	DLLExport int GetDeviceStatus(int index);
	DLLExport int GetConnectedDeviceType(int index);

	DLLExport void MotionControlStart();
	DLLExport void MotionControlEnd();
	DLLExport int GetCenterCode(int deviceType);

	DLLExport int SetMotionDeviceConfig(
		//int m_TestFlag,		//mline 사고체험 임시
		bool m_UseFlag,
		int m_DeviceType,
		int m_DeviceControlDelay,

		double m_MaxRoll,
		double m_MaxPitch,
		double m_MaxTractionLoss,
		double m_MaxSway,
		double m_MaxSurge,
		double m_MaxHeave
	);

	DLLExport int GetMotionDeviceConfig(
		int m_DeviceType,

		double* m_MaxRoll,
		double* m_MaxPitch,
		double* m_MaxTractionLoss,
		double* m_MaxSway,
		double* m_MaxSurge,
		double* m_MaxHeave
	);

	DLLExport int SetWindDeviceConfig(
		//int m_TestFlag,		//mline 사고체험 임시
		bool m_UseFlag,
		int m_DeviceType,
		int m_DeviceControlDelay
	);


	DLLExport int SetMotionProfile(
		int m_DeviceType,
		bool m_UseFlag,
		bool m_UseRoll,
		int m_RollWeight,

		bool m_UsePitch,
		int m_PitchWeight,

		bool m_UseSway,
		int m_SwayWeight,

		bool m_UseSurge,
		int m_SurgeWeight,

		bool m_UseHeave,
		int m_HeaveWeight,
		bool m_UseTractionLoss,
		int m_TractionLossWeight,

		int m_ActuratorAccel,
		int m_ActuratorMaxSpeed,
		int m_ActuratorVibration,
		int m_ActuratorSmooth
	);

	DLLExport int SetMotionFilter(
		int m_DeviceType,
		int m_RollFilter,
		int m_PitchFilter,
		int m_SwayFilter,
		int m_SurgeFilter,
		int m_HeaveFilter,
		int m_TLFilter
		//,					//mline 사고체험 임시
		//int m_SusFilter,//mline 사고체험 임시
		//int m_AccelFilter//mline 사고체험 임시
	);

	DLLExport int SetWindProfile(
		int m_DeviceType,
		bool m_UseFlag,
		int m_BaseOffset,
		int m_Min,
		int m_Max,
		int m_MaxPower
	);


	DLLExport bool SetDllMotionTelemetry(int motionState
		, float roll
		, float pitch
		, float sway
		, float surge
		, float heave
		, float yaw
		, float wind);


	DLLExport void RequestReadyState();
	DLLExport bool IsReadyState();

	DLLExport void RequestSleepState();
	DLLExport bool IsSleepState();

	DLLExport int IsWindDeviceType(int deviceType);
	DLLExport int IsMotionDeviceType(int deviceType);

	DLLExport int GetMotionProfile(
		int m_DeviceType,
		bool& m_UseFlag,

		bool& m_UseMinusSurge,
		float& m_MinusSurge,

		bool& m_UseRoll,
		int& m_RollWeight,

		bool& m_UsePitch,
		int& m_PitchWeight,

		bool& m_UseSway,
		int& m_SwayWeight,

		bool& m_UseSurge,
		int& m_SurgeWeight,

		bool& m_UseHeave,
		int& m_HeaveWeight,

		bool& m_UseSuspension,
		int& m_SuspensionWeight,

		bool& m_UseTractionLoss,
		int& m_TractionLossWeight,

		int& m_ActuratorAccel,
		int& m_ActuratorMaxSpeed,
		int& m_ActuratorVibration,
		int& m_ActuratorSmooth
	);

	DLLExport void SetSDKPath(char* path);
	DLLExport bool SetIniPath(char* path);

	DLLExport bool SetDllMotionTelemetryEx(MHTelemetryInfoInterface info);
	DLLExport int GetSafetyBeltStatus();

	DLLExport int StartTelemetryLogging();
	DLLExport int StopTelemetryLogging();

	DLLExport int SetAxisControlMode(int deviceType, int mode);

	//DLLExport int SetAxisPositions(int deviceType, TargetAxisPosition data);
	//DLLExport int SetAxisPositionVibration(int deviceType, TargetAxisPosition data);

	//DLLExport int CheckAxisPositions(int deviceType, AxisPositionCheck data);
	DLLExport int GetAxisCount(int deviceType);

	DLLExport void ClearDeviceErrorCode(int deviceType, int errorCode);
	DLLExport int SetModuleUseFlag(int index, int flag);

	DLLExport int MotionPlayerState();
	DLLExport int LoadMotionFile();
	DLLExport int GetLoadedMotionFileName(int index, char* name, int* length);
	DLLExport int ReadyToPlay(char* file);
	DLLExport int PlayMotionFile(char* file);
	DLLExport int PauseMotionFile();
	DLLExport int StopMotionFile();
	DLLExport int SetPlayPosition(int position);
	DLLExport int GetPlayPosition();


	DLLExport int DeviceForcePowerOn(int deviceType, int on);

	DLLExport void SetDCCCCommand(int deviceType, int command);
	DLLExport int GetDCCCState(int deviceType);

	DLLExport void MotionDeviceStart(int deviceType);
	DLLExport void MotionDeviceEnd(int deviceType);
	DLLExport void HoldPosition(int deviceType, int flag);

	DLLExport int GetSeatPositionControllerState();
	DLLExport int SetSeatPosition(int slide, int recline, int seatFront, int seatRear);

	DLLExport int GetTorqueControllerPosition();

	DLLExport void MotionControl(bool isStart, int deviceType);


	//Preload MotionPlayer
	DLLExport bool SetPreloadMotionPlayer(int deviceType, int motionDataCountPerSec);

	DLLExport bool StartPreloadMotionPlayer(int deviceType);
	DLLExport bool StopPreloadMotionPlayer(int deviceType);
	DLLExport bool PausePreloadMotionPlayer(int deviceType);

	//DLLExport int AddPreloadBuffer(int deviceType, PreloadMotionData* data);
	DLLExport int ClearPreloadBuffer(int deviceType);
	DLLExport int LoadCompletePreloadBuffer(int deviceType);
}