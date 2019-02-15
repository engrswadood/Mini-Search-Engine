struct MemCorSrchQry//Memory correct words search query (mcsq)
{
	//uint32_t h_ind;// hash index in priority-nodes-list.
	REF_COUNT_T ref_count;//how much pointers point to mcsq in mcwc.
	char* usr_q;
	SCHLIMIL_T usr_bytes_n;
	char** pageAr;
	uint16_t n_pages;
	MemCorPriNode* mcpn;//This is used for "if it is retreived, then it should be placed in the first position of priority list". This is also used "when it is deleted by word(insertion/updation) then it also has to delete the reference in the priority list."
	
};
typedef struct MemCorSrchQry MemCorSrchQry;

struct MemCorWordCont// //memory correct wid/word (mcwc)
{
	char* w;
	CHWORDLIMIT_T chlen;
	uint32_t sqlen;
	MemCorSrchQry** sqAr;//
}
typedef struct MemCorWordCont MemCorWordCont;

struct MemCorPriNode//memory correct priority node (mcpn)
{
	PriorityNode* back;
	PriorityNode* next;
	MemCorSrchQuery* sq;//This is just used for "if its the last node in the priority list and needed to be deleted then it must have reference to the actual contents once query came for".
};
typedef struct MemCorPriNode MemCorPriNode;
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
struct MemMCSQ_Tbl{
	MemCorSrchQry		***hArs;
	short 				hArsLen;//
	int					hTotalBuc;
};
typedef struct MemMCSQ_Tbl MemMCSQ_Tbl;


struct MemMCWC_Tbl{
	struct	MemCorWordCont		***hArs;
	short 				hArsLen;//
	int					hTotalBuc;
};
typedef struct MemMCWC_Tbl MemMCWC_Tbl;

struct MemMCPN_Tbl
{
	MemCorSrchQry*		sq;
	int					hTotalBuc;
	
	MemCorSrchQry*		start;
	MemCorSrchQry*		end;
};
typedef struct MemMCPN_Tbl MemMCPN_Tbl;















/*MemCorSrchQuery* get_mem_cor_val(char* sval, chlen)
{
	MemCorSrchQuery* so = mem_get_search_obj(sval, chlen);
	if(so)
	{
		MemCorNode mcpn = so->mcpn;
		mcpn->next = mem_cor_start;
		mem_cor_start = mcpn;
	}
	return so;
}*/
//mem_get_cor_mcsq(MemMCSQ_Tbl *ht, char *strKey, SCHLIMIL_T chlen)
SrchPage* void srch_cor_mcm(Thread* thr)//char* q, uint32_t page_number)
{
	MemCorSrchQuery* sq = mem_get_cor_mcsq(AppData.mcsq_tbl, thr->query, thr->query_len);
	SrchPage* sp = NULL;
	if(sq)
	{
		if(thr->page_number < sq->n_pages){
			sp = sq->pageAr[thr->page_number];
		}
		else
		{
			thr->pp_marks = sq->pageAr[sq->n_pages-1]->lowest_marks;
			thr->page_number = sq->n_pages;
			thr->unique_tbl = sq->unique_tbl;
		}
		mem_prioritise_cor_mcpn(sq->mcpn);// We may need to update it after sending info over the socket.
	}
	else
	{
		thr->page_number = 0;
		thr->pp_marks = MAX_MARKS;
	}
	return sp;
}

void add_cor_mcm(Thread* thr, char** pageAr)//(char* sval, CHLEN_T chlen, char** pageAr, wordAr, lenAr, wlen) mcm /mem_cor_main
{
	MemCorSrchQuery* sq = mem_add_cor_mcsq(thr, pageAr);
	mem_add_mcpn(sq);
	
	if(mem_cor_total > MEM_COR_TOTAL)
	{
		char**	wordAr2 = malloc(MAX_WORDS*sizeof(char*));
		CHLIMIT_T*	lenAr2 = malloc(MAX_WORDS*sizeof(CHLIMIT_T));
		
		MemCorPriNode* mcpn =  mem_delete_cor_mcpn_end();
		MemCorSrchQuery* del_sq = mcpn->sq;
		int wlen = get_words_list(del_sq->str, del_sq->len, wordAr2, lenAr);//_
		
		for(int i=0; i<wlen; i++)
			mem_delete_cor_mcwc(del_sq, wordAr2[i], lenAr2[i]);
		mem_delete_cor_mcsq(del_sq);
		free(mcpn);
	}
	else mem_cor_total++;
	
	for(int i=0; i<wlen; i++)
		mem_add_cor_word(sq, wordAr[i], lenAr[i]);
}


