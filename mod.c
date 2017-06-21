#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char name[32] = "\0";
	char id[32] =  "\0";
	char sex[20] = "\0";
	char Sid[32] =  "\0";
	char age[16] = "\0";

	int status = 0 ;

	status = cgiFormString("name",  name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("id",  id, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get id error!\n");
		return 1;
	}
	status = cgiFormString("sex",  sex, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}
	status = cgiFormString("Sid", Sid, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sid error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, id = %s,sex = %s,Sid =%s\n", name, age, id,sex,Sid);

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


	sprintf(sql, "update information set Sid=%d, name='%s', age= %d ，sex='%s' where id = %d ",atoi(Sid),name, atoi(age),sex,atoi(id));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
