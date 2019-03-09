#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"



int record_to_db(char *id,char *time,char *tem)
{

    char     *zErrMsg=0;
    sqlite3  *db=NULL;
    char     *a=0;
    int      rz;
    char     sql_insert[100];
    
    rz=sqlite3_open("tem.db",&db);/*cteate a DBMS*/
    if(rz)
    {
        perror("open error");
        return -1;

    }


/******create table*******/

        char *sql="create table Tem ( \
               id text identity(1,1) primary key, \
               time text ,\
               tem  text );";
        sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
        #ifdef _DEBUG_
            printf("%s\n",zErrMsg);
            return -1;
        #endif
/******insert data********/
    memset(sql_insert,0,sizeof(sql_insert));
    snprintf(sql_insert,sizeof(sql_insert),"insert into Tem values('%s','%s','%s');",id,time,tem);
    printf("insert  %s\n",sql_insert);

    sqlite3_exec(db,sql_insert,NULL,NULL,&zErrMsg);
    #ifdef _DEBUG_
        printf("%s\n",zErrMsg)
        return -1;
    #endif


    return 0;

}


