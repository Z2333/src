#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

char course[32] = "\0";
char score[32] = "\0";
char id[32] = "\0";
int status = 0 ;
status = cgiFormString("course",  course, 32);
if (status != cgiFormSuccess)
{
  fprintf(cgiOut, "get course error!\n");
  return 1;
}
status = cgiFormString("score", score, 32);
if (status != cgiFormSuccess)
{
  fprintf(cgiOut, "get score error!\n");
  return 1;
}
status = cgiFormString("id", id, 32);
if (status != cgiFormSuccess)
{
  fprintf(cgiOut, "get id error!\n");
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



strcpy(sql, "create table score(course varchar(32) not null , score varchar(32) not null,id int not null)");
if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
{
  if (ret != 1)
  {
    fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
    mysql_close(db);
    return -1 ;
  }
}



sprintf(sql, "insert into score values(%d,'%s','%s')", atoi(id),course,score );
fprintf(cgiOut, "%s\n                  ",sql );
if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
{
  fprintf(cgiOut, "%s\n", mysql_error(db));
  mysql_close(db);
  return -1;
}

fprintf(cgiOut, "add student ok!\n");
mysql_close(db);
return 0;
}
