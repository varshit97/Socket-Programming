// // Server1 and Client1
// #include <bits/stdc++.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <unistd.h>
// #include <string>
// #include <arpa/inet.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #define PORT1 8888
// #define PORT2 8889

// using namespace std;

void *server(void *threadid)
{
    cout << "In server1" << endl;
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

// void *client(void *threadid)
// {
//     cout << "In client1" << endl;
//     struct sockaddr_in address;
//     int sock = 0, valread;
//     struct sockaddr_in serv_addr;
//     char buffer[1024] = {0};
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         cout << "\nSocket creation error" << endl;
//         // return -1;
//     }


//     memset(&serv_addr, '0', sizeof(serv_addr));

//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT2);
    
//     // Convert IPv4 and IPv6 addresses from text to binary form
//     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
//     {
//         cout << "\nInvalid address/ Address not supported" << endl;
//         // return -1;
//     }

//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//         cout << "\nConnection Failed \n" << endl;
//         // return -1;
//     }
//     // cout << "In client1" << endl;
//     string input;
//     while(true)
//     {
//         cin >> input;
//         if(!input.compare("quit"))
//         {
//             cout << "breaking thread" << endl;
//             break;
//         }
//         int sent = send(sock, input.data(), input.size(), 0);
//         cout << "Message sent" << endl;
//     }
}
        
int main()
{
    //int NUM_THREADS = 2;
    //pthread_t threads[NUM_THREADS];
    //int server1, client1;
    server();
    //sleep(5);
    //client1 = pthread_create(&threads[1], NULL, client, (void *)1);
    //pthread_exit(NULL);
    return 0;
}

// #include <bits/stdc++.h>
// #include <errno.h> 
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/types.h> 
// #include <sys/socket.h> 
// #include <netinet/in.h> 
// #include <sys/time.h>
  
// #define TRUE   1 
// #define FALSE  0 
// #define PORT 8890

// using namespace std;

// int main(int argc, char *argv[])
// {
//     int opt = TRUE;
//     int master_socket, addrlen, new_socket, client_socket[30], max_clients = 30, activity, i, valread, sd;
//     int max_sd;
//     struct sockaddr_in address;
      
//     char buffer[1024];
//     string message = "Connected to server\n";

//     for (i = 0; i < max_clients; i++)
//     {
//         client_socket[i] = 0;
//     }
//     if( (master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }
//     if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);
//     if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
//     {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }
//     cout << "Listener on port " << PORT << endl;
//     if (listen(master_socket, 3) < 0)
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }

//     addrlen = sizeof(address);
//     cout << "Waiting for connections ..." << endl;
//     fd_set readfds;

//     while(TRUE)
//     {
//         FD_ZERO(&readfds);
//         FD_SET(master_socket, &readfds);
//         max_sd = master_socket;
//         for (i = 0 ; i < max_clients ; i++)
//         { 
//             sd = client_socket[i];
//             if(sd > 0)
//             {
//                 FD_SET(sd, &readfds);
//             }
//             if(sd > max_sd)
//             {
//                 max_sd = sd;
//             }
//         }
//         activity = select( max_sd + 1, &readfds, NULL, NULL, NULL);
//         if ((activity < 0) && (errno!=EINTR))
//         {
//             cout << "select error" << endl;
//         }
//         if (FD_ISSET(master_socket, &readfds))
//         {
//             if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
//             {
//                 perror("accept");
//                 exit(EXIT_FAILURE);
//             }
//             cout << new_socket << " " << inet_ntoa(address.sin_addr) << " " << ntohs(address.sin_port) << endl;
//             if(send(new_socket, message.data(), message.size(), 0) != message.size())
//             {
//                 perror("send");
//             }
              
//             cout << "Welcome message sent successfully" << endl;
//             for (i = 0; i < max_clients; i++)
//             {
//                 if( client_socket[i] == 0)
//                 {
//                     client_socket[i] = new_socket;
//                     cout << "Adding to list of sockets as " << i << endl;
//                     break;
//                 }
//             }
//         }
//         for (i = 0; i < max_clients; i++)
//         {
//             sd = client_socket[i];
//             if (FD_ISSET(sd, &readfds))
//             { 
//                 if ((valread = read(sd, buffer, 1024)) == 0)
//                 {
//                     getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
//                     cout << " " << inet_ntoa(address.sin_addr) << " " << ntohs(address.sin_port) << endl;
//                     close(sd);
//                     client_socket[i] = 0;
//                 }
//                 else
//                 {
//                     buffer[valread] = '\0';
//                     send(sd, buffer, strlen(buffer), 0);
//                 }
//             }
//         }
//     }
//     return 0;
// }