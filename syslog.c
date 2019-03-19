#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <libgen.h>      /*char *basename(char *path)*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

const char *  path="/home/gts/syslog.log";


int main (int argc,char *argv[])
{   
    int     rv;
    int     nfd;
    int     fd;
    char  * progname;
  
    
    fd=openat(nfd,path,O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd<0)
    {    perror("Open fiult");}
    rv=dup2(fd,1);
    if(rv<0)
    {    perror("Daemon fiult");        }
    rv=daemon(0,0);
    if(rv<0)
    {   perror("dup filut");}
    progname=basename(argv[0]);
    printf("Start!\n");
    openlog("daemon",LOG_CONS|LOG_PID,0);
    syslog(LOG_EMERG,"Program %s running with a emergenry message.\n",progname);
    syslog(LOG_ALERT,"Program %s exception,please repair it immediately.\n",progname);
    syslog(LOG_NOTICE,"Program %s running .\n",progname);
    syslog(LOG_DEBUG,"Program %s running .\n",progname);
    syslog(LOG_INFO,"Program %s running .\n",progname);
    syslog(LOG_WARNING,"Program %s running .\n",progname);
    syslog(LOG_ERR,"Program %s running .\n",progname);
    syslog(LOG_CRIT,"Program %s running .\n",progname);
    printf("hair\n");
    

    while(1)   {  ;  }
    closelog();
    close(fd);
    return 0;


    


}
