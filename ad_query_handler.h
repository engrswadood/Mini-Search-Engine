#ifndef QUERY_HANDLER_FILE
#define QUERY_HANDLER_FILE

//type, keys_len, keys, id, suggeestions//select
//type, keys_len, keys, id, pos, query_len, query //insert
//type, keys_len, keys, id, delete_query//delete
//type, keys_len, keys, id, ukeys_len, ukeys, id, pos, query_len, query//updating
//reset_sq, init_cache, collect_result, apply_pos_marks



//short start_time;//time and day
//short end_time;// time and month
//char total_tokens;
//char per_hour_tokens;

int init_query_handler(char */*q_val*/, short /*size*/);
void search_employer(char */*q_val*/);
void add_employer(char */*q*/, char*/*ins_p*/);
void update_employer(char */*q_val*/);
void delete_employer(char */*q*/);
void collect_result();
void set_db_query(unsigned int /*total_replying_ad*/);

#endif