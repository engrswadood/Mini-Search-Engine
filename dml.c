/*void add_employer(LIBEVENT_THREAD *thr, char *q_val)
{
	QueryData qd = thr->query_data;
	int len;
	//****
	qd->_pos = q_val;
	q_val = q_val+qd->_keysLen;
	len = READ_LE2(q_val);
	char sql[100] = "select id from group where name = ";
	sql_len = 34+
	strcpy(sql, group_name);
	
	//mysql_insert_address(qd->sqlcon, ins_val, len);
	
	mysql_insert_address(qd->sqlcon, q_val);//len is the total length of query.
	add_address(address_table, qd->_id, qd->_keys, qd->_pos, qd->_keysLen);
	delete_cor_mcm(thr->adding_keyAr, thr->adding_lenAr, thr->adding_len);
}*/

void update_eng_employer(Thread* thr)
{//type, keys_len, keys, id, ukeys_len, ukeys, id, ad_string//updating

	delete_employer(thr);
	
	bytes_to_blends(thr);
	
	CorObj* cor_objAr = convert_to_CorObj(thr);
	selectionSort(cor_objAr, thr->klen);
	
	char *ch_widAr = malloc(wlen*sizeof(WIDSIZE_T));
	char *ch_blendAr = malloc(wlen*N_BLEND_BYTES);
	convert_to_bytes(ch_widAr, ch_blendAr, cor_objAr, wlen);
	
	
	
	insert_as_ad_cont(id, new_widsAr, nwlen);

	
	////////////////
	
	size_t w_buf_size = N_WID_BYTES*wlen*2;
	size_t b_buf_size = N_BLEND_BYTES*wlen*2;
	
	char wid_bytes_data[w_buf_size];
	mysql_real_escape_string(con, wid_bytes_data, ch_widAr, w_buf_size);
	
	char blend_bytes_data[b_buf_size];
	mysql_real_escape_string(con, blend_bytes_data, ch_blendAr, b_buf_size);

	char *q_val = "UPDATE table SET wids = '%s', blends= '%s' where id = %d";
	size_t q_len = strlen(q_val);
	int qsize = w_buf_size+b_buf_size+q_len+1;
	char query[qsize];
	int len = snprintf(query, qsize, q_val, wid_bytes_data, blend_bytes_data, thr->cl_id);

	if (mysql_real_query(con, query, len))
	{
		finish_with_error(con);
	}
	
	delete_cor_mcm(thr->adding_keyAr, thr->adding_lenAr, thr->adding_len);
	
}

void delete_eng_employer(Thread* thr)
{
	delete_as_ad_cont(thr->id, thr->old_widsAr, thr->owlen);
	delete_cor_mcm(thr->deleting_keyAr, thr->deleting_lenAr, thr->deleting_len);
}

typedef struct{
	int wid;
	int blend;
}	CorObj ;

void selectionSort(CorObj* woAr, int n)//made for search engine.
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (woAr[j].wid < woAr[min_idx].wid)
            min_idx = j;
        //Swap the found minimum element with the first element
		CorObj temp		= woAr[min_idx];
		woAr[min_idx]	= woAr[i];
		woAr[i]			= temp;
    }
}



void CorObj* convert_to_CorObj(Thread* thr)//WIDSIZE_T* widAr, uint32_t* blendAr, int len)//made for search engine.
{
	WIDSIZE_T* widAr = thr->addAr;
	WIDSIZE_T* blendAr = thr->blendAr;
	int len = thr->klen;
	CorObj* ar = malloc(len*sizeof(CorObj));
	for(size_t i=0; i<len; i++)
	{
		ar[i].wid = widAr[i];
		ar[i].blend = blendAr[i];
	}
	return ar;
}

void CorObj_to_bytes(char* widAr, char *blendAr, CorObj* cbAr, wlen)
{
	
		int j = 0;
		for(int i=0; i<wlen; i++)
		{
			WIDSIZE_T a = cbAr[i].wid;
			uint32_t b = cbAr[i].blend;
			
			widAr[j++] = a&0x000000FF;
			widAr[j++] = a&0x0000FF00;
			#if (N_WID_BYTES == 4)
				widAr[j++] = a&0x00FF0000;
				widAr[j++] = a&0xFF000000;
			#endif
			
			blendAr[j++] = a&0x000000FF;
			blendAr[j++] = a&0x0000FF00;
			blendAr[j++] = a&0x00FF0000;
			blendAr[j++] = a&0xFF000000;
		}
	
}
// Driver program to test above functions
/*int main()
{
    CorObj arr[10];
	for(int i=5; i<10; i++)
	{
		arr[i].wid = (i+1)*100;
		arr[i].blend = i+1;
	}
	for(int i=0; i<5; i++)
	{
		arr[i].wid = (i+1)*1000;
		arr[i].blend = i+1;
	}
	for(int i=0; i<10; i++)
	{
		printf("%d,		%d \n", arr[i].wid, arr[i].blend);
	}
	printf("___________________________________________________\n");
	selectionSort(arr,  10);
	for(int i=0; i<10; i++)
	{
		printf("%d,		%d \n", arr[i].wid, arr[i].blend);
	}
	
    return 0;
}

command
appdata

*/