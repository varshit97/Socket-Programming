// Server1 and Client1
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int PORT1 ,PORT2 ;
using namespace std;
string cla;

void *server(void *threadid)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT1);
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        cout << "client2 connected" << endl;
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while(true)
    {
        valread = read(new_socket, buffer, 1024);
        cout << buffer << endl;
        memset(&buffer, '\0', sizeof(buffer));
    }
}

void *client(void *threadid)
{
	char hostname[128];
	cin >> PORT2;
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "\nSocket creation error" << endl;
        // return -1;
    }
  

    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT2);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, cla.data(), &serv_addr.sin_addr) <= 0) 
    {
        cout << "\nInvalid address/ Address not supported" << endl;
        // return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << "\nConnection Failed \n" << endl;
        // return -1;
    }
    // cout << "In client1" << endl;
    string input;
    while(true)
    {
        getline(cin, input);
        if(!input.compare("quit"))
        {
            cout << "breaking thread" << endl;
			exit(0);
        }
        int sent = send(sock, input.data(), input.size(), 0);
    }
}

int main()
{
	srand (time(NULL));
    int NUM_THREADS = 2;
    pthread_t threads[NUM_THREADS];
    int server1, client1;
	PORT1=4000+(rand()%5000);
	cout << "Enter This Port in your client "<< PORT1 << endl;
	cout << "Enter The client adress" << endl;
	cin >> cla;
	cout <<"Enter the port of client u want to connect"<<endl;
    server1 = pthread_create(&threads[0], NULL, server, (void *)0);
    client1 = pthread_create(&threads[1], NULL, client, (void *)1);
    pthread_exit(NULL);
    return 0;
}
