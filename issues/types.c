//----
#define CL_SCHLIM_T	uint8_t;
#define CL_SCHLIM_MAX		0XFF;
//----
#define CL_WLIM_T		uint8_t;
#define CL_WLIM_MAX		0XFF;
//----
#define USR_SCHLIM_T	uint8_t;
#define USR_SCHLIM_MAX		0XFF;
//----
#define USR_WLIM_T		uint8_t;
#define USR_WLIM_MAX			0XFF;
//----
//__________common for CL & USR____________
#define W_CHLIM_T		uint8_t;
#define W_CHLIM_MAX		0XFF;
//----
#define CH_TYPE_T		uint8_t;
#define CH_TYPE_MAX			0XFF;
#define CH_SEPERATOR	0XFE;
//----
#define WIDTYPE_T		uint8_t;





enum{ DB_DUP_FIELD, DB_WIDS_FIELD, DB_BLENDS_FIELD, DB_RATTING_FIELD }

//--User Defined Types
typedef struct{
	Blender*** mat;
	uint16_t* lenAr;
	USR_WLIM_T n_rows;
}	DB_MatObj;

typedef struct{
	CL_WLIM_T		usr_wind;
	//uint16_t		col_wind;
	WORDS_LIMIT_T	db_wind;
	char type;
}	Blender;



struct Thread{
//////////////////////////////////
////***Search Engine***//////////
	SrchTupleNode** srch_nodeAr;
	uint16_t n_srch_nodes;
	SrchTwinNode* srch_smallest;
	
	uint16_t sel_ind;
	
	uint32_t blend_bytes_n;
	char* blend_q;
	
	uint32_t blend_len;
	uint32_t* blendAr;
	
	uint32_t n_eng_pri_nodes;
	
	CL_W_LIM_T	*db_flgAr;//need to be reset.
	
	USR_WLIM_T	*sug_indAr;
	WIDTYPE_T** suggArs;
	USR_WLIM_T n_msw;
	
	Blender*** mat;
	USR_WLIM_T* mat_lenAr;
	uint16_t n_mat_rows;

	
//////////////////////////////////
////***Dictionary***//////////	
	//uint64_t*	corgAr	= thr->corgAr;//!grp belong only to dic
	uint32_t	usr_bytes_n;
	char*		usr_q;
	
	uint32_t	upd_bytes_n;
	char*		upd_q;
	
	uint32_t n_dic_pri_nodes;// to be reset to zero.
	
	uint32_t n_msw;// to be reset for every request.
	WIDSIZE_T** swArs[ub];//memory to allocated at loading the app.
	uint16_t** smArs[ub];//memory to allocated at loading the app.
	//uint64_t** sgArs[ub];//!grp memory to allocated at loading the app.
	
	
	size_t dic_tree_size;// for suggestions.
	
//////////////////////////////////
////***Common***//////////
	uint8_t op_mode;
	USR_WLIM_T* msw_indAr;// will be NULL.
	
	
	
}
typedef   struct Thread		Thread;

struct Connection{
//////////////////////////////////
////***Search Engine***//////////	
	

	
//////////////////////////////////
////***Dictionary***//////////	
	//uint64_t*	corgAr	= thr->corgAr;//!grp belong only to dic
	
	
//////////////////////////////////
////***Common***//////////
	
	
	
}
typedef   struct Connection		Connection;


struct Thread
{
	///////////////////////////////////////////////////
	/////////////////////***Search Engine***///////////
	CL_WLIM_T* db_flgAr;
	CL_WLIM_T* cl_wid_flgAr
};
typedef struct Thread Thread;

struct Configured
{
	char*		pk;//primary key/ index key.
	char*		table;
	char**		columns;
	uint16_t	n_cols;// to be calculated.
	
}
typedef struct Configured Configured;

struct AppData
{
	
}
typedef struct AppData AppData;












//*****************SETTING VARIABLES******************//
//*****************SETTING VARIABLES******************//
setting.tbl_name);
sql_len += setting.tbl_name_len;

setting.primary_key);
	strcpy(sql+sql_len, setting.primary_key_len);
	
	
	
//*********************Requirements for the developer****************************//
//1		developer will have to create 3 columsn in the associated table.
//2		developer will have to configure/tell fields from the associated table to this engine.
//3		developer will have to configure/tell the name of the primary key/column.

name, image_url, title, skills, address//id// and the 





enum OperationMode	{SEARCH_QUERY,  UPDATE_QUERY, DELETE_QUERY};
enum ErrorMode		{TOO_MUCH_LENGTHY_QUERY };