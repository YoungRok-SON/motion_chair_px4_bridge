#include <iostream>
#include <stdio.h>
#include <Windows.h>
// Motion House library import
#include "../x64/Debug/MHDLL.h"
#include "../x64/Debug/MHSDKDLL.h"


int main()
{
	std::cout << "Fuck You ~ Window ~." << std::endl;


	int i_run_result = MHRun();
	if(i_run_result != MHSERVICE_INIT_SUCCESS )
	{ 
		MHStop();
		printf("MotionHouse SDK initialization fail, ErrorCode: %d \n", i_run_result);
		return -1;
	}

	MotionControlStart();
	Sleep(900);


	float f_pitch_degree = 10.;
	float f_wind = 100;

	for( int idx = 0; idx < 20; idx++)
	{
		if(idx % 2 == 1)
		{
			f_pitch_degree = 10.;
			f_wind = f_wind + 0.5;
		}

		if (idx % 2 == 0)
		{
			f_pitch_degree = -10.;
			f_wind = f_wind + 0.5;
		}

		SetDllMotionTelemetry(1, 0, f_pitch_degree * 3.141592 / 180, 0, 0, 0, 0, 0);
		std::cout << "Pitch changed to degree: " << f_pitch_degree << std::endl;
		Sleep(1000);
	}


	for (int idx = 0; idx < 20; idx++)
	{
		if (idx % 2 == 1)
		{
			f_pitch_degree = 10.;
			f_wind = f_wind + 0.5;
		}

		if (idx % 2 == 0)
		{
			f_pitch_degree = -10.;
			f_wind = f_wind + 0.5;
		}

		SetDllMotionTelemetry(1, f_pitch_degree * 3.141592 / 180, 0, 0, 0, 0, 0, 0);
		std::cout << "ROLL changed to degree: " << f_pitch_degree << std::endl;
		Sleep(1000);
	}


	MotionControlEnd();
	MHStop();

	std::cout << "Motion Actuator Test is done." << std::endl;

	return 1;
}
