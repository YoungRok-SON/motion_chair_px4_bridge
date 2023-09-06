#include "util.hpp"

void errorHandling(std::string  message) {
    std::cout << message << std::endl;
	exit(1);
}

void sendDataToServer(double d_roll_deg, double d_pitch_deg)
{
    double m_d_roll_deg = d_roll_deg * RAD2DEG;
    double m_d_pitch_deg = d_pitch_deg * RAD2DEG;
    // double m_d_yaw_deg = m_d_yaw_rad * RAD2DEG;

    // Send to server socket!
    char c_num_1[64], c_num_2[64];
    //set a size of number n--> make number to xx.xxx
    int i_num_size_1 = 6;
    int i_num_size_2 = 6;

    if (m_d_roll_deg < 0.0)
        i_num_size_1++;
    if (m_d_pitch_deg < 0.0)
        i_num_size_2++;
    if( abs(m_d_roll_deg) > 10.000)
        i_num_size_1++;
    if( abs(m_d_pitch_deg) > 10.000)
        i_num_size_2++;

    // make double nuber to char array for sending data.
    snprintf(c_num_1, i_num_size_1, "%f", m_d_roll_deg);
    snprintf(c_num_2, i_num_size_2, "%f", m_d_pitch_deg);
    printf("-------\nchar Num1: %s  ", c_num_1);
    printf("char Num2: %s \n", c_num_2);    
    strcat(c_num_1, m_c_spacer);
    strcat(c_num_1,c_num_2);
    
    //sendmsg 보내고 recvmsg에 수신된 string 데이터 담기
    write(m_i_client_socket, c_num_1, sizeof(c_num_1));
    int m_i_read_str_length = read(m_i_client_socket, m_c_recv_msg, sizeof(m_c_recv_msg)-1);
}


void motionDataCallback(const geometry_msgs::PoseStamped::ConstPtr &cptr_pose_stamped_data)
{

    // Conver quaternion to euler.  
    double d_roll_rad = 0, d_pitch_rad = 0, d_yaw_rad = 0;

    tf::Quaternion tf_quat(cptr_pose_stamped_data->pose.orientation.x,
                           cptr_pose_stamped_data->pose.orientation.y,
                           cptr_pose_stamped_data->pose.orientation.z,
                           cptr_pose_stamped_data->pose.orientation.w);
                           
    tf::Matrix3x3 tf_matrix_orientation(tf_quat);

    tf_matrix_orientation.getRPY(d_roll_rad, d_pitch_rad, d_yaw_rad);

    ROS_INFO("Node gets sim pose data  Roll:%f  Pitch:%f  Yaw:%f",d_roll_rad, d_pitch_rad, d_yaw_rad);

    // send data to server
    sendDataToServer(d_roll_rad, d_pitch_rad);
}

bool connectToServerSocket()
{
    std::cout << "Create Socket..." << std::endl;
    //클라이언트 소켓 TCP/IP 프로토콜 생성
    m_i_client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(m_i_client_socket == -1)
    {
        errorHandling("Socket() Error!");
        return false;
    }

    std::cout << "Trying to bind to server..." << std::endl;
    //m_i_client_socket에 bind하기 위한 작업
    memset(&m_st_server_addr, 0, sizeof(m_st_server_addr));
    m_st_server_addr.sin_family = AF_INET;
    m_st_server_addr.sin_addr.s_addr = inet_addr(m_c_target_ip);
    m_st_server_addr.sin_port = htons(m_i_target_port);

    std::cout << "Trying to connect server..." << std::endl;
    // Connect()로 서버 소켓에 연결 요청
    int m_i_connect = connect( m_i_client_socket,
                               (struct sockaddr*) &m_st_server_addr,
                               sizeof(m_st_server_addr));
    
    if (m_i_connect == -1)
    {
        errorHandling("connect() Error!");
        return false;
    }

    return true;
}


int main(int argc, char **argv)
{

    // Init ros things
    ros::init(argc, argv, "motion_bridge");
    ros::NodeHandle nh;
    ros::Subscriber sub_pose_sim_data = nh.subscribe("/mavros/local_position/pose", 1, motionDataCallback);

    // Init with tcp/ip socket communication things
    if (connectToServerSocket() == false)
    {
        ROS_ERROR("Connection to Server is not availiable.");
        return -1;
    }

    ros::spin();

    close(m_i_client_socket);
    return 0;
}
