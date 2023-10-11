#include "util.hpp"


// To do 
// WSL PX4 연결
// Roll, Pitch 값 가져오기
// Motion SDK를 사용하여 목표값 송출

void errorHandling(std::string  message) {
	std::cout << message << std::endl;
	exit(1);
}


bool InitServer()
{

	std::cout << "Socket has initialized..." << std::endl;

	// 소켓 라이브러리 초기화
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
	{
		errorHandling("WSAStartup() Error!");
		return false;
	}
	std::cout << "Create Socket..." << std::endl;
	m_h_server_sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성
	if (m_h_server_sock == INVALID_SOCKET)
	{
		errorHandling("SOCKET() Error!");
		return false;
	}

	memset(&m_server_addr, 0, sizeof(m_server_addr));
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_server_addr.sin_port = htons(7777);

	if (bind(m_h_server_sock, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) == SOCKET_ERROR) // 소켓에 IP주소와 PORT 번호 할당
	{
		errorHandling("bind() Error!");
		return false;
	}
	if (listen(m_h_server_sock, 5) == SOCKET_ERROR) // listen 함수호출을 통해 생성한 소켓을 서버 소켓으로 완성
	{
		errorHandling("listen() error");
		return false;
	}
	std::cout << "Socket has created... Wait for client... " << std::endl;
	m_i_size_client_addr = sizeof(m_client_addr);
	m_h_client_sock = accept(m_h_server_sock, (struct sockaddr*)&m_client_addr, &m_i_size_client_addr);  //클라이언트 연결요청 수락하기 위해 accept함수 호출
	if (m_h_client_sock == INVALID_SOCKET)
	{
		errorHandling("accept() Error!");
		return false;
	}
	return true;
}



int main()
{
	std::cout << "Motion Bridge Node has started. \n" << std::endl;

	//Device Initialization
	int runResult = MHRun();
	if (runResult != MHSERVICE_INIT_SUCCESS)
	{
		MHStop();
		printf("MotionHouseSDK initialization fail, errorCode %d\n", runResult);
		return -1;
	}

	// Connect to motion chair via MotionSDK.
	MotionControlStart();
	Sleep(2000);

	// Turn on the server for communication with wsl tcp/ip port.
	if (InitServer() == false)
	{
		std::cout << "Server initialization has failed." << std::endl;
		return -1;
	}


	while (1)
	{
		memset(m_c_message, '\0', 64);
		m_i_str_length = recv(m_h_client_sock, m_c_message, sizeof(m_c_message), 0);
		if (m_i_str_length == -1)
			errorHandling("read() error!");

		//printf("Meassage from client: %s \n\n", m_c_message);
		send(m_h_client_sock, m_c_message, 64, 0);

		// 받은 문자열 자르기
		char *c_pitch_deg = NULL;
		char* c_roll_deg = strtok_s(m_c_message, ",", &c_pitch_deg);
		//printf("Roll: %s Pitch: %s \n", c_roll_deg, c_pitch_deg);

		// 받은 char array를 float으로 변환
		float f_roll_deg = atof(c_roll_deg);
		float f_pitch_deg = atof(c_pitch_deg);
		printf("Roll: %f Pitch: %f \n", f_roll_deg, f_pitch_deg);

		// motionSDK를 사용하여 롤, 피치값 전송.
		SetDllMotionTelemetry(1, -f_roll_deg * 3.141592 / 180/2, -f_pitch_deg * 3.141592 / 180/2, 0, 0, 0, 0, 0);
		
	}

	// motionSDK delete
	MotionControlEnd();
	MHStop();
	// Socket 해제
	closesocket(m_h_client_sock);
	closesocket(m_h_server_sock);
	WSACleanup();    //프로그램 종료 전에 초기화한 소켓 라이브러리 해제

	std::cout << "Motion Actuator Test is done." << std::endl;

	return 1;
}