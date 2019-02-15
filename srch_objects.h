/*int8_t
int16_t
int32_t
int64_t
uint8_t
uint16_t
uint32_t
uint64_t*/
//****************Configurating Macros****************//
#ifndef GLOBAL_CACHE_FILE
#define GLOBAL_CACHE_FILE



#include <my_global.h>
#include <mysql.h>

///////////////////////////////////////////////
struct SrchTupleNode
{
    struct SrchTupleNode *leftchild;
	
    uint32_t marks;
	char**	col_valAr;
	uint16_t* col_lenAr;
	
	//struct H1Adress *_ad;
	//unsigned int _adi;
	//WORD_SIZE _wordContainer;
	
    struct SrchTupleNode *rightchild;
} ;
typedef struct SrchTupleNode
struct SrchTwinNode
{
	struct SrchTupleNode *par;
	struct SrchTupleNode *node;
};
typedef struct SrchTwinNode
////////////////////////////////////////////////


typedef struct{
	Blender*** mat;
	uint16_t* lenAr;
	WORDS_LIMIT_T n_rows;
}	DB_MatObj;

typedef struct{
	WORDS_LIMIT_T	cl_wind;
	uint16_t		col_wind;
	WORDS_LIMIT_T	db_wind;
	char type;
}	Blender;

typedef struct
{
	WORDS_LIMIT_T	m;
	WORDS_LIMIT_T	p;
	WORDS_LIMIT_T	l;
	WORDS_LIMIT_T	i;
} Locator;
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

struct Group_t
{
	unsigned int w;
	struct word_t *next;
	uint64_t gBits;
};

struct GroupTbl_t
{
	Group_t **groupAr2;
	int size;
	int totalItems;
};

struct ad_t
{
	int				id;
	uint64_t*		bAr;
	WIDSIZE_T*		wAr;
	int				len;//size of table.

};
typedef struct ad_t ad_t;

struct adtbl_t
{
	ad_t	**adArs;
	int					cur;
	/////////////////////////////
	WIDSIZT_T			top;
	WIDSIZT_T*			stack;
};
typedef struct adtbl_t adtbl_t;

struct con_t{
	unsigned int wid;
	struct con_t *next;
	AD_LIMIT_T *iAr;//
	unsigned int len;
};
typedef struct con_t con_t;
struct contbl_t
{
	con_t		***hArs;
	short 		hArsLen;
	int			hTotalBuc;
	int			nItems;
};

struct SugList
{
	short arsLen;
	int **sug_ar;
};
typedef struct SugList SugList;

struct Dictionary
{
	int ***fwAr;
	int **rvAr;
}
typedef struct Dictionary Dictionary;


	
typedef struct
{
	int			*sq;//srchQuery;//sq
	int			id;//_id;//id
	wTYPE		*pos;//_pos;//pos
	int			sKeyInd;//_srchingKeyInd;// the one flaged for being searched//sKInd
	char		*remKeysL;//_remaingkeysAr;//remKeysAr
	short		rem;//_remaining;//rem
	char		ver;//verified;//ver
	
	int			*keys;//k
	int			*kLen;//_keysLen;//kLen
	int			**sugL2;//suggestedAr//sugAr;
	int			n_msw;
	
	char		thresh;//threshold;//thresh
	char		wSrch;//_webSearch;//wSrch
		
	TupleNode	**_result;//result
	char		tn;//totalNodes;//tn
	TupleNode	*root;//_root;//root;
	char		*qry_rply;//_
	MYSQL		*sqlcon;
} QueryData;

/*struct BuffVars{
	uint16_t comb_r;
	uint16_t threshold;
	uint64_t cor_bits;
	uint64_t off_bits;
}*/


extern ADDRESS_TABLE		address_table;
extern CONTAINER_TABLE		container_table;
extern QUERY_DATA			**query_data;



#endif