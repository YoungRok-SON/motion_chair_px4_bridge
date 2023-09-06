#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

// Debugging
#include <random>

#define PORT 7777
#define BUF_SIZE 1024

void ErrorHandling(std::string message);

int main(void)
{
    //클라이언트 소켓 파일디스크립터 변수 선언
    int m_i_client_socket;

    // sockaddr_in 구조체 변수 선언
    struct sockaddr_in st_server_addr;

    //보내고 받을 버퍼 정의
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
    
    // Random float nuber 생성
    // For debugging
    std::random_device random_device;
    std::mt19937 gen1(random_device());
    std::uniform_real_distribution<> dist1(0, 20);
    std::uniform_real_distribution<> dist2(0, -20);

    char c_spacer[] = ",";
    while(1)
    {

        float f_num1 = dist1(gen1);
        float f_num2 = dist2(gen1);

        // std::cout << "num 1:" << dist1(gen1) << "  num2: " << dist2(gen1) << std::endl;
        printf("Num1: %f  ", f_num1);
        printf("Num2: %f \n", f_num2);
        // num1 + "," + num2
        char c_num_1[64], c_num_2[64];
        //set a size of number
        int i_num_size_1 = 6;
        int i_num_size_2 = 6;

        if (f_num1 < 0.0)
            i_num_size_1++;
        if (f_num2 < 0.0)
            i_num_size_2++;
        if( abs(f_num1) > 10.000)
            i_num_size_1++;
        if( abs(f_num2) > 10.000)
            i_num_size_2++;

        snprintf(c_num_1, i_num_size_1, "%f", f_num1);
        snprintf(c_num_2, i_num_size_2, "%f", f_num2);
        printf("-------\nchar Num1: %s  ", c_num_1);
        printf("char Num2: %s \n", c_num_2);

        std::cout <<"Size of only one num: " << sizeof(c_num_1) << std::endl;
        
        strcat(c_num_1, c_spacer);
        strcat(c_num_1,c_num_2);
        std::cout <<"Size of combined char: " << sizeof(c_num_1) << std::endl;
        // printf("-------\nCombined char: %s  ", c_num_1);
        //sendmsg 보내고 recvmsg에 수신된 string 데이터 담기
        write(m_i_client_socket, c_num_1, sizeof(c_num_1));
        int m_i_read_str_length = read(m_i_client_socket, m_c_recv_msg, sizeof(m_c_recv_msg)-1);

    }
    
    close(m_i_client_socket);

    return 0;
}

void ErrorHandling(std::string  message) {
    std::cout << message << std::endl;
	exit(1);
}