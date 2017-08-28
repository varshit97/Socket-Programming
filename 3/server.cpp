// // Server1 and Client1
#include <bits/stdc++.h>
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#define PORT 8890

using namespace std;

static void
broadcast(const char *mess)
{
    struct sockaddr_in s;

    if(broadcastSock < 0)
        return;

    memset(&s, '\0', sizeof(struct sockaddr_in));
    s.sin_family = AF_INET;
    s.sin_port = (in_port_t)htons(tcpSocket ? tcpSocket : 3310);
    s.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    cli_dbgmsg("broadcast %s to %d\n", mess, broadcastSock);
    if(sendto(broadcastSock, mess, strlen(mess), 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
        perror("sendto");
}

int main(int argc, char *argv[])
{
    int master_socket, addrlen, new_socket, client_sockets[30] = {0}, max_clients = 30, valread, sockety, opt = 1, max_socket;
    fd_set readfds;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    string message = "Connected to server\n";
    if( (master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if( setsockopt(master_socket, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    cout << "Listener on port " << PORT << endl;
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    addrlen = sizeof(address);
    cout << "Waiting for clients..." << endl;

    while(true)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_socket = master_socket;
        for (int i = 0 ; i < max_clients ; i++)
        { 
            sockety = client_sockets[i];
            if(sockety > 0)
            {
                FD_SET(sockety, &readfds);
            }
            if(sockety > max_socket)
            {
                max_socket = sockety;
            }
        }
        int working = select(max_socket + 1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(master_socket, &readfds))
        {
            if((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            cout << new_socket << " " << inet_ntoa(address.sin_addr) << " " << ntohs(address.sin_port) << endl;
            if(send(new_socket, message.data(), message.size(), 0) != message.size())
            {
                perror("send");
            }
            for (int i = 0; i < max_clients; i++)
            {
                if(client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    cout << "Client " << i << " connected" << endl;
                    break;
                }
            }
        }
        for (int i = 0; i < max_clients; i++)
        {
            sockety = client_sockets[i];
            if (FD_ISSET(sockety, &readfds))
            { 
                valread = read(sockety, buffer, 1024);
                string getData(buffer);
                getData.erase(remove(getData.begin(), getData.end(), '\n'), getData.end());
                if(!getData.find("quit"))
                {
                    getpeername(sockety, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    close(sockety);
                    cout << "Client " << i << " disconnected" << endl;
                    client_sockets[i] = 0;
                }
                else
                {
                    buffer[valread] = '\0';
                    string sendData(buffer);
                    reverse(sendData.begin(), sendData.end());
                    sendData.erase(remove(sendData.begin(), sendData.end(), '\n'), sendData.end());
                    sendData += '\n';
                    send(sockety, sendData.data(), sendData.size(), 0);
                }
            }
        }
    }
    return 0;
}