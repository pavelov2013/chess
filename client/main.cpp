#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <cstddef>
#include <stdlib.h>
#include <unistd.h> 
#include <cstdio>
#include <netdb.h> 

#define host "192.168.88.252"
#define port 7777

char message[256] = "";
char buf[sizeof(message)];

int main()
{
    struct hostent *server;
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock <= 0)
    {
        printf("socket");
        exit(1);
    }
    bzero((char *) &addr, sizeof(addr));
    bcopy((char *)server->h_addr, 
         (char *)&addr.sin_addr.s_addr,
         server->h_length);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("not connected");
        exit(2);
    }
    while(sock){
        std::cin >> message;
        int n = write(sock,message,strlen(message));
        if (n < 0) printf("ERROR writing to socket");
        bzero(buf,256);
        n = read(sock,buf,255);
        if (n < 0) printf("ERROR reading from socket");
        printf("%s\n",buf);
   }
    close(sock);

    return 0;
}