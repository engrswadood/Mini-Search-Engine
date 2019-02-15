MARKS_T resolve_simple_wid(Thread* thr, CL_WLIM_T n_db_wid, WIDTYPE_T wid, USR_WLIM_T usr_wind)//(ad_wiAr, ad_pbAr, ad_len, sr_wpAr, sr_spAr, sr_bpAr);//p_bytes= wp, sp, bp//word position,suggesting position,blend position.
{
	int16_t m = bin_search_for_wid(thr->db_row[WIDS_TBL_FIELD], n_db_wid, wid);
	if(m>-1)
	{
		thr->cl_wid_flgAr[m] = 1;
		thr->usr_blendAr[usr_wind] = thr->blender_store[usr_wind];
		thr->usr_blendAr[usr_wind]->type = 0;
		thr->usr_blendAr[usr_wind]->db_wind = m;
	}
	return global.marks_ar[COR_WORD_MARKS];
}

void resolve_simple_sug_wid(Thread* thr, CL_WLIM_T n_db_wid)//p_bytes= wp, sp, bp//word position,suggesting position,blend position.
{
	WIDTYPE_T** suggArs = thr->suggArs;
	USR_WLIM_T* mat_lenAr = thr->mat_lenAr;
	USR_WLIM_T n_msw = thr->n_msw;
	
	Blender*** mat = thr->mat;
	CL_WLIM_T* cl_wid_flgAr = thr->cl_wid_flgAr[m];
					
	uint16_t row = 0;
	for(int a=0; a<n_msw; a++)
	{
		WIDTYPE_T* sug_ar  = suggArs[a];
		sug_len = sug_ar[0];
		size_t c=0;
		for(int b=1; b<sug_len; b++)
		{
			//mat[ars_ind][0] = 0;//setting length to zero.
			WIDTYPE_T wid = sug_ar[b];
			int16_t m = bin_search_for_wid(thr->db_row[WIDS_TBL_FIELD], n_db_wid, wid);
			if(m>-1 && !cl_wid_flgAr[m])
			{
				uint32_t rsize = sizeof(Blender*)*(c+1);
				INC_MAT_ROW_MEM(mat[row], mat_sizeAr[row], rsize);
				mat[row][c]->usr_wind = a;//it will be access from there.
				mat[row][c]->cl_col = b;
				mat[row][c]->db_wind = m;//it will be access from there.
				mat[row][c++]->type = 1;//it will be access from there.
			}
		}
		if(c)
		{
			mat_lenAr[row] = c;
			row++;
		}	
	}
	thr->n_mat_rows = row;
}


void resolve_dup_wid(thr, n_db_wid, WIDTYPE_T wid, USR_WLIM_T usr_wind)//thr, db, wid, usr_wInd)
{
	int16_t m = bin_search_for_wid(thr->db_row[WIDS_TBL_FIELD], n_db_wid, wid);
	size_t row_ind = thr->n_mat_rows;
	//int16_t wInd = m;
	if(m>-1)
	{
		//uint16_t located_ind = m;
		char* ch_ptr = --m*sizeof(WIDTYPE_T);
		
		while(m>-1 &&  IS_WID_EQUAL(ch_ptr, w))	{ch_ptr -= sizeof(WIDTYPE_T); m--;}
		int16_t st = ++m;
		ch_ptr = ++m*sizeof(WIDTYPE_T);
		while(m<len && IS_WID_EQUAL(ch_ptr, w))	{ch_ptr += sizeof(WIDTYPE_T); m++;}
		
		if((m - st) == 1)
		{
			m--;
			if(!thr->cl_wid_flgAr[m])
			{
				thr->cl_wid_flgAr[m] = usr_wInd;
				Blender* b = thr->usr_blendAr[usr_wind] = thr->blender_store[usr_wind];
				b->usr_wind = usr_wInd;	b->db_wind = bind;	b->type = 0;
			}
			else
			{// This block comes to life when for single/one db wid there are repeated wids from client.
				if(thr->cl_wid_flgAr[m]<USR_WLIM_MAX)
				{
					Blender** row1 = mat[row_ind] = malloc(sizeof(Blender*));
					Blender** row2 = mat[row_ind+1] = malloc(sizeof(Blender*));
					
					row1[0] = malloc(sizeof(Blender));
					row2[0] = malloc(sizeof(Blender));
					
					mat_lenAr[row_ind] = mat_lenAr[row_ind+1] = 1;
					row_ind += 2;
					
					row1[0]->usr_wind = thr->cl_wid_flgAr[m];
					row1[0]->db_wind = st;
					
					row2[0]->usr_wind = usr_wInd;
					row2[0]->db_wind = st++;
					
					row1[0]->type = row2[0]->type = 1;
					thr->cl_wid_flgAr[st] = USR_WLIM_MAX;//it will create two arrays.
				}
				else
				{
					Blender** row1 = mat[row_ind++] = malloc(sizeof(Blender*));
					row1[0] = malloc(sizeof(Blender));
					row1[0]->usr_wind = usr_wInd;
					row1[0]->db_wind = st;
					row1[0]->type = 1;
				}
			}
				
		}
		else
		{
				
				Blender** mat_col = mat[row_ind] = malloc(n*sizeof(Blender*));
				int i=0;
				while(st<m)
				{
					mat_col[i] = malloc(sizeof(Blender));
					mat_col[i]->usr_wind = cl_wInd;
					mat_col[i]->db_wind = st++;
					mat_col[i++]->type = 1;
				}
				mat_lenAr[row_ind++] = n;
		}
	}
	thr->n_mat_rows = row_ind;
}



