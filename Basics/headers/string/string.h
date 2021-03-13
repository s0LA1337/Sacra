
#ifndef SACRA_STRING
#define SACRA_STRING


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    
    size_t length;   // How many bytes are used
    size_t capacity; // How many bytes are allocated
    
    char* data;
    
} sacra_string;


sacra_string* sacra_string_new             ();
void          sacra_string_free            (sacra_string *string);

sacra_string* sacra_string_copy            (sacra_string *string);
sacra_string* sacra_string_copy_part       (sacra_string *string, size_t first, size_t length);
bool          sacra_string_equals          (sacra_string *string1, sacra_string *string2);

void          sacra_string_resize_to       (sacra_string *string, size_t new_size);
void          sacra_string_resize_by       (sacra_string *string, size_t difference);

void          sacra_string_to_lowercase    (sacra_string *string);
void          sacra_string_to_uppercase    (sacra_string *string);

void          sacra_string_from_chars      (sacra_string *string, char *data, size_t length);
void          sacra_string_from_chars_null (sacra_string *string, char *data);
char*         sacra_string_to_chars        (sacra_string *string);

void          sacra_string_prefix          (sacra_string *string, sacra_string *prefix);
void          sacra_string_infix           (sacra_string *string, sacra_string *infix, size_t index);
void          sacra_string_suffix          (sacra_string *string, sacra_string *suffix);

void          sacra_string_prefix_single   (sacra_string *string, char prefix);
void          sacra_string_infix_single    (sacra_string *string, char infix,  size_t index);
void          sacra_string_suffix_single   (sacra_string *string, char suffix);


#endif

