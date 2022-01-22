#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstddef>
#include <stdlib.h>
#include <unistd.h> 
#include <iostream>
#include <cstdio> 
#include <cstring>
char* validation(const char *s,int sock, int bytes_read)
{
    char result[5];
    std::cout<<s;
    result[0]=s[0];
    result[1]=s[1];
    result[2]=',';
    result[3]=s[3];
    result[4]=s[4];
    //std::cout<<"fir coords"<<x0<<' '<<y0<<'\n';
    //std::cout<<"sec coords"<<x1<<' '<<y1<<'\n';
    // for(int i = 0; i < 4; i++)
    //     {123
    //         strcpy(result[i], str);
    //     }
    // char* result = x0+x;
    // return x0;
    //std::cout<<result;
    //return result;
    send(sock, result, bytes_read, 0);
    bzero(result,sizeof(result));
};



int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            //std::cout << buf;
            

            /*for (size_t i = 0; i < sizeof(buf); i++)
            {
                //std::cout<<buf[i];
               
            }
            */
            if(bytes_read <= 0) break;
            validation(buf,sock, bytes_read);
            
        }
    
        close(sock);
    }
    
    return 0;
}