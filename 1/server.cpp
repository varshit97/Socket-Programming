// // Server1 and Client1
#include <bits/stdc++.h>
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#define PORT 8899

using namespace std;

int main(int argc, char *argv[])
{
    int broad, master_socket, addrlen, new_socket, client_sockets[30] = {0}, max_clients = 30, valread, sockety, opt = 1, max_socket;
    fd_set readfds;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    string message = "Connected to server\n";
    if((master_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if((broad = setsockopt(master_socket, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt))) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.1.34.*");
    address.sin_port = htons(PORT);
    if(bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    cout << "Listening on port " << PORT << endl;

    addrlen = sizeof(address);
    cout << "Waiting for clients..." << endl;

    while(true)
    {
        string sendData = "Hello00000";
        new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        int rr= sendto(master_socket, sendData.data(), sendData.size(), 0, (struct sockaddr *)&address, sizeof(sockaddr_in));
		sleep(5);
    }
    return 0;
}
