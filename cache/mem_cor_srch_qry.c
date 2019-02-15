#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
struct MemCorSrchQry//Memory correct words search query (mcsq)
{
	//uint32_t h_ind;// hash index in priority-nodes-list.
	REF_COUNT_T ref_count;//how much pointers point to mcsq in mcwc.
	char* str;
	SCHLIMIL_T len;
	UniqueTbl* ut;
	MemCorPriNode* mcpn;//This is used for "if it is retreived, then it should be placed in the first position of priority list". This is also used "when it is deleted by word(insertion/updation) then it also has to delete the reference in the priority list."
	
};
typedef struct MemCorSrchQry MemCorSrchQry;
struct MemMCSQ_Tbl{
	MemCorSrchQry		***hArs;
	short 				hArsLen;//
	int					hTotalBuc;
};
typedef struct MemMCSQ_Tbl MemMCSQ_Tbl;


void print_dual_item(MemCorSrchQry *, int );
void resize_dtbl_int_array(MemMCSQ_Tbl *);
void add_dual_item(MemMCSQ_Tbl *, char *);
void delete_dual_item_by_str(MemMCSQ_Tbl *, char* );
MemCorSrchQry * get_ditem_by_str(MemMCSQ_Tbl *, char * );


void print_dual_item(MemCorSrchQry *item, int i)
{
	printf("\nind=%d\t", i);
	printf("intID=%d\t", item->num);
	printf("strID=%s\t\t", item->usr_q);
	printf("similar=%d", item->_total);
}

void resize_dtbl_str_array(MemMCSQ_Tbl *ht)
{
	//if(ht->delAddMode>-1) return;
	//ht->delAddMode = 1;
	int rhArsLen == ht->hArsLen<<1;
	ht->hArs = realloc(rhArsLen * sizeof(MemCorSrchQry**));
	for(int j=hArsLen; j<rhArsLen; j++)
		ht->hArs[j] = calloc((IND_ANDING+1) * sizeof(MemCorSrchQry*));
	///////////////////////////////////
	int len	 = IND_ANDING+1;
	int rSize = rhArsLen<<IND_SHIFTING;
	for(int j=0; j<ht->hArsLen; j++)
	{
		for(k=0; k<len; k++)
		{
			MemCorSrchQry *item = hArs[j][k];
			hArs[j][k] = NULL;
			while(item)
			{
				MemCorSrchQry *nitem = item->next;
				int i = str_hash(rSize, item->usr_q, item->usr_bytes_n);
				item->next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
				hArs[i>>IND_SHIFTING][i&IND_ANDING] = item;
				item = nitem;
			}
		}	
	}
	ht->hArsLen = rhArsLen;
	ht->hTotalBuc = rSize;
}

MemCorSrchQuery*  mem_add_cor_mcsq(Thread* thr, char** pageAr)//(char* sval, CHLEN_T chlen, char** pageAr, wordAr, lenAr, wlen)
{
	CHLIMIT_T chlen = thr->qlen;
	char* q = thr->query;
	MemCorSrchQuery  ***hArs = ht->hArs;
	
	int i = str_hash(ht->hTotalBuc, q, chlen);//_ strSize
	MemCorSrchQuery *adding_item = malloc(sizeof(MemCorSrchQuery));
	
	adding_item->usr_q = thr->usr_q;
	adding_item->usr_bytes_n = thr->usr_bytes_n;
	adding_item->next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
	hArs[i>>IND_SHIFTING][i&IND_ANDING] = adding_item;
	return adding_item;
}

void mem_delete_cor_mcsq(MemCorSrchQuery* sq)
{
	CHLIMIT_T chlen = sq->usr_bytes_n;
	char* q = sq->usr_q;
	int i = str_hash(ht->hTotalBuc, q, chlen);
	MemCorSrchQuery  ***hArs = ht->hArs;
	MemCorSrchQuery* item = hArs[i>>IND_SHIFTING][i&IND_ANDING];
	
	while(item)
	{
		if(item->usr_bytes_n == chlen)
			if(!strncmp(strKey, item->usr_q, chlen ))	break;
		last_item = item;
		item = item->next;
	}
	//if(item)//This if/check is useless as we know that item must exists for the word MemCorSrchQuery/mcsq string/sentence.
	//{
		if(last_item) last_item->next = item->next;
		else hArs[i>>IND_SHIFTING][i&IND_ANDING] = item->next;
		free(item->usr_q);
		free(item);
		
	//}
	//return 0;
}

