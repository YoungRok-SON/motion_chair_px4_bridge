#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define BUF_SIZE 1024

void ErrorHandling(std::string message);

int main(void)

    //클라이언트 소켓 파일디스크립터 변수 선언
    int m_i_client_socket;

    // sockaddr_in 구조체 변수 선언
    struct sockaddr_in st_server_addr;

    //보내고 받을 버퍼 정의
    char m_c_send_msg[] = "Test_client";
    char m_c_recv_msg[BUF_SIZE];

    //ip, port 정의
    char m_c_target_ip[] = "172.21.240.1";
    int  m_i_target_port = 7777;

    std::cout << "Create Socket..." << std::endl;
    //클라이언트 소켓 TCP/IP 프로토콜 생성
    m_i_client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(m_i_client_socket == -1)
        ErrorHandling("Socket() Error!");
    
    std::cout << "Trying to bind to server..." << std::endl;
    //m_i_client_socket에 bind하기 위한 작업
    memset(&st_server_addr, 0, sizeof(st_server_addr));
    st_server_addr.sin_family = AF_INET;
    st_server_addr.sin_addr.s_addr = inet_addr(m_c_target_ip);
    st_server_addr.sin_port = htons(m_i_target_port);

    std::cout << "Trying to connect server..." << std::endl;
    // Connect()로 서버 소켓에 연결 요청
    int m_i_connect = connect( m_i_client_socket,
                               (struct sockaddr*) &st_server_addr,
                               sizeof(st_server_addr));
    
    if (m_i_connect == -1)
        ErrorHandling("connect() Error!");
    
    while(1)
    {
        //sendmsg 보내고 recvmsg에 수신된 string 데이터 담기
    write(m_i_client_socket, m_c_send_msg, sizeof(m_c_send_msg));
    int m_i_read_str_length = read(m_i_client_socket, m_c_recv_msg, sizeof(m_c_recv_msg)-1);
    std::cout << "Received Message: " << m_c_recv_msg << std::endl;

    }
    
    close(m_i_client_socket);

    return 0;
}

void ErrorHandling(std::string  message) {
    std::cout << message << std::endl;
	exit(1);
}