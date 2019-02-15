#include "search.h"
void search_eng_employer(Thread* thr/*, char *q_val*/) // argument commented by applying the mergence of dic and ad.
{
	QueryData qd = thr->query_data;
	/*int i;
	int j;
	int *ar;
	int	**sugAr = qd->suggestedAr; //commented by applying the mergence of dic and ad.
	qd->n_msw =  *q_val++;
	
	if(qd->n_msw)
	{	
		i=0;
		while(i<qd->n_msw)
		{
			short val = 1;
			j=0;
			ar = sugAr[i++];
			while(val) {ar[j++] = val = READ_LE2(q_val);}
		}
	}
	qd->_webSearch = *q_val++;*/ //<<commented by applying the mergence of dic and ad.
	
	init_web_search(thr);
	set_db_query((qd->_webSearch)? 0xFFFFFFFF : MIN_REP);
	mysql_select_address(qd->sqlcon, qd->qry_rply);
	int n_pages;
	char** pageAr = create_pages(srch_nodeAr, total_items, &n_pages);
	if(thr->page_number == 2)//Initial pages for query exist but the page that is required does not exist.
	{
		resize_unique_tbl(thr, total_items);
		update_cor_mcm(thr, char* sval, CHLEN_T chlen, pageAr, n_pages);
		//if(thr->search_page == 2)// the search query exists but the page does not exist.
			
	}
	else// no such search query exists.
	{
		thr->unique_tbl = create_srch_unique_tbl(thr, total_items);
		add_cor_mcm(thr, char* sval, CHLEN_T chlen, pageAr, n_pages, wordAr, lenAr, wlen);
	}
		
	//thr->page = pageAr[0];
}

void init_web_search(Thread* thr)
{//in future fastest web-fcache may be checked first, if exisits then return.

	int remaining = thr->keys_len - thr->n_msw;
	char *flgAr = calloc(thr->keys_len);
	for(i=0; i<qd->keys_len; i++)	
		if(srch_twinAr[i]) flgAr[i] = 1;
	uint32_t rem_marks;
	do
	{
		int sel_ind = -1;
		unsigned int sel_smallest = 0XFFFFFFFF;
		for(i=0; i<thr->keys_len; i++)
		{
			if(*flgAr)
			{
				if(thr->srch_twinAr[i]->n < sel_smallest)
				{
					sel_smallest = n;
					sel_ind = i;
				}	
			}
		}
		
		if(sel_ind > -1)
		{
			remaining--;
			flgAr[sel_ind] = 0;
			search_db(thr, sel_ind);
		}

		rem_marks = remaining*(MARKS+MARKS+...) + n_sug*(MARKS+MARKS+...);//_
	}while(thr->srch_smallest->node->marks <= rem_marks  &&  sel_ind > -1);
	if(thr->srch_smallest->node->marks <= rem_marks)	init_msw_search();
}
int init_msw_search()//
{	
	for(int a=0; a<n_checking_ars; a++)
	{
		sug_ar  = suggArs[a];
		sug_len = sug_ar[0];
		for(int b=1; b<sug_len; b++)
		{
			int w = sug_ar[b];
			//WordContainer *wc;
			//wc = get_word_container(ctbl[i], w);
			//int wlen = wc->len;
			MYSQL_RES *result = get_ads(w);
			examin_ad(result);
		}
		MARKS_T rem_marks = (n_checking_ars-a-1)*()//all options here.
		if(smallest->node->marks > rem_marks)	break;// cp_lowest_marks must be uint...
	}
}

int search_db(Thread* thr, int sel_ind)
{	
	MYSQL_RES *result = get_ads(thr, qd->keys[thr->sel_ind]);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		size_t *lens = mysql_fetch_lengths(result);
		
		ad = get_address(address_table, windAr[i]);
		//uint8_t qualified = is_qualified(ad);
		//if(qualified)
		examin_ad();
	}
}



void examin_ad(MYSQL_RES *result)
{
	MYSQL_ROW db_row;
			
	while ((db_row = mysql_fetch_row(result))) 
	{
		thr->db_row = db_row;
		unsigned long *lengths = mysql_fetch_lengths(result);
		if (lengths == NULL) {
		  finish_with_error(con);
		}
		n_db_wid = lengths[BLENDS_TBL_FIELD]/4;// blend contains 4 bytes;
		if(db_row[DB_DUP_FIELD] | thr->dup)	examin_dup_ad(thr, n_db_wid);
		else	examin_simple_ad(thr, n_db_wid);
	}
	
}

void examin_simple_ad(Thread* thr, CL_WLIM_T n_db_wid)
{
	thr->cp_blenders_marks = 0;
	int sug_ars_ind = 0;
	unsigned int keys_len = qd->keys_len;
	
	for(size_t i=0; i<keys_len; i++)
	{
		WIDSIZE_T wid = qd->_keys[i];// condition for matching here.
		if(wid)	resolve_simple_wid(thr, n_db_wid, wid, i);
		else	thr->sug_indAr[sug_ars_ind++] = i;
	}
	if(me->mat_rows_len)
	{
		resolve_simple_sug_wid(thr, n_db_wid);
		mat_handler(thr);
	}
	else	calculate_score();
	insert_ad_node(ad, thr->db_row[DB_RATTING_FIELD] + thr->blenders_marks);
}

void examin_dup_ad(Thread* thr, CL_WLIM_T n_db_wid)
{
	thr->cp_blenders_marks = 0;
	int sug_ars_ind = 0;
	unsigned int keys_len = qd->keys_len;
	
	wid_marks = 0;
	for(size_t i=0; i<keys_len; i++)
	{
		WIDSIZE_T wid = qd->_keys[i];// condition for matching here.
		if(wid)	wid_marks += resolve_dup_wid(thr, n_db_wid, wid, i);
		else	sug_indAr[sug_ars_ind++] = i;
	}
	if(me->mat_rows_len)
	{
		resolve_sug_dup_wid(thr, n_db_wid);
		mat_handler(mat, n_rows);
	}
	else	calculate_score(thr);
	insert_ad_node(ad, thr->db_row[DB_RATTING_FIELD] + thr->blenders_marks);
}


void calculate_score(Thread* thr)
{
	MARKS_T c_marks = 0;//1
	for(size_t i=0; i<klen; i++)
	{
		Blender* b = thr->cl_blendAr[k];
		if(b)
		{
			c_marks += get_pos_marks(my, b->db_wind);//2,3
			//n_all_words, where duplication is counted. how much times is this wid/word (n_this_words=times) duplicated.
			if(b->type == 2)
			{
				c_marks += ((thr->n_all_words - b->n_this_words) / thr->n_all_words) * global.marks_ar[SUG_UNIQUENESS_MARKS];//5 Uniqueness Quality.
				c_marks += global.marks_ar[SUG_WID_MARKS];//1
				c_marks += ((thr->n_quality_num - b->msw_quality) / thr->n_quality_num) * global.marks_ar[SUG_MSW_QUALITY_MARKS];//4 Miss Spelled Quality.
			}
			else
				c_marks += ((thr->n_all_words - b->n_this_words) / thr->n_all_words) * global.marks_ar[COR_UNIQUENESS_MARKS];//5 Uniqueness Quality.
		}			
	}
	if(thr->cp_blenders_marks<c_marks)
		thr->cp_blenders_marks = c_marks;
		
}



void insert_ad_node(ad, cp_marks)
{
	if(cp_marks >= me->pp_marks || cp_marks < me->np_marks)
		return;
	
	//slen = nodeAr[k]->col_lenAr[j];
	//WRITE_LE2(conf_buffer, slen);
	//strncpy(data_buffer, nodeAr[i]->col_valAr[j], slen);
	//data_buffer += slen;
	
	struct TupleNode *node;
	if(total_nodes<TOTAL_NODES)
	{
		node = thr->nodeAr[total_nodes++];
		//node = malloc(sizeof(TupleNode));
		for(int i=0; i<n_col; i++)
		{
			int len = strlen(ad->ar[i]);
			node->col_valAr[i] = malloc(len);
			node->col_lenAr[i] = len;
			strncpy(node->col_valAr[i], ad->ar[i], len);
		}
	}
		
	else
	{
		deleteSmallestNode(&root, smallest);
		node = smallest->node;
		
		int len = strlen(ad->ar[i]);
		node->col_lenAr[i] = len;
		node->col_valAr[i] = realloc(len);
		strncpy(node->col_valAr[i], ad->ar[i], len);
	}
	node->marks = marks;
	//node->h1ad = ad;
	//node->addressInd = windAr[i];
	node->right = node->left = NULL;
	insert(&root, node);
	if(total_nodes == TOTAL_NODES)
	{
		smallest->node = NULL;
		getSmallestNode(root, smallest);
		np_marks = smallest->node->marks;
	}
}



does_dup_exist()
{
	uint16_t n;
	if(klen<16) n = 63;
	else
	{
		n=7*klen;
		n = ifloor_of_2(n)-1;
	}
	int chkAr[n] = {0};
	for(int i=0; i<klen; i++)
	{
		size_t h = widAr[i]&n;//equal to widAr[i]%n;
		if(chkAr[h])
		{
			WIDSIZE_T wid = widAr[i];
			for(int j=chkAr[h]; j<klen; j++)
			{if(wid == widAr[j]){ dup = 1; break;}}
		}
		else	chkAr[h] = i+1;
	}
}

MARKS_T get_pos_marks(Thread* my, db_wind, char wtype)// old blending
{ 
	MARKS_T marks;
	db_wind <<= 2;
	char* ptr = thr->db_pos_buf+db_wind;
	Locator* ob = thr->pblender;
	 
	char m = *ptr++;
	char l = *ptr++;
	char p = *ptr++;
	char i = *ptr;

	if(m!=ob->m&&p==0&&ob->p==ob->l||m==ob->m&&l==ob->l&&p==ob->p+1)
	{
		if(wtype < 2){
			marks = global.marks_ar[COR_BLEND_MARKS];
			if(ob->i+1 == i)
				marks += global.marks_ar[COR_INDEX_MARKS];
		}
		else{
			marks = global.marks_ar[SUG_BLEND_MARKS];
			if(ob->i+1 == i)
				marks += global.marks_ar[SUG_INDEX_MARKS];
		}
	}
	ob->p = p; ob->m = m;  ob->l = l; ob->i = i;
	return marks;
}