void delete_cor_mcm(char** keyAr, int* lenAr, size_t wlen);// it will delete all items which have any of word in query.
{
	for(int i=0; i<wlen; i++)
	{
		MemCorWordCont* mcwc = mem_delete_cor_mcwc_cont(ar[i], lenAr[i]);//ar[i]->sqAr;
		MemCorSrchQuery** sqAr = mcwc->sqAr;
		
		uint32_t sqlen = item->sqlen;
		for(size_t j=0; j<sqlen; j++)
		{
			MemCorSrchQuery* sq = sqAr[j];
			--sq->ref_count;
			if(!sq->ref_count)
			{
				MemCorPriNode* pn = sq->mcpn;
				mem_delete_cor_mcsq(sq);
				mem_delete_cor_mcpn(pn);				
			}
		}
	}
}

void update_cor_mcm(Thread* thr, char* sval, CHLEN_T chlen, char** pagesAr, n_pages)//mcm means mem_cor_main
{
	MemCorSrchQuery* sq = mem_get_cor_mcsq(thr->sval);
	increase_pages(sq, pagesAr, n_pages);
}

increase_pages(SrchQuery* sq, char** epageAr, n_pages);
{
	int i = sq->n_pages;
	sq->n_pages += n_pages;
	sq->pageAr = realloc(sq->pageAr, sq->n_pages * sizeof(char*));
	
	size_t j=0;
	while(i<sq->n_pages)
		sq->pageAr[i++] = epageAr[j++];
	
	return sq->pageAr;
}

char**  create_pages(srch_nodeAr, total_items, int *n_pages)
{
	size_t ub = thr->n_srch_nodes-1;
	SrchNode** srch_nodeAr = thr->srch_nodeAr;
	
	char** pageAr = NULL;

	uint32_t n_bytes = 0;
	size_t page_ind = 0;
	size_t k=0;

	total_rows = 0;
	for(int i=0; i<=ub; i++)	//name, image_url, title, skills, address(better for clouding)//id// and the developer will also have to create 3 columsn in the associated table. 
	{
		for(int j=0; j<Configured.n_viewing_col; j++)
			n_data_bytes += srch_nodeAr[i]->col_lenAr[j];
		if(++total_rows == TOTAL_ROWS_ON_PAGE || i==ub)
		{
			pageAr = realloc(sizeof(char*)*(page_ind+1));
			
			n_conf_bytes = total_rows*global_obj.n_viewing_col*2;//(global_obj.n_viewing_col*2) is for each field length of rows 
			n_bytes = n_data_bytes+n_conf_bytes+4+2;//4 is used to recognize the number of bytes for data. 2 is used to recognize the number of rows/records.

			char* buffer = pageAr[page_ind++] = malloc(n_bytes);
			char* sizes_buffer = buffer;
			
			
			WRITE_LE4(sizes_buffer, n_bytes);// total bytes of data to be followed.
			WRITE_LE2(sizes_buffer, total_rows);// total rows
			
			char* conf_buffer = buffer;
			char* data_buffer = buffer+n_conf_bytes;
			
			for(;k<i; k++)
			{
				for(int j=0; j<Configured.n_viewing_col; j++)// Configured, AppData, macros/static_conf
				{
					slen = srch_nodeAr[k]->col_lenAr[j];
					WRITE_LE2(conf_buffer, slen);
					
					strncpy(data_buffer, srch_nodeAr[i]->col_valAr[j], slen);
					data_buffer += slen;
				}
			}
			
			n_bytes = 0;
			total_rows = 0;
		}
	}
	*n_pages = page_ind;
	return pageAr;
}

/*struct SrchResult
{
	char** pages;
	uint32_t n_pages;
}
struct SrchPage
{
	char* buf;
}
*/
/*struct SrchResult
{
	SrchPage** pages_buffers;
	uint32_t n_pages;
}
struct SrchPage
{
	char* buf;
}*/