#include <CUnit/Basic.h>
#include "C_hash/include/extended.h"
#include "utils.h"
#include "C_hash/include/iterator.h"


// These are example test functions. You should replace them with
// functions of your own.
int
main(void) 
{
    ioopm_hash_table_t *word_table = ioopm_hash_table_create(ioopm_s_hash, ioopm_s_cmp, 256);
    ioopm_hash_add_cleaner(word_table, ioopm_clean_strings, NULL);
    ioopm_process_file("test.txt", word_table);
    ioopm_list_t *list = ioopm_hash_table_values(word_table);
    ioopm_iterator_t *iter = ioopm_list_iterator(list);
    do if(!ioopm_linked_list_is_empty(list))
    {
      printf("%s: ", ioopm_iterator_current_key(iter).return_value.normal_string);
      printf("%d\n", ioopm_iterator_current_value(iter).return_value.i);
      
    }
    while(ioopm_iterator_next(iter).success);

    ioopm_hash_table_destroy(word_table);
    ioopm_linked_list_clear(list);
    ioopm_linked_list_destroy(list);
}
