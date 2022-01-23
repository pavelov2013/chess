#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstddef>
#include <stdlib.h>
#include <unistd.h> 
#include <iostream>
#include <algorithm>
#include <cstdio> 
#include <cstring>
#include <cstdlib>

//,int sock, int bytes_read
void sendM(int sock, int bytes_read,const char *s)
{
    send(sock, s, bytes_read, 0);
}
bool validation(const char *s)
{
    int i=0;
    int a[5];
    int valid[5] = {2,1,0,2,1};
    while ( s[i] ) 
    {
        if  ((isalpha(s[i])))
            { 
                std::cout << "is bukva " << s[i] << "\n";
                a[i]=2;
            }
        else if ((isdigit(s[i])))
            { 
                std::cout << "is num " << s[i] << " \n";
                a[i]=1;
            }
        else if (s[i]==',')
        {
            std::cout << "is zapatai "<< " \n";
            a[i]=0;
        }
        else {}
        i++; 
    } 
    if (!std::equal(a,a+5,valid)) return 1;
    
    

    //bzero(result,sizeof(result));

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
    int opt = 1;
    if (setsockopt (listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1) perror("setsockopt");
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
            std::cout<<validation(buf)<<std::endl;
            //if (validation(buf)) sendM(sock, buf, bytes_read);
            
        }
    
        close(sock);
    }
    
    return 0;
}