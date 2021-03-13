#include "string/string.h"


int main(int argc, char** argv) {
    
    sacra_string *string = sacra_string_new();
    sacra_string *suffix = sacra_string_new();
    
    sacra_string_from_chars_null(string, "I like testing strings with this.");
    printf("LenString1: %d\n", string->length);
    
    sacra_string_from_chars_null(suffix, "Foo Bar");
    
    sacra_string_suffix(string, suffix);
    sacra_string_prefix(string, suffix);
    
    sacra_string_print(string);
    printf("\nLength: %d\n", string->length);
    
    sacra_string_free(string);
    
}

