get_words_list(char* str, int len, wordAr, lenAr)
{
	int j=1;
	int ind=0;
	wordAr[0] = str;
	for(int i=1; i<len; i++)
	{
		if(str[i] == WSEPARATOR)
		{
			lenAr[ind] = j*sizeof(CHSIZE_T);
			wordAr[++ind]	= str+i;
			j=0;
		}
		j++;
	}
	lenAr[ind++] = j*sizeof(CHSIZE_T);
	return ind;// equal to length.
	//#if (CHBYTES == 1)
		//lenAr[i++] = p++ - wAr[i];
	//#else
		//lenAr[i++] = (p++ - wAr[i])*sizeof(CHSIZE_T);
	//#endif
}

char* wids_to_bytes(int* widAr, size_t wlen)//pos will be in little endian format from nodejs.
{
	WIDSIZE_T* widAr = my->widAr;
	char* wid_buf = malloc(wlen*sizeof(WIDSIZE_T));
	IF__LITTLE_ENDIAN
		wid_buf = (char*) widAr;
	else
	{
		size_t j = 0;
		for(int i=0; i<wlen; i++)
		{
			int a = widAr[i];
			wid_buf[j++] = a&0x000000FF;
			wid_buf[j++] = a&0x0000FF00;
			#if (WID_BYTES == 4)
				wid_buf[j++] = a&0x00FF0000;
				wid_buf[j++] = a&0xFF000000;
			#endif
		}
	}
	return wid_buf;
}

WIDSIZE_T* bytes_to_blends(Thread* thr)//made for search engine.
{
	char* buf = thr->blend_q;
	uint32_t len = thr->blend_len;
	WIDSIZE_T* ar = malloc(len*sizeof(uint32_t));
	for(size_t i=0; i<len; i++)
		ar[i] = READ_LE4(buf);
	return ar;
}