#include <iostream>
#include <winsock2.h>
#include <winsock.h>

int main (int argc, char **argv)
{

//Initializing winsock
    WSADATA ws_data;
    WORD w_version_requested = MAKEWORD(2, 2);
    int s_working = WSAStartup(w_version_requested, &ws_data);

    if (s_working == SOCKET_ERROR)
    {
        return -5;
    }

//Information for socket initialization
    struct sockaddr_in server_s;
    server_s.sin_family = AF_INET;
    server_s.sin_port = htons(6500);
    server_s.sin_addr.s_addr = htonl(INADDR_ANY);

//Creating socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    
    if (s == INVALID_SOCKET)
    {
        return -6;
    }

//Binding port and socket
    int bind_p_s = bind(s, (sockaddr *)&server_s, sizeof(server_s));

    if (bind_p_s < 0)
    {
        return -7;
    }

//Listen
    int ear = listen(s, SOMAXCONN);

    if (ear < 0)
    {
        return -8;
    }

//accept
    struct sockaddr_in client_s;
    int client_s_length = sizeof(client_s);
    int c_connect_s = accept(s, (sockaddr *)&client_s, &client_s_length);

    if (c_connect_s == false)
    {
        return -9;
    }

//acccepting and echoing back
    char s_buff [32768];

    while (true)
    {
        ZeroMemory (s_buff, 32768);

        int client_message_recieved = recv(c_connect_s, s_buff, 32768, 0);

        if (client_message_recieved > 0)
        {
            std::cout << "> User Message: " << std::string (s_buff, 0, client_message_recieved) << std::endl;
        }

        if (client_message_recieved == SOCKET_ERROR)
        {
            std::cout << "Error in recv()" << std::endl;
            break;
        }

        if (client_message_recieved == 0)
        {
            std::cout << "Client Disconnected " << std::endl;
            break;
        }

        send(c_connect_s, s_buff, client_message_recieved + 1, 0);
        
    }

//closing
closesocket(s);

//General cleaning
WSACleanup();

}