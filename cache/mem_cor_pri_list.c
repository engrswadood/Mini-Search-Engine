void mem_add_mcpn(MemCorSrchQuery* sq)
{
	MemMCPN_Tbl* ht = global->mcpn_tbl;
	MemCorPriNode  ***hArs = ht->hArs;
	
	int i = str_hash(ht->hTotalBuc, key, chlen);//_ strSize
	MemCorPriNode *adding_item = malloc(sizeof(MemCorPriNode));
	
	adding_item->str = key;
	adding_item->chlen = chlen;
	adding_item->_next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
	hArs[i>>IND_SHIFTING][i&IND_ANDING] = adding_item;
	if(ht->start)
	{
		ht->start->back = adding_item;
		adding_item->next = ht->start;
	}
	else
	{
		adding_item->next = NULL;
		ht->end = adding_item;
	}
	ht->start = adding_item;
	adding_item->back = NULL;
}
mem_prioritise_cor_mcpn(MemCorPriNode* pn)
{
		if(end == pn)
		{
			end = end->back->back;
			end->next = NULL;
		}
		else if(pn != start)
			
		{
			pn->next->back = pn->back;
			pn->back->next = pn->next;
		}
		start = pn;
}

MemCorPriNode* mem_delete_cor_mcpn_end()
{
		MemMCPN_Tbl* ht = global->mcpn_tbl; 
		MemCorPriNode* mcpn = ht->end;
		end = end->back->back;
		end->next = NULL;
		return mcpn;
}

mem_delete_cor_mcpn(MemCorPriNode* pn)
{
		if(end == pn)
			mem_delete_cor_mcpn_end();
		else if(pn == start)
			start = start->next;
		else
		{
			pn->next->back = pn->back;
			pn->back->next = pn->next;
		}
		free(pn);
}