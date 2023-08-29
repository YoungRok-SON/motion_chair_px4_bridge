#pragma once

#pragma pack(push, 4)
struct MHTelemetryInfoInterface
{
	int motionState;
	int gameId;
	float roll;
	float pitch;
	float sway;
	float surge;
	float heave;
	float yaw;
	float m_SuspensionDeflectionFR;
	float m_SuspensionDeflectionFL;
	float m_SuspensionDeflectionRR;
	float m_SuspensionDeflectionRL;
	float m_Throttle;
	float m_Brake;
	float m_Clutch;
	float m_SteeringWheelAngle;
	float m_FuelPercent;
	float m_Fuel;
	float m_MaxFuel;
	float m_Gear;
	float m_Speed;
	float m_Rpm;
	float m_MaxRpm;
	int m_Drs;
	char m_RaceStatusFlag;
	int m_Kers;
	int m_InPit;

	float m_CurrentLapTime; //Current LapTime in milliseconds[0, ¡¦]
	int m_CurrentLapCount;
	int m_CurrentRacePosition;

	float m_WorldPosX;
	float m_WorldPosY;
	float m_WorldPosZ;

	float m_SuspensionHorizon;
	float m_SuspensionVetical;

	float m_WheelSpeedFr;
	float m_WheelSpeedFl;
	float m_WheelSpeedRr;
	float m_WheelSpeedRl;

	float m_VelocityX;
	float m_VelocityY;
	float m_VelocityZ;

	float m_AngularVelocityX;
	float m_AngularVelocityY;
	float m_AngularVelocityZ;

	unsigned int m_TelemetryTime;

	float m_Wind1;
	float m_Wind2;
	float m_Wind3;

	float m_WorldYaw;
	float m_DataValidateData;
};

struct MHVibrationInfoInterface
{
	int channelDevice[4];
	int channelMode[16];
	int channelStrength[16];
};
#pragma pack(pop)
