#include <ctype.h>
#include "utils.h"

bool 
is_number(char *str) {
    if(str[0] == 0) return false;

    if (str[0] == '-') { 
        if (strlen(str) == 1) { 
            return false; 
        }
        for (int i = 1; i < strlen(str); i++) {
            if (!isdigit(str[i]) ) {
                return false;
            } 
        }
    } else {
        for (int i = 0; i < strlen(str); i++) {
            if (!isdigit(str[i]) ) {
                return false;
            } 
        }
    } 
    return true; 
}

void 
clear_input_buffer() {
    int c;
    do {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
    return;
}

int 
read_string(char *buf, int buf_siz) {
    int cnt = 0;
    char c; 
    do {
        c = getchar();
        if (c == '\n') {
            break;
        } else {
            buf[cnt] = c;  
            cnt = cnt + 1;
        }
    } while (c != '\n' && c != EOF && cnt < buf_siz - 1);
    if (cnt >= buf_siz -1) {
        clear_input_buffer();
    }
    buf[cnt] = '\0';
    return cnt;
}

int 
string_length(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return i; 
}

void 
print(char str[]) {
    // int len_str = string_length(str);
    // alt lösning med for loop med hjälp av längden av strängen
    int j = 0; 
    while (str[j] != '\0') { 
        putchar(str[j]); 
        j = j + 1; 
    }
}

void 
println(char str[]) {
    print(str);
    print("\n");
}

bool 
not_empty(char *str) {
    return strlen(str) > 0;
}

bool 
not_number_empty(char *str) {
    if (string_length(str) == 3) {
        if (!isdigit(str[0])) {
            str++;
            if (is_number(str)) {
                return true; 
            }
        }
    }
    return false; 
}

bool 
not_string_empty(char *str) {
    return strlen(str) == 1;
}

answer_t 
ask_question(char *question, check_func check, convert_func convert) {
    int buf_siz = 100;
    char buf[buf_siz];
    do {
        printf("%s\n", question);
        read_string(buf, buf_siz);
    }
    while (check(buf) == false);
    return convert(buf);
}

int 
ask_question_int(char *question) {
    answer_t answer = ask_question(question, is_number, (convert_func) atoi);
    return answer.int_value; // svaret som ett heltal
}

char *
ask_question_string(char *question) {
  return ask_question(question, not_empty, 
                      (convert_func) strdup).string_value;
}

char *
ask_question_char(char *question) {
  return ask_question(question, not_string_empty, 
                      (convert_func) strdup).string_value;
}

char *
ask_question_shelf(char *question) {
  return ask_question(question, not_number_empty, 
                      (convert_func) strdup).string_value;
}
static
int
mod(int x, int n)
{
    return (x % n + n) % n;
}

ioopm_hash_table_t *
ioopm_process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r");
    if(!f)
        return NULL;
    
    while(!feof(f))
    {
        char buf[255];
        char *ptr = buf;
        int fetch;
        do
        {
            fetch = fgetc(f);
            if(mod(fetch, ASCII_SIZ) > ASCII_GARBAGE)
            {
                *ptr = (char) fetch;
                ptr++;
            }
        } 
        while(mod(fetch, ASCII_SIZ) > ASCII_GARBAGE && fetch != -1 && fetch != 127);
        
        *ptr = 0;

        if(mod(buf[0], ASCII_SIZ) <= ASCII_GARBAGE || buf[0] == 127 || buf[0] == -1)
            continue;
        
        elem_t string_to_add;
        string_to_add.p = strdup(buf);
        elem_t holder;
        option_t result = ioopm_hash_table_lookup(ht, string_to_add);
        ioopm_hash_table_insert(ht, string_to_add, (elem_t)(result.return_value.i + 1));
    }

    fclose(f);
    return ht;
}