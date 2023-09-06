#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/tf.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 7777
#define BUF_SIZE 1024
#define RAD2DEG 180.0/M_PI

//클라이언트 소켓 파일디스크립터 변수 선언
int m_i_client_socket;

// sockaddr_in 구조체 변수 선언
struct sockaddr_in m_st_server_addr;

//보내고 받을 버퍼 정의
char m_c_recv_msg[BUF_SIZE];

//ip, port 정의
char m_c_target_ip[] = "172.21.240.1";
int  m_i_target_port = 7777;

char m_c_spacer[] = ",";\

#endif //__UTIL_HPP__