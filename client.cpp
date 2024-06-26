#include <iostream>
#include <winsock2.h>
#include <winsock.h>

int main(int argc, char **argv)
{

//Initializing winsock
    WSADATA ws_data;
    WORD w_version_requested = MAKEWORD(2, 2);
    int c_working = WSAStartup(w_version_requested, &ws_data);

    if (c_working == SOCKET_ERROR)
    {
        return -1;
    }

//Filling information needed to initialize a socket
    struct sockaddr_in client_s;
    client_s.sin_family = AF_INET;
    client_s.sin_port = htons(6500);
    client_s.sin_addr.s_addr = inet_addr("127.0.0.1");

//Creating socket
    SOCKET c = socket(AF_INET, SOCK_STREAM, 0);
    
    if (c == INVALID_SOCKET)
    {
        return -2;
    }

//Connecting
    if  (connect(c, (SOCKADDR *)&client_s, sizeof(client_s)) == SOCKET_ERROR)
    {
        return -3;
    }

//sending and recieving
    char request [32768];
    std::string user_input;

    do 
    {
        std::cout << "> ";
        getline (std::cin, user_input);

        if (user_input.size() > 0)
        {
            int send_message = send(c, user_input.c_str(), user_input.size() + 1, 0);

            if (send_message != SOCKET_ERROR)
            {
                ZeroMemory (request, 32768);
                int message_recieved = recv(c, request, 32768, 0);

                if (message_recieved > 0)
                {
                    std::cout << "<Server::Seen> " << std::string (request, 0, message_recieved) << std::endl;
                }
            }
        }
    } while (user_input.size() > 0);

//closing connection
    closesocket(c);

//General clean-up drive
    WSACleanup();
}