MemCorSrchQry* mem_get_cor_mcsq(MemMCSQ_Tbl *ht, char *strKey, SCHLIMIL_T chlen)
{
	int i = str_hash(ht->hTotalBuc, strKey, chlen);
	MemCorSrchQry *item = ht->hArs[i>>IND_SHIFTING][i&IND_ANDING];
	while(item)
	{
		if(item->usr_bytes_n == chlen && !strncmp( strKey, item->usr_q, chlen))		break;
		item = item->next;
	}
	return item;
}







void traverse_dual_tbl(MemMCSQ_Tbl *ht)
{//
	printf("\n************************************* **************");
	
	
	printf("\ntotal************************************ **************%d", ht->hTotalBuc);
}


MemMCSQ_Tbl* create_dual_tbl(int size)
{
	MemMCSQ_Tbl *ht = malloc(sizeof(MemMCSQ_Tbl));
	ht->hArs =  malloc(size * sizeof(MemCorSrchQry**));
	ht->hArsLen = size;
	for(int j=0; j<size; j++)
		ht->hArs[j] = malloc((IND_ANDING+1) * sizeof(MemCorSrchQry*));
	
	/*ht->intArs =  malloc(sizeof(MemCorSrchQry*));
	ht->intArs[0] = malloc(size*sizeof(MemCorSrchQry));
	
	
	
	ht->intArsLen = 1;
	ht->cur = 0;
 
	ht->hTotalBuc = size<<IND_SHIFTING;
	ht->_biggestSimilarWords = 0;
	
	ht->top = 0;
	ht->stack = NULL;*/
	
	
	return ht;
}




int main( int argc, char **argv ) {

	MemMCSQ_Tbl *hashtable = create_dual_tbl(7);
	

	
char **strings;
strings = malloc(15*sizeof(char *));
strings[0] = malloc(20);
strings[1] = malloc(20);
strings[2] = malloc(20);
strings[3] = malloc(20);
strings[4] = malloc(20);
strings[5] = malloc(20);
strings[6] = malloc(20);
strings[7] = malloc(20);
strings[8] = malloc(20);
strings[9] = malloc(20);
strings[10] = malloc(20);
strings[11] = malloc(20);
strings[12] = malloc(20);
strings[13] = malloc(20);
strings[14] = malloc(20);


strcpy(strings[0],"0bslam");
strcpy(strings[1],"1bslam");
strcpy(strings[2], "2cslam");
strcpy(strings[3], "3dslam");
strcpy(strings[4], "4eslam");
strcpy(strings[5], "5fslam");
strcpy(strings[6], "6gslam");
strcpy(strings[7], "7hslam");
strcpy(strings[8], "8aslam");
strcpy(strings[9], "9aslam");
strcpy(strings[10], "A-fslam");
strcpy(strings[11], "B-6gslam");
strcpy(strings[12], "C-hslam");
strcpy(strings[13], "D-aslam");
strcpy(strings[14], "E-aslam");

	
	MemCorSrchQry *item;
	int i;

	for( i=0; i<15; i++)
	{	
		printf("\n%d<-----kk-->%s",i, strings[i]);
		add_dual_item(hashtable, strings[i]);
		
	}
	
	printf("\nTraversal******************%d", get_total_dual_items(hashtable));
	traverse_dual_tbl(hashtable);
	printf("\nResized******************");
	//hashtable = resize_DualTable(hashtable, hashtable->_singleLen*2 );
	//traverse_dual_tbl(hashtable);
	printf("\nDeleted*****************");
	delete_dual_item_by_str(hashtable, "C-hslam");

	traverse_dual_tbl(hashtable);
	
	printf("\nGot************************%d", get_total_dual_items(hashtable));
	item = get_ditem_by_num(hashtable, 2);
	
	if(item)
		print_dual_item(item, 0);	
}
