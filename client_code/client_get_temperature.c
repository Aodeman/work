#include <stdio.h>          
#include <string.h>          
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "ds18620.h"   /* get_tem() */

#define id "Aodeman"
 
int get_sig=1;
char *serip ="192.168.0.16";


char *get_time()
{
    char      *s;
    time_t    now;
    struct tm *timenow;
  
    time(&now);//International time
    timenow=localtime(&now);

    s=asctime(timenow);
    s[strlen(s)-1]=0;    /*delete the last '\n'*/
    return s;

}


void get_signal(int signum)
{

     get_sig=0;

}



int main (int argc , char  *argv[])
{
    int                 port=12335;
    int             	sockfd=-1;
    int			rv=-1;
    int                 buf[100];
    int                 tem;
    char                *time;
    char                data[100];
    struct sockaddr_in      seraddr;



    int ch=getopt( argc, argv,"i:p:h");
    while(ch!=-1)
    {
	switch(ch)
	{
	    case 'i':
		    printf("IP is %s\n",optarg);
		    serip=optarg;
		    break;
	    case 'p':
		    printf("Prot is %s\n",optarg);
                    port=atoi(optarg);
		    break;
	    case 'h':
                    printf("usage:[-i] [-h]\n");
		    break;
            case '?':
                    printf("ERROR!\n");
                    break;
        }
        break;
    }

	
      
    signal(SIGINT,get_signal);
    signal(SIGTERM,get_signal);
    while(get_sig)                                 
    {
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("creat socket failure");
		return -1;
	}
	printf("Socket success!\n");
	if(argc != 2)
	{	
		seraddr.sin_family=AF_INET;
		seraddr.sin_port=htons(port);
		inet_aton(serip,&seraddr.sin_addr);
	}
	else
	{
		port=atoi(argv[2]);
	 
		seraddr.sin_family=AF_INET;
		seraddr.sin_port=htons(port);
		inet_aton(argv[1],&seraddr.sin_addr);
	}
  		

	rv=connect(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if (rv<0)
	{
		perror("Connect failure");
		return -2;
	}

    memset(data,0,sizeof(data));
    tem=get_tem();                 
    time=get_time();
    snprintf(data,sizeof(data),"id=%s\n tem=%d\n time=%s\n",id,tem,time);
    
    rv=write(sockfd,data,strlen(data));
	if(rv<0)		
	{
        perror("write failure:");
		return -3;
	}
    else if(rv==0)
    {
        printf("Write data failure\n");
    }
    else
	{
        printf("/**************************/\n");
        printf("Client:%s\n",data);
        printf("/**************************/\n");
	}


        close(sockfd);
//        sleep(30);
    }
	return 0;
}
