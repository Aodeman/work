#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"



int db_open(char *db_name,sqlite3 *db)
{

    char     *zErrMsg=0;
    char     *a=0;
    int      rz;
    rz=sqlite3_open(db_name,&db);/*cteate a DBMS*/
    if(rz)
    {
        perror("open error");
        return -1;
    }


    /******create table*******/
    char *sql="create table Tem ( \
               id text identity(1,1) , \
               time text ,\
               tem  int );";
    
    sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
    #ifdef _DEBUG_
        printf("%s\n",zErrMsg);
        return -1;
    #endif
    sqlite3_close(db);
    return 1;
}



/******insert data********/
int db_insert(sqlite3 *db,char *db_name,char *id,char *time,char *tem) 
{
    char     *zErrMsg=0;
    char     sql1[100];
    
    
    sqlite3_open(db_name,&db);/*cteate a DBMS*/
    memset(sql1,0,sizeof(sql1));
    snprintf(sql1,sizeof(sql1),"insert into Tem values('%s','%s','%s');",id,time,tem);
    printf("%s\n",sql1);
    sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);
    #ifdef _DEBUG_
        printf("%s\n",zErrMsg)
        return -1;
    #endif

    sqlite3_close(db);
    return 1;
}


