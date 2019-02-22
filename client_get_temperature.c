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


int get_sig=1;
void get_signal(int signum)
{

     get_sig=0;

}


char *serip ="192.168.0.16";

int main (int argc , char  *argv[])
{
	int                     port=12345;
	int             	sockfd=-1;
	int			rv=-1;
	struct sockaddr_in      seraddr;
	char                    buf[100];

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
        memset(buf,0,sizeof(buf));
        int fd=open("/home/iot/yangbiao/data.txt",O_RDONLY,644);
        read(fd,buf,sizeof(buf));
	rv=write(sockfd,buf,sizeof(buf));
	if(rv<0)		
	{
	        perror("write failure:");
		return -3;
	}
	else
	{
		printf("Client:%s\n",buf);
	}
        close(fd);

        close(sockfd);
        sleep(3);
    }
	return 0;
}
