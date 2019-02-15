#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


void print_dual_item(DualNode *, int );
void resize_dtbl_int_array(DualAssocArray *);
void add_dual_item(DualAssocArray *, char *);
void delete_dual_item_by_str(DualAssocArray *, char* );
DualNode * get_ditem_by_str(DualAssocArray *, char * );


void print_dual_item(DualNode *item, int i)
{
	printf("\nind=%d\t", i);
	printf("intID=%d\t", item->num);
	printf("strID=%s\t\t", item->str);
	printf("similar=%d", item->_total);
}

void resize_dtbl_str_array(DualAssocArray *ht)
{
	//if(ht->delAddMode>-1) return;
	//ht->delAddMode = 1;
	int rhArsLen == ht->hArsLen<<1;
	ht->hArs = realloc(rhArsLen * sizeof(DualNode**));
	for(int j=hArsLen; j<rhArsLen; j++)
		ht->hArs[j] = calloc((IND_ANDING+1) * sizeof(DualNode*));
	///////////////////////////////////
	int len	 = IND_ANDING+1;
	int rSize = rhArsLen<<IND_SHIFTING;
	for(int j=0; j<ht->hArsLen; j++)
	{
		for(k=0; k<len; k++)
		{
			DualNode *item = hArs[j][k];
			hArs[j][k] = NULL;
			while(item)
			{
				DualNode *nitem = item->next;
				int i = str_hash(rSize, item->str, item->chlen);
				item->_next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
				hArs[i>>IND_SHIFTING][i&IND_ANDING] = item;
				item = nitem;
			}
		}	
	}
	ht->hArsLen = rhArsLen;
	ht->hTotalBuc = rSize;
}



void mem_delete_cor_mcwc(MemCorSrchQuery* sq, char* w, uint32_t len)
{
	MemMCWC_Tbl* ht = global->mcwc_tbl;
	MemCorWordCont*** hArs = global->mcwc_tbl->hArs;
	int i = str_hash(ht->hTotalBuc, key, chlen);//_ strSize
	
	int j = i&IND_ANDING;
	i >>= IND_SHIFTING;
	
	MemCorWordCont* last_item = NULL;
	MemCorWordCont* item = hArs[i][j];
		
	while(item)
	{
		if(item->chlen == chlen)
			if(!strncmp(strKey, item->str, chlen ))	break;
		last_item = item;
		item = item->_next;
	}
	
	//if(item)//This if/check is useless as we know that item must exists for the word MemCorSrchQuery/mcsq string/sentence.
	//{		
	MemCorSrchQry** sqAr = item->sqAr;
	uint32_t sqlen = item->sqlen--;
	size_t k=sqlen;
	while(k)
	{
		if(sq == sqAr[k--])
		{
			--sq->ref_count;
			if(!sq->ref_count) free(sq);//_ w may require to delelte associated nodes.
			break;
		}
	}
	while(k<sqlen) {	sqAr[k] = sqAr[k]; k++;	}
	
	if(!item->sqlen)
	{
		if(last_item) last_item->_next = item->_next;
		else hArs[i][j] = item->_next;
		free(item->str);
		free(item->sqAr);
		free(item);
	}
	//}
}
MemCorWordCont* mem_delete_cor_mcwc_cont(char* w, uint32_t chlen)
{
	MemMCWC_Tbl* ht = global->mcwc_tbl;
	MemCorWordCont*** hArs = global->mcwc_tbl->hArs;
	int i = str_hash(ht->hTotalBuc, key, chlen);//_ strSize
	
	int j = i&IND_ANDING;
	i >>= IND_SHIFTING;
	
	MemCorWordCont* last_item = NULL;
	MemCorWordCont* item = hArs[i][j];
	
	
	while(item)
	{
		if(item->chlen == chlen)
			if(!strncmp(strKey, item->str, chlen ))	break;
		last_item = item;
		item = item->_next;
	}
	if(last_item) last_item->_next = item->_next;
	else hArs[i][j] = item->_next;
	return item;
	//if(item)//This if/check is useless as we know that item must exists for the word MemCorSrchQuery/mcsq string/sentence.
	//{		
	
	
	
	//free(item->str);
	//free(item->sqAr);
	//free(item);
	
	//}
}



DualNode* get_ditem_by_str(DualAssocArray *ht, char *strKey,CHLEN_T chlen)
{
	int i = str_hash(ht->hTotalBuc, strKey, chlen);
	DualNode *item = ht->hArs[i>>IND_SHIFTING][i&IND_ANDING];
	while(item)
	{
		if(item->chlen == chlen && !strncmp( strKey, item->str, chlen))		break;
		item = item->_next;
	}
	return item;
}

/*void traverse_dual_tbl(DualAssocArray *ht)
{//
	printf("\n************************************* **************");
	
	
	printf("\ntotal************************************ **************%d", ht->hTotalBuc);
}


DualAssocArray* create_dual_tbl(int size)
{
	DualAssocArray *ht = malloc(sizeof(DualAssocArray));
	ht->hArs =  malloc(size * sizeof(DualNode**));
	ht->hArsLen = size;
	for(int j=0; j<size; j++)
		ht->hArs[j] = malloc((IND_ANDING+1) * sizeof(DualNode*));
	
	ht->intArs =  malloc(sizeof(DualNode*));
	ht->intArs[0] = malloc(size*sizeof(DualNode));
	
	
	
	ht->intArsLen = 1;
	ht->cur = 0;
 
	ht->hTotalBuc = size<<IND_SHIFTING;
	ht->_biggestSimilarWords = 0;
	
	ht->top = 0;
	ht->stack = NULL;
	
	
	return ht;
}




int main( int argc, char **argv ) {

	DualAssocArray *hashtable = create_dual_tbl(7);
	

	
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

	
	DualNode *item;
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
}*/
