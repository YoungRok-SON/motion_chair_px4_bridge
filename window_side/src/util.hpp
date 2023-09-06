#ifndef __Util_HPP__
#define __Util_HPP__

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string>

#include <WinSock2.h>
#include <Windows.h>

// Motion House library import
#include "MHDLL.h"
#include "MHSDKDLL.h"


WSADATA m_wsaData; // for what?
SOCKET m_h_server_sock, m_h_client_sock;
SOCKADDR_IN m_server_addr, m_client_addr;

int m_i_size_client_addr;
char m_c_message[64];
int m_i_str_length;



#endif //__Util_HPP__