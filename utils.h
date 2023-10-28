#pragma once

#include "C_hash/include/extended.h"

extern char *strdup(const char *);

typedef union { 
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool(*check_func)(char *);

typedef answer_t(*convert_func)(char *);


int 
read_string(char *buf, int buf_siz);

bool 
is_number(char *str);

void 
print(char str[]);

void 
println(char str[]);

bool 
not_empty(char *str);

answer_t 
ask_question(char *question, check_func check, convert_func convert);

int 
ask_question_int(char *question);

char *
ask_question_char(char *question);

char *
ask_question_string(char *question);

char *
ask_question_shelf(char *question);

ioopm_hash_table_t *
ioopm_process_file(char *filename, ioopm_hash_table_t *word_hash);