void resolve_sug_dup_wid(Thread* thr, CL_WLIM_T n_db_wid)//(db, qd, WIDTYPE_T** s_ars, ars_len, mat)//(ad_wiAr, ad_pbAr, ad_len, sr_wpAr, sr_spAr, sr_bpAr);//p_bytes= wp, sp, bp//word position,suggesting position,blend position.
{
	//mat//
	WIDTYPE_T** suggArs = thr->suggArs;
	USR_WLIM_T n_msw = thr->n_msw;
	
	Blender*** mat = thr->mat;
	USR_WLIM_T* mat_lenAr = thr->mat_lenAr;
	size_t row_ind = thr->n_mat_rows;
	for(size_t a=0; a<n_msw; a++)
	{
		WIDTYPE_T* sug_ar  = suggArs[a];
		USR_WLIM_T sug_len = sug_ar[0];
		size_t c=0;
		
		for(size_t b=0; b<sug_len; b++)
		{
			WIDTYPE_T wid = sug_ar[b];
			m = bin_search_for_wid(db->wiAr, db->len, wid);
			if(m>-1)
			{
				char* ch_ptr = --m*sizeof(WIDTYPE_T);
				char *cl_wid_flgAr = thr->cl_wid_flgAr;
				while(m>-1 && IS_WID_EQUAL(ch_ptr, w))	{ch_ptr -= sizeof(WIDTYPE_T); m--;}
				;//bring m to the position where wid hasn't been checked
				int16_t st = ++m;
				ch_ptr = ++m*sizeof(WIDTYPE_T);
				while(m<len && IS_WID_EQUAL(ch_ptr, w))	{ch_ptr += sizeof(WIDTYPE_T); m++;}//going ahead as bin_search may've returened pos at back from the checked ind's.
				uint16_t n = m - st;
				uint32_t rsize = sizeof(Blender*)*(n+c);
				INC_MAT_ROW_MEM(mat[row_ind], mat_sizeAr[row_ind], rsize);
				
				if(n > 1)
				{
					while(st<m)
					{
						mat[row_ind][c]->usr_wind = a;//sug_indAr has indexes to their associates positions in client wids.
						mat[row_ind][c]->cl_col = b;
						mat[row_ind][c]->db_wind = st++;//it will be access from there.
						mat[row_ind][c++]->type = 2;//it will be access from there.
						mat_lenAr[row_ind]++;// Incrementing length.
					}
				}
				else if(cl_wid_flgAr[m]<USR_WLIM_MAX)
				{
						mat[row_ind][c]->usr_wind = a;//sug_indAr has indexes to their associates positions in client wids.
						mat[row_ind][c]->col = b;
						mat[row_ind][c]->db_wind = m;//it will be access from there.
						mat[row_ind][c++]->type = 2;//it will be access from there.
						mat_lenAr[row_ind]++;// Incrementing length.
				}
			}
		}
		if(c)
		{
			mat_lenAr[row_ind] = c;
			row_ind++;
		}
	}
	thr->n_mat_rows = row_ind;
}







void mat_handler(Thread* thr)//for every  suggesting array there is an array pointing to db positions or duplicated wids in db wids. wids can be duplicated in cl or/and db.
{
	Blender*** mat = thr->mat;
	uint16_t n_rows = thr->n_mat_rows;
	uint16_t ub_row = n_rows-1;
	Blender** sel_pos_objAr = thr->sel_pos_objAr;
	//sug_mat, sug_mat_lenAr
	countAr[n_rows] = {0};
	while(1)
	{
		if(countAr[r]>lenAr[r]-1)
		{
			if(!r) {// if it is first row.
				printf("==--->%d\n", r);
				break;// if r==0
			}
			countAr[r]=0;
			r--;
			continue;
		}
		else
		{
			if(r==ub_row)
			{
				size_t len = lenAr[r];
				for(size_t j=0; j<len; j++)
				{	//printf("%d    ,", mat[r][j]);
					usr_blendAr[mat[r][j]->usr_wind] = mat[r][j];
					if(thr->duplication_exist)
					{
						sel_pos_objAr[r] = mat[r][j];
						DB_MatObj* dmo = is_dbpos_duplicated(sel_pos_objAr, n_rows);
						if(dmo)
						{
							dup_db_mat_handler(dmo);
							freeDB_MatObj(dmo);
						}	
						else
							calculate_score();
					}
					else calculate_score();
				}
				countAr[r] = 0;
				r--;
				continue;
			}
			else
			{  //printf("\n%d --> ", mat[r][countAr[r]]);//here we should set qd_in/qd_pos
				sel_pos_objAr[r] = usr_blendAr[mat[r][countAr[r]]->usr_wind] = mat[r][countAr[r]];//we assign it sel_pos_objAr[r] inorder to avoid extra if.
				countAr[r]++;
			}
		}
		if(r<ub_row) r++;
	}
}



void dup_db_mat_handler(DB_MatObj* dmo)//for every db pos there is an array pointing to suggesting arrays/duplicated wids in usr_blendAr.
{
	//cl_dup_mat, cl_dup_mat_lenAr, countAr
	//counter
	Blender*** db_mat = dmo->mat;
	uint16_t* lenAr = dmo->lenAr;
	nullify_duplicated_db_poses(db_mat);
	//WORDS_LIMIT_T n_rows = dmo->n_rows;
	uint16_t ub = dmo->n_rows-1;
	countAr[dmo->n_rows] = {0};
	while(1)
	{
		if(countAr[r]>lenAr[r]-1)
		{
			if(!r) {//if it is first row.
				printf("==--->%d\n", r);
				break;// if r==0
			}
			countAr[r]=0;
			r--;
			continue;
		}
		else
		{
			if(r==ub)
			{
				size_t len = lenAr[r];
				for(size_t j=0; j<len; j++){
					if(j)	usr_blendAr[db_mat[r][j-1]->usr_wind] = NULL; //replace the previous one with empty blend.
					else	usr_blendAr[db_mat[r][lenAr[r]-1]->usr_wind] = NULL;//replace the last one with empty blend.
					usr_blendAr[db_mat[r][j]->usr_wind] = db_mat[r][j];// put it in array to be checked for the marks of a new comb.
					//usr_blendAr[db_mat[r][j]->usr_wind] = db_mat[r][j];
					calculate_score();
					//printf("%d    ,", db_mat[r][j]);
					//here to call another function.
				}
					
				countAr[r] = 0;
				r--;
				continue;
			}
			else
			{
				if(countAr[r])	usr_blendAr[db_mat[r][countAr[r]-1]->usr_wind] = NULL; //replace the previous one with empty blend.
				else	usr_blendAr[db_mat[r][lenAr[r]-1]]->usr_wind] = NULL;//replace the last one with empty blend.
				usr_blendAr[db_mat[r][countAr[r]->usr_wind] = db_mat[r][countAr[r]];// put it in array to be checked for the marks of a new comb.
				//usr_blendAr[db_mat[r][countAr[r]->usr_wind] = db_mat[r][countAr[r];
				//printf("\n%d --> ", db_mat[r][countAr[r]]);
					
				countAr[r]++;
			}
		}
		if(r<ub) r++;
	}
	restore_duplicated_db_poses(db_mat);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

char is_dbpos_duplicated(Blender** sel_pos_objAr, WORDS_LIMIT_T n_rows)
{
	
	char dup = 1;
	WORDS_LIMIT_T* sel_posAr[n_rows];
	WORDS_LIMIT_T* ar = sel_posAr;
	for(size_t i=0; i<n_rows); i++) ar[i] = sel_pos_objAr[i]->db_wind;
	
	DB_MatObj* dmo = NULL;
	switch(n_rows)//length of sug_ars
	{
		case 1:
				dup = 0;
				break;
		case 2:
				if(ar[0] != ar[1]) dup = 0;
				break;
		case 3:
				if(ar[0] != ar[1] && ar[0] != ar[2] &&	ar[1] != ar[2]) dup = 0;
				break;
		case 4:
				if(ar[0] != ar[1] && ar[0] != ar[2] &&	ar[0] != ar[3] && ar[1] != ar[2] && ar[1] != ar[3] &&	ar[2] != ar[3])	dup = 0;
				break;
		default:
				break;
	}
	if(dup)
	{
		cl_wid_flgAr[thr->key_len];
		memset(cl_wid_flgAr, 0, thr->key_len);
		for(int i=0; i<n_rows; i++)	cl_wid_flgAr[ar[i]]++;
		dmo = make_dup_pos_mat(sel_pos_objAr, sel_posAr, n_rows);
	}
	return dmo;
}


