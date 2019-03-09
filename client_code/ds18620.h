#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>   
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int get_tem (void)
{  
    int               a;   	
    int               fd;	
    DIR               *dir;
    struct dirent     *dp;
    char              buf[100];
    char              path[100]="/sys/bus/w1/devices/";
    char              *s;
    char              data[50];
    float             swp;
    char              *tem;   
    dir=opendir(path);
    while((dp=readdir(dir))!=NULL)
    {   

        if((s=strstr(dp->d_name,"28-"))!=NULL)
	{
		strncat(path,dp->d_name,strlen(dp->d_name));
		strncat(path,"/w1_slave",12);

	    if((fd=open(path, O_RDONLY,0644))<0)
		    perror("Open file filure \n");
            if((read(fd,buf,sizeof(buf)))==-1)
		    perror("Read file filure \n");

	    s=strtok(buf,"t");
	    lseek(fd,strlen(s)+2,SEEK_SET);
	    memset(buf,0,sizeof(buf));

            if((read(fd,buf,sizeof(buf)))==-1)    
		    perror("read again file filure");
	    a=atoi(buf);
	    swp=(float)a/1000;
            tem=buf;
	    close(fd);
	}
	else
		continue;

    }
    closedir(dir);
    return a;


}

