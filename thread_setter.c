#include "global_cache.h"

void set_thr_srch_props()
{
	/////////////////////***Search Engine***//////////
	thr->msw_indAr = malloc(n_msw*sizeof(WIDTYPE_T));
	memcpy(thr->usr_blendAr, thr->blender_store, key_len*(Blender*));
	thr->cl_wid_flgAr = calloc(sizeof(CL_WLIM_T)*W_CHLIM_MAX);// MSW.
	thr->cl_wid_flgAr = calloc(sizeof(CL_WLIM_T)*W_CHLIM_MAX);
	
	thr->srch_smallest->node = thr->nodeAr[TOTAL_NODES-1];
	thr->srch_smallest->node->marks = 0;
}

void clr_thr_srch_props()
{
	/////////////////////***Search Engine***//////////
	free(thr->msw_indAr);
	for(int i=0; i < n_nodes; i++) free(thr)
}

void set_thr_upd_props()
{
	
}

void clr_thr_upd_props()
{
	
}

void set_thr_del_props()
{
	
}

void clr_thr_del_props()
{
	
}

void load_thr_props(Thread* thr)
{
	/////////////////////***Search Engine***///////////
	thr->blender_store = malloc(USR_WLIM_MAX*sizeof(Blender*));//this will be equal to the USR_WLIM_MAX.
	for(int i=0; i<USR_WLIM_MAX; i++)	thr->blender_store[i] = malloc(sizeof(Blender));
	thr->usr_blendAr = malloc(USR_WLIM_MAX*sizeof(Blender*));
	memset(sizeof(thr->cl_wid_flgAr, 0, sizeof(CL_WLIM_T)*W_CHLIM_MAX);
	
	thr->n_srch_nodes = 0;
	uint16_t n_nodes = TOTAL_ROWS_ON_PAGE * 5;
	thr->srchTupleNode = malloc(sizeof(SrchTupleNode*) * n_nodes);
	for(int i=0; i < n_nodes; i++)
	{
		thr->srchTupleNode[i]->col_lenAr = malloc(sizeof(uint16_t) * Configured.n_viewing_col);
		thr->srchTupleNode[i]->col_lenAr = malloc(sizeof(char*) * Configured.n_viewing_col);
		for(int j=0; j<Configured.n_viewing_col; j++)
			thr->srchTupleNode[i]->col_valAr[j] = NULL;
	}
	
	thr->srch_smallest = malloc(sizeof(SrchTwinNode));	
		
}
