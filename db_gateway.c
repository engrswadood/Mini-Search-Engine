#include "db_gateway.h"
MYSQL * get_connection()
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
	  fprintf(stderr, "mysql_init() failed\n");
	  exit(1);
	}

	if (mysql_real_connect(con, HOST, USER, PASSWORD, 
	DATA_BASE, 0, NULL, 0) == NULL)
	{
	  finish_with_error(con);
	  con = NULL;	  
	}
	return con;
}
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  //exit(1); /// should not have an exit in case of more than one threads.      
}

void mysql_select_address(MYSQL *con, char *q)
{
	if (mysql_query(con, q))      finish_with_error(con);
}
void mysql_delete_address(MYSQL *con, char *q)
{
	if (mysql_query(con, q))      finish_with_error(con);
}
void mysql_insert_address(MYSQL *con, char *q)
{
	if (mysql_query(con, q))      finish_with_error(con);
}
void mysql_update_address(MYSQL *con, char *q)
{
	if (mysql_query(con, q))      finish_with_error(con);
}

void load_address_db()
{
	MYSQL *con = get_connection();
	
	mysql_select_address(con, "select count(*) total from address_tbl;");	
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)   finish_with_error(con);
	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	
	unsigned int total_records = row[0];
	unsigned int rem_records = total_records;
	
	unsigned offset = 0;
	char *sel_query =  malloc(140);
	char *limit_str = malloc(21);
	char *offset_str = malloc(21);
	
	strcpy(sel_query, "SELECT id, keys, pos, len FROM address_tbl");
	total_record_sets = 4;
	//accumulative_size = (total_queries*(total_queries+1))/2;
	
	int q_size = strlen(sel_query);
	for(int i=0; i<total_record_sets; i++)
	{
		if(offset >= total_records)	break;
		
		int csize = q_size;
		unsigned int limit	= rem_records>>1;
		rem_records		>>=	1;
		
		if(rem_records)
		{
			strcpy(q+csize, " LIMIT ");		csize += 7;
			limit_str = itoa(limit, limit_str, 10);
			strcpy(q+csize, limit_str);	csize += strlen(limit_str);	
		}
		strcpy(q+csize, " OFFSET ");		csize += 8;
		offset_str = itoa(offset, offset_str, 10);
		strcpy(q+csize, offset_str);	csize += strlen(offset_str);
		
		offset += limit;
		
		mysql_select_address(sq->qry_rply);	
		MYSQL_RES *result = mysql_store_result(con);
		if (result == NULL)   finish_with_error(con);
		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;
		
		while ((row = mysql_fetch_row(result))) 
		{
			//unsigned int b =READ_LE4(q_val);
			//unsigned long long int id = READ_LE4(q_val);
			//id = id<<32|b;
			//order of columns id, keys, pos, len
			ad_add_address(address_tbl, atoll(row[0]), row[1], row[2], atoi(row[3]));
		  //for(int i = 0; i < num_fields; i++) 
			 // printf("%s ", row[i] ? row[i] : "NULL");
		  strcat(reply, row[0]);//
		  strcat("\n");
		}
		mysql_free_result(result);
	}
	
	free(sel_query);
	free(limit_str);
	free(offset_str);
	
	
	mysql_close(con);
}