DB_MatObj* make_dup_pos_mat(Blender** sel_pos_objAr, WORDS_LIMIT_T* sel_posAr, WORDS_LIMIT_T n_rows)
{
	WORDS_LIMIT_T db_IndAr[db_klen];
	memset(db_IndAr, 0xFF, ad->len);
	size_t j=0;
	DB_MatObj* dmo = NULL;
	Blender*** mat = NULL;
	uint16_t* lenAr = NULL;
	for(size_t i=0; i<n_rows; i++)
	{
		if(cl_wid_flgAr[sel_posAr[i]]>1)
		{
			mat = realloc(++j*sizeof(WORDS_LIMIT_T*));
			lenAr = realloc(j*sizeof(WORDS_LIMIT_T));
			mat[j-1] = malloc(cl_wid_flgAr[sel_posAr[i]]*sizeof(WORDS_LIMIT_T));
			lenAr[j-1] = cl_wid_flgAr[sel_posAr[i]];
			//cl_wid_flgAr[sel_posAr[i]] = 0;
			db_IndAr[sel_posAr[i]] = j;
		}
	}
	if(j)
	{
		dup_pos_ars_len = j;
		fill_dup_pos_mat(mat, db_IndAr, sel_pos_objAr, sel_posAr, n_rows);
		DB_MatObj* dmo = malloc(sizeof(DB_MatObj));
		dmo->mat = mat;	dmo->lenAr = lenAr;	dmo->n_rows = j;
		
	}
	return dmo;
}
fill_dup_pos_mat(Blender*** mat, WORDS_LIMIT_T* db_IndAr, Blender** sel_pos_objAr, WORDS_LIMIT_T* sel_posAr, WORDS_LIMIT_T n_rows);
{
	countAr = calloc(WORDS_LIMIT_T, ars_len);
	for(int i=0; i<n_rows; i++)
	{
			pi = db_IndAr[sel_posAr[i]];//pos index// 
			if(pi<255)// then its an index in posAr
				posArs[pi][countAr[pi]++] = sel_pos_objAr[i];
	}
}

void nullify_duplicated_db_poses(DB_MatObj* dmo)//for every db pos there is an array pointing to suggesting arrays or duplicated wids in usr_blendAr.
{
	Blender*** db_mat = dmo->mat;
	uint16_t* lenAr = dmo->lenAr;
	for(size_t r=0; r<dmo->n_rows; r++)
	{
		int len = lenAr[r];
		for(int j=0; j<len; j++)
			usr_blendAr[mat[r][j]->usr_wind] = NULL;
	}
}

restore_duplicated_db_poses(DB_MatObj* dmo)
{
	Blender*** db_mat = dmo->mat;
	uint16_t* lenAr = dmo->lenAr;
	for(size_t r=0; r<dmo->n_rows; r++)
	{
		int len = lenAr[r];
		for(int j=0; j<len; j++)
			usr_blendAr[mat[r][j]->usr_wind] = mat[r][j];
	}	
}
///////////////////////////////////////
//////////////////////////////////////
/////////////////////////////////////
void bin_search_for_wid(char* ar, int l, swi)
{
		int f = 0;
		int m = (f+l)>>1;
		while (f < l) {
			char* p = ar+m;
			WIDTYPE_T wi = READ_WID(p);		
		  if (wi < swi)//sv/searching-value
			 f = m + 1;
		  else if (wi > swi)
			 l = m - 1;
		  else break;
		  m = (f+l)>>1;
	   }
	}
   return m;
}

freeDB_MatObj(DB_MatObj* dmo)
{
	Blender*** db_mat = dmo->mat;
	uint16_t* lenAr = dmo->lenAr;
	WORDS_LIMIT_T n_rows = dmo->n_rows;
	
	for(size_t i=0; i<n_rows; i++)
		free(db_mat[i]);
	free(db_mat);
	free(dmo);
	
}

void deduce_matrix_size()
{
	for(size_t i=MATRIX_DEFAULT_ROW_SIZE; i<n_size; i++)
	{
		size_t size = mat_sizeAr[i];
		for(size_t j=0; j<size; j++)
			free(mat[i][j]);
		free(mat[i]);
	}
	realloc(mat, sizeof(Blender**)*MATRIX_DEFAULT_ROWS);
	
	for(size_t i=0; i<MATRIX_DEFAULT_ROWS; i++)
	{
		size_t size = mat_sizeAr[i];
		for(size_t j=MATRIX_DEFAULT_COLUMNS; j<size; j++)
			free(mat[i][j]);
		realloc(mat[i], sizeof(Blender*)*MATRIX_DEFAULT_COLUMNS);
	}
}

//////////////////////to be part of thread
