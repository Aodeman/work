#include <stdio.h>       
#include <string.h>       
#include <errno.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include "db.h"  /*int db_open(char *db_name,sqlite *db) ,int db_insert(sqlite3 *db,char *db_name,char *id,char *time,char *tem)*/

#define   db_name "temp.db"
int  get_signal=1;
int  serfd=-1;

void set_signal(int signum)
{
	get_signal=0;
	close(serfd);
        printf("Serfd was closed!\n");
}


int main()
{
	pid_t                   pid;
	int                     on=1;
	int                     newfd=-1;
	int			            rv=-1;
	struct sockaddr_in      seraddr;
	struct sockaddr_in      cliaddr;
	socklen_t		        len;
	char                    buf[100];
	struct hostent          * host;
    sqlite3                 *db;

        char                    *s;
        char                    *id;
        char                    *tem;
        char                    *time;

	printf("Start\n");
	serfd=socket(AF_INET,SOCK_STREAM,0);
	if(serfd<0)
	{
		perror("Socket failure:");
		return -1;
	}

        if((setsockopt(serfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))<0)
	{
	        perror("Setsockpt failure");
	}
        


	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(12335);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	printf("Socket success!\n");
	rv=bind(serfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(rv<0)
	{
		perror("Bind failure");
		return -2;
	}
	printf("Bind success!\n");

	rv=listen(serfd,0);
	if(rv<0)
	{
		printf("Listen failure");
		return -3;
	}
	printf("Listen success!\n");

    if((db_open(db_name,db))<0)     //create a DBMS.
    {
        printf("Create db failure\n");
        return -1;
    }
	signal(SIGINT,&set_signal);
	while(get_signal)
	{    
        printf("Waiting new client connect...\n");
		newfd=accept(serfd,(struct sockaddr *)&cliaddr,&len);
		if (newfd<0)
		{
			perror("accept failure");
			return -4;
		}
        printf("Accept new client[%s:%d] successfully\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		pid=fork();
		if(pid<0)
		{
		        ;	
		}
		else if(pid==0)
		{
            while(get_signal)
		    {
                memset(buf,0,sizeof(buf));
                rv=read(newfd,buf,sizeof(buf));
                if(rv==-1)
                {  
                    printf("read failure\n");
                    perror("Read failure");
                    close (newfd);
                    return -5;
                }
                if(rv==0)
                {
//                  get_signal=0;
                    printf("Clent disconnet!\n");
                    close(newfd);
                    return -6;
			    }

                printf("Received data from client: %s\n",buf);
                
                id=strtok(buf,"|");
                time=strtok(NULL,"|");
                tem=strtok(NULL,"|");
                
                printf("/********************************************/\n");
               
                rv=db_insert(db,db_name,id,time,tem);
                if(rv<0)
                    printf("record fiult\n");
                printf("/********************************************/\n");
		    }
                    return 0;
                        
		}
		else
		{	
		     ;
		}

	
	
	
	}


        return 0;

}
