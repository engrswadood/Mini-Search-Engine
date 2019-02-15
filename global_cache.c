#include "global_cache.h"
void init_address_app(uint32_t nthreads)
{
	ctbl = createCtTables();
	query_data = malloc(nthreads * sizeof(QUERY_DATA));
	address_table = create_address_tbl(TOTAL_INITIAL_ADDRESSES);
	container_table	= create_container_tbl(TOTAL_INITIAL_CONTAINERS);
	
	
	load_address_db();
	init_query_obj();
}
void init_query_obj()// web ba masal kawi.
{
	//addationaly we will be having a container for every wid.
	//srchQuery has not been coded yet.
	int i;
	query_data->_remaingkeysAr = malloc(USER_WORDS_LEN*sizeof(char));
	query_data->_keys = malloc(USER_WORDS_LEN*sizeof(int *));
	query_data->suggestedAr = malloc(TOTAL_MISS_SPFELLED*sizeof(int *));
	for(i=0; i<TOTAL_MISS_SPFELLED; i++)
		query_data->suggestedAr[i] = malloc(TOTAL_SUGGESTIONS*sizeof(int *));
	
	query_data->_result = malloc(TOTAL_NODES*sizeof(TupleNode *));
	for(i=0; i<TOTAL_NODES; i++)
		query_data->_result[i] = malloc(sizeof(TupleNode));
	
	query_data->qry_rply = malloc(QRY_RPLY_SIZE);
	query_data->con = get_connection();
}
