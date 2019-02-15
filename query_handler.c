#include "query_handler.h"
//threshold, keys_len, keys, id_bool, id, total_suggesting arrays, suggesting arrays (each array ends with NULL/0 Integer, threshold in case of web search//select
//type, keys_len, keys, id_bool, id, group, pos, query_len, query //insert
//type, keys_len, keys, id_bool, id, delete_query//delete
//type, keys_len, keys, id_bool, id, ukeys_len, ukeys, id_bool, id, group, pos, query_len, query//updating
//reset_sq, init_cache, collect_result, apply_pos_marks


//*******Made By Dic****//Search-> id_index, total_group_arrays, group_ars, id, keys_len, keys, total_sugg, sug_ids

//short start_time;//time and day
//short end_time;// time and month
//char total_tokens;
//char per_hour_tokens;

int init_query_handler(LE_THREAD *thr, char *q_val, uint8_t op_mode)// This function is used in case ad is seperate server.
{
	QueryData qd = thr->query_data;
	int i=0, j=0;
	unsigned int b, len = qd->_keysLen = READ_LE2(q_val);
	unsigned long long int a;
	int *ar = qd->_keys;
	for(i=0; i<len; i++)
		ar[i] = READ_WORD(q_val);
	if(*q_val++)
	{
		b = READ_LE4(q_val);
		a = READ_LE4(q_val);
		qd->_id = a<<32|b;
	}
	if(op_mode != 2)// if insert/add then reset is not needed.		
		reset_sq();
	

	if(op_mode == 1)
			search_employer(thr, q_val);
	else if(op_mode == 2)
			add_employer(thr, q_val);
	else if(op_mode == 3)
			update_employer(thr, q_val);
	else if(op_mode == 4)
			delete_employer(thr, q_val);
	//write_responce();
}





