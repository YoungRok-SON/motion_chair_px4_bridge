#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <WinSock2.h>

// 아래 사이트 참고
//https://aronglife.tistory.com/entry/NetworkTCPIP-%EC%86%8C%EC%BC%93%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D4%EC%9C%88%EB%8F%84%EC%9A%B0-%EC%84%9C%EB%B2%84-%EA%B5%AC%ED%98%84

void ErrorHandling(std::string message);

int main(int argc, char *argv[])
{
    WSADATA m_wsaData; // for what?
    SOCKET m_h_server_sock, m_h_client_sock;
    SOCKADDR_IN m_server_addr, m_client_addr;

    int m_i_size_client_addr;
    char m_c_message[30];
    int m_i_str_length;

    std::cout << "Socket has initialized..." << std::endl;
    if (argc != 2)
    {
        printf("Usage:%s <port>\n", argv[0]);
        exit(1);
    }

    // 소켓 라이브러리 초기화
    if ( WSAStartup(MAKEWORD(2,2), &m_wsaData) != 0)
        ErrorHandling("WSAStartup() Error!");
    
    std::cout << "Create Socket..." << std::endl;
    m_h_server_sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성
    if( m_h_server_sock == INVALID_SOCKET )
        ErrorHandling("SOCKET() Error!");
    
    
    memset(&m_server_addr, 0, sizeof(m_server_addr));
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    m_server_addr.sin_port = htons(atoi(argv[1]));

    if( bind(m_h_server_sock, (struct sockaddr*) & m_server_addr, sizeof(m_server_addr))==SOCKET_ERROR) // 소켓에 IP주소와 PORT 번호 할당
        ErrorHandling("bind() Error!");
    if( listen(m_h_server_sock, 5) == SOCKET_ERROR ) // listen 함수호출을 통해 생성한 소켓을 서버 소켓으로 완성
        ErrorHandling("listen() error");
    
    std::cout << "Socket has created... Wait for client... " << std::endl;
    m_i_size_client_addr = sizeof(m_client_addr);
    m_h_client_sock = accept(m_h_server_sock, (struct sockaddr*)&m_client_addr, &m_i_size_client_addr);  //클라이언트 연결요청 수락하기 위해 accept함수 호출
    if( m_h_client_sock == INVALID_SOCKET)
        ErrorHandling("accept() Error!");

    while(1)
    {
        memset(m_c_message, '\0', 30);
        m_i_str_length = recv(m_h_client_sock, m_c_message, sizeof(m_c_message)-1, 0);
        if( m_i_str_length == -1)
            ErrorHandling("read() error!");
        
        printf("Meassage from client: %s \n", m_c_message);
        printf("Insert your message >> ");
        gets_s(m_c_message);
        send(m_h_client_sock, m_c_message, strlen(m_c_message)+1, 0);
    }

    closesocket(m_h_client_sock);
    closesocket(m_h_server_sock);
    WSACleanup();    //프로그램 종료 전에 초기화한 소켓 라이브러리 해제


    return 0;
}

void ErrorHandling(std::string  message) {
    std::cout << message << std::endl;
	exit(1);
}