#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

char Sname[32] = "\0";
char Sid[20] = "\0";

int status = 0 ;

status = cgiFormString("Sname",  Sname, 32);
fprintf(cgiOut, "%s\n", Sname);
if (status != cgiFormSuccess)
{
  fprintf(cgiOut, "get Sname error!\n");
  return 1;
}
status = cgiFormString("sid", Sid, 20);
if (status != cgiFormSuccess)
{
  fprintf(cgiOut, "get Sid error!\n");
  return 1;
}


int ret;
char sql[128] = "\0";
MYSQL *db;

//初始化
db = mysql_init(NULL);
if (db == NULL)
{
  fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
  return -1;
}

//连接数据库
db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
if (db == NULL)
{
  fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
  mysql_close(db);
  return -1;
}



strcpy(sql, "create table school (Sid int not null primary key, Sname varchar(20) not null)");
if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
{
  if (ret != 1)
  {
    fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
    mysql_close(db);
    return -1 ;
  }
}



sprintf(sql, "insert into school values('%s',%d)", Sname, atoi(Sid));
if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
{
  fprintf(cgiOut, "%s\n", mysql_error(db));
  mysql_close(db);
  return -1;
}

fprintf(cgiOut, "add school ok!\n");
mysql_close(db);
return 0;
}
