#include "string/string.h"


size_t sacra_string_init_capacity   = 32;
size_t sacra_string_realloc_padding = 16;


sacra_string* sacra_string_new() {
    
    sacra_string *string = malloc(sizeof(sacra_string));
    string->length       = 0;
    string->capacity     = sacra_string_init_capacity;
    string->data         = calloc(1, string->capacity);
    
    return string;
}

void sacra_string_free(sacra_string *string) {
    
    free(string->data);
    free(string);
}



sacra_string* sacra_string_copy(sacra_string *string) {
    
    size_t        length       = string->length;
    
    sacra_string *copy         = sacra_string_new();
    sacra_string_resize_to(copy, length);
    
    char         *copy_data    = copy->data;
    char         *string_data  = string->data;
    
    size_t        index = 0;
    while(index < length) {
        
        copy_data[index] = string_data[index];
        ++index;
    }
    
    return copy;
}

sacra_string *sacra_string_copy_part(sacra_string *string, size_t first, size_t length) {
    
    sacra_string *copy         = sacra_string_new();
    sacra_string_resize_to(copy, length);
    
    char         *copy_data    = copy->data;
    char         *string_data  = string->data;
    
    size_t        index        = 0;
    while(index < length) {
        
        copy_data[index] = string_data[index+first];
    }
    
    return copy;
}

bool sacra_string_equals(sacra_string *string1, sacra_string *string2) {
    
    size_t length1 = string1->length;
    size_t length2 = string2->length;
    
    if(length1 != length2) {
        
        return false;
    }
    
    char  *data1   = string1->data;
    char  *data2   = string2->data;
    
    size_t index   = 0;
    while(index < length1) {
        
        if(data1[index] != data2[index]) {
            
            return false;
        }
        
        ++index;
    }
    // If the loop has gone through the strings without finding a difference
    
    return true;
}



void sacra_string_resize_to(sacra_string *string, size_t new_size) {
    
    if(new_size < string->length) {
        // The capacity is ALWAYS kept higher than or equals to the length,
        // so it is not needed to re-allocate anything here.
        
        // Overwrite the old parts with zeroes
        
        size_t  length = string->length;
        char   *data   = string->data;
        size_t  index  = new_size;
        while(index < length) {
            
            data[index] = 0x00;
            ++index;
        }
        
        
        string->length = new_size;
        
        return;
    }
    
    if(new_size < string->capacity) {
        // It is only needed to set the new area to spaces
        // and set the length to 'new_size'
        
        char   *data  = string->data;
        size_t  index = string->length;
        while(index < new_size) {
            
            data[index] = ' ';
            ++index;
        }
        
        string->length = new_size;
        
        return;
    }
    
    if(new_size >= string->capacity) {
        // Now, it is needed to re-allocate and copy the data
        
        char   *old_data = string->data;
        char   *new_data = calloc(1, new_size + sacra_string_realloc_padding + 1); // +1 for the NULL-ending
        
        size_t  length = string->length;
        size_t  index  = 0;
        while(index < length) {
            
            new_data[index] = old_data[index];
            ++index;
        }
        
        while(index < new_size) {
            
            new_data[index] = ' ';
            ++index;
        }
        
        free(old_data);
        string->data   = new_data;
        string->length = new_size;
    }
    
}

void sacra_string_resize_by(sacra_string *string, size_t difference) {
    
    ssize_t new_size = string->length + difference;
    
    if(new_size < 1) {
        
        return;
    }
    
    sacra_string_resize_to(string, new_size);
    
}



void          sacra_string_to_lowercase    (sacra_string* string) {
    
    // TODO
    
    
    
}

void          sacra_string_to_uppercase    (sacra_string* string) {
    
    // TODO
    
    
    
}



void sacra_string_from_chars(sacra_string *string, char *data, size_t length) {
    
    sacra_string_resize_to(string, length);
    
    char   *string_data = string->data;
    size_t  index       = 0;
    while(index < length) {
        
        string_data[index] = data[index];
        ++index;
    }
    
}

void sacra_string_from_chars_null(sacra_string *string, char *data) {
    
    size_t  length = 0;
    while(data[length] != 0x00) {
        
        ++length;
    }
    
    sacra_string_from_chars(string, data, length);
    
}

char* sacra_string_to_chars(sacra_string *string) {
    
    size_t  length      = string->length;
    char   *output      = malloc(length+1);
    
    char   *string_data = string->data;
    size_t  index       = 0;
    while(index < length) {
        
        output[index] = string_data[index];
        ++index;
    }
    
    return output;
}


void sacra_string_prefix(sacra_string *string, sacra_string *prefix) {
    
    ssize_t  index          = string->length;
    size_t   prefix_length  = prefix->length;
    
    sacra_string_resize_by(string, prefix_length);
    
    
    // Move the characters of 'string' 'prefix->length' bytes to the end
    
    index                  += prefix_length;
    char    *string_data    = string->data;
    while(index >= prefix_length) {
        
        string_data[index] = string_data[index-prefix_length];
        --index;
    }
    
    
    // Copy the prefix in front of the string
    
    char    *prefix_data = prefix->data;
    index                = 0;
    while(index < prefix_length) {
        
        string_data[index] = prefix_data[index];
        ++index;
    }
    
}

void sacra_string_infix(sacra_string *string, sacra_string *infix, size_t index) {
    
    
    
    
    
}

void sacra_string_suffix(sacra_string *string, sacra_string *suffix) {
    
    size_t  string_length = string->length;
    size_t  suffix_length = suffix->length;
    
    sacra_string_resize_by(string, suffix->length);
    
    
    // Copy the suffix after the string
    
    char   *string_data   = string->data;
    char   *suffix_data   = suffix->data;
    size_t  index         = 0;
    while(index < suffix_length) {
        
        string_data[string_length+index] = suffix_data[index];
        ++index;
    }
    
}



void sacra_string_prefix_single(sacra_string *string, char prefix) {
    
    // TODO
    
    
    
}

void sacra_string_infix_single(sacra_string *string, char infix,  size_t index) {
    
    // TODO
    
    
    
}

void sacra_string_suffix_single(sacra_string *string, char suffix) {
    
    // TODO
    
    
    
}



void sacra_string_print(sacra_string *string) {
    
    printf("%s", string->data);
}

