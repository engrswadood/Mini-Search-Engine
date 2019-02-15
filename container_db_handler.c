#include <stdlib.h>
#include <string.h>
#include "contbl_t.h"

void insert_as_ad()
{//id, wid_buf, pos_buf, len 
	
	size_t size = 80;
	size_t csize;// = 80;
	char *q_str = malloc(size);
	char* len_str = malloc(22);
	
	len_str = itoa(len, len_str, 10);
	
	strcpy(q_str, "INSERT INTO wid_ad(id, wids, poses, len) VALUES(1, '%s', '%s', "); csize = strlen(q_str);
	strcpy(q_str+csize, len_str);	csize += strlen(len_str);
	strcpy(q_str+csize, ");");	csize += strlen(len_str);
	

	strcpy(q_str+csize, grp_str);		csize += grp_len;
	strcpy(q_str+csize, ");");			csize += 2;

	size_t wid_size = len*sizeof(WIDSIZE_T);//_
	size_t pos_size = len*4;//_

	size_t chunk1_len = 2 * wid_size +1;
	size_t chunk2_len = 2 * pos_size +1;

	char chunk1[chunk1_len];
	IF__LITTLE_ENDIAN
	mysql_real_escape_string(con, chunk1, wid_buf, wid_size);

	char chunk2[chunk2_len];
	mysql_real_escape_string(con, chunk2, pos_buf, pos_size);


	size_t q_len = chunk1_len + chunk2_len + csize;

	char query[q_len];//multiplication of 2 for escaping.

	size_t query_len = snprintf(query, q_len, q_str, chunk1, chunk2);
  
	if(mysql_real_query(con, query, len))
	{
	  finish_with_error(con);
	}
}
void insert_as_ad_cont(id, widAr,wlen)//_
{//id, wid_buf, wlen
	//WIDSIZE_T* widAr = th->widAr;
	size_t size = 180;
	size_t csize;// = 80;
	char *q_str = malloc(size);
	char* id_str = malloc(22);
	char* wid_str = malloc(41);
	
	id_str = itoa(id, id_str, 10);
	
	strcpy(q_str, "INSERT INTO wid_cont(wid, ids) VALUES"); csize = strlen(q_str);
	
	size_t query_len = 0;
	for(size_t i=0; i<wlen; i++)
	{
		
		size_t rsize = csize+6+41+41;
		INC_MEM_IF_REQ(q_str, size, rsize);
		
		wid_str = itoa(widAr[i], wid_str, 10);
		strcpy(q_str+csize, "(");			csize++;
		strcpy(q_str+csize, wid_str);	csize += strlen(wid_str);//_ if wid_str is string in table then it should be enquoted.
		strcpy(q_str+csize, ",'");			csize +=2;
		strcpy(q_str+csize, id_str");	csize += strlen(id_str);
		strcpy(q_str+csize, "'), ");			csize +=4;
	}
	
	size_t rsize = csize+6+41+41;
	INC_MEM_IF_REQ(q_str, size, rsize);
	strcpy(q_str+csize, " ON DUPLICATE KEY UPDATE ids = CONCAT(ids, ',");
	strcpy(q_str+csize, wid_str);
	strcpy(q_str+csize, "');");
	//INSERT INTO authors(id, name) values(5, 'sul'), (103, 'sul'), (2, 'sul')  ON DUPLICATE KEY UPDATE name = CONCAT(NAME, ',sul');
}
void delete_as_ad()()// This function may not be applied any-more.
{
//id
	char* id_str = malloc(22);
	id_str = itoa(id, id_str, 10);
	size_t csize;
	char *q_str = malloc(200); 
	strcpy(q_str+csize, "DELETE FROM wid_ad where id=");	csize = strlen(q_str);
	strcpy(q_str+csize, id_str);	csize += strlen(id_str);
	strcpy(q_str+csize, ";");

}
void delete_as_ad_cont(id, widAr, wlen)//_
{
//id, wid_buf, wlen
	WIDSIZE_T* widAr = get_wids_ad(id)//_
	size_t size = 180;
	size_t csize;// = 80;
	char *q_str = malloc(size);
	
	char* id_str = malloc(22);
	char* wid_str = malloc(41);

	id_str = itoa(id, id_str, 10);


	strcpy(q_str, "UPDATE wid_cont SET ids = replace(ids, '");	csize = strlen(q_str);
	strcpy(q_str, id_str);	csize += strlen(id_str);
	strcpy(q_str, "', '') WHERE wid IN(");	csize += 11;

	for(size_t i=0; i<wlen; i++)
	{
		
		size_t rsize = csize+44;
		INC_MEM_IF_REQ(q_str, size, rsize);
		
		wid_str = itoa(widAr[i], wid_str, 10);
		strcpy(q_str+csize, ",");			csize++;
		strcpy(q_str+csize, wid_str);	csize += strlen(wid_str);//_ if wid_str is string in table then it should be enquoted.
	}
	
	strcpy(q_str-1, ");";
	
	//UPDATE authors SET name = replace(name, ',Sir,', '') WHERE id IN(2, 3, 102, 5);

}
WIDSIZE_T* get_wids_of_ad(id)//_
{
	char* id_str = malloc(22);
	id_str = itoa(id, id_str, 10);
	size_t csize;
	char *q_str = malloc(200); 
	strcpy(q_str+csize, "SELECT wids FROM wid_ad where id=");	csize = strlen(q_str);
	
	
	strcpy(q_str+csize, id_str);	csize += strlen(id_str);
	strcpy(q_str+csize, ";");

	mysql_query//_
	MYSQL_ROW row = mysql_fetch_row(result);
	bAr//_
	WIDSIZE_T* wAr = malloc(clen);
	IF__LITTLE_ENDIAN
		memcpy(bAr, clen, wAr);
	ELSE
		leb_to_arr(char* cAr, size_t clen, wAr)
	return wAr;
}

void update()
{//id, wid_buf, pos_buf, len 
	delete_as_ad_cont(id)
	insert_as_ad(id, wid_buf, pos_buf, len)//_
	insert_as_ad_cont(id, wid_buf, wlen);
}

//*****************
//_____________________
char* get_ids_of_wid(wid)
{
	char* wid_str = malloc(22);
	wid_str = itoa(wid, wid_str, 10);
	size_t csize;
	char *q_str = malloc(200); 
	strcpy(q_str+csize, "SELECT ids FROM wid_cont where wid=");	csize = strlen(q_str);
	
	
	strcpy(q_str+csize, wid_str);	csize += strlen(id_str);
	strcpy(q_str+csize, ";");

	mysql_query//_
	MYSQL_ROW row = mysql_fetch_row(result);
	bAr//_
	WIDSIZE_T* wAr = malloc(clen);
	IF__LITTLE_ENDIAN
		memcpy(bAr, clen, wAr);
	ELSE
		leb_to_arr(char* cAr, size_t clen, wAr)
	return wAr;
}

char* get_recs_of_ids(Thread* thr, ids_str)//_
{
	UniqueTbl* ut = thr->unique_tbl;
	
	size_t sent_len = strlen(ids_str);
	
	char sql_query;
	char* q_str = sql_query = malloc(180);
	size_t size = 180;
	
	strcpy(q_str, "SELECT * FROM wid_ad WHERE id IN('");
	size_t csize = strlen(q_str);
	
	size_t j = 0;
	char* id = ids_str;
	for(int i=0; i<sent_len; i++)
	{
		if(ids_str[i] == ",")
		{
			//W_CHLIM_T len = j*sizeof(CH_TYPE_T);
			UniqueID* un = get_ditem_by_str(ut, id, j);
			if(!un)
			{
				//
				rsize = csize+j+1;
				INC_MEM_IF_REQ(q_str, size, rsize);
				strncpy(q_str+csize,  id, j);
				csize += j;
				strcpy(q_str+csize, "','");
				csize += 3;
			}	
			j=0;
			id = ids_str;
		}
		else	j++;
	}
	
	rsize = csize+j+3;
	INC_MEM_IF_REQ(q_str, size, rsize);
	strncpy(q_str+csize,  id, j);
	csize += j;
	strcpy(q_str+csize, "');");
	return 
}

MYSQL_RES* get_ads(Thread* thr, wid)// Container for the above two functions and is the main function, which should be called frome searching algo
{
	char* ids_str  = get_ids_of_wid(wid);
	char* sql_query =  get_recs_of_ids(thr, ids_str+1);
	//.....
}


//****************************
//_____________________

char* arr_to_leb(WIDSIZE_T* wAr, size_t wlen)//leb for "little endian bytes"
{
	//size_t clen = wlen*sizeof(WIDSIZE_T);
	char* cAr = malloc(clen);
	//IF__LITTLE_ENDIAN
		//memcpy(cAr, wAr, clen);
	//ELSE
	//{
		size_t w_size = sizeof(WIDSIZE_T);
		size_t j=0;
		size_t val;
		for(int i=0; i<wlen; i++)
		{
			val = wAr[i];
			cAr[j++] = val&0xFF;
			cAr[j++] = val&0xFF00>>8;
			if(w_size>2)
			{
				cAr[j++] = val&0xFF0000>>16;
				cAr[j++] = val&0xFF000000>>24;
			}
		}
	//}
	return cAr;
}

WIDSIZE_T* leb_to_arr(char* cAr, size_t clen)
{
	//WIDSIZE_T* wAr = malloc(clen);
	//IF__LITTLE_ENDIAN
		//memcpy(wAr, cAr, clen);
	//ELSE
	//{
		size_t w_size = sizeof(WIDSIZE_T);
		size_t j=0;
		char* cAr2 = (char*) wAr;
		
		if(w_size==4)
		{
			for(int i=0; i<clen; i+=4)
			{
				cAr2[j]   = cAr[i+3];
				cAr2[j++] = cAr[i+2];
				cAr2[j++] = cAr[i+1];
				cAr2[j++] = cAr[i];
			}
		}
		else
		{
			for(int i=0; i<clen; i+=2)
			{
				cAr2[j++] = cAr[i+1];
				cAr2[j++] = cAr[i];
			}
		}
		
	//}
	return wAr;
}