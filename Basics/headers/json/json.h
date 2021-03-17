#ifndef SACRA_JSON
#define SACRA_JSON

#include "string/string.h"
#include "json/impl/json_error.h"

#include <stdint.h>

typedef struct /* sacra_json_object */
{
  sacra_string *key;
  
  // can be sacra_string, sacra_json_array or sacra_json_object
  // will always end with either an array or a string
  void *value;
} sacra_json_object;

typedef struct /* sacra_json_array */
{
  sacra_string *key;

  sacra_json_object *json_objects[]; // we want to differentiate...
  size_t json_object_count; 

  sacra_json_array *json_arrays[];
  size_t json_arr_count;

} sacra_json_array;

typedef struct /* sacra_json_base */
{
  void *children[];
  size_t child_count;

} sacra_json_base;

/**
* /brief Construction of the JSON object (on the heap)
* 
* /param path The path to a file containing JSON data
* /param error_msg The potential returning error message
* 
* /return the JSON object
* 
* /remarks error_msg and the returning object have to be managed by yourself
* /see delete_json_base
* /see sacra_string.sacra_string_free
* 
*/
sacra_json_base *create_from_file(const char *path, sacra_string *error_msg);

/**
* /brief Removes the create sacra_json_base object
*/
void delete_json_base(sacra_json_base *json_base);

/**
* /brief Attempts to get a json object based on the given key value
*/
sacra_json_object *try_get_object(const sacra_json_base *json_base, const sacra_string *key);

/**
* /brief Attempts to get a json array based on the given key value
*/
sacra_json_array *try_get_array(const sacra_json_base *json_base, const sacra_string *key);

void delete_json_object(sacra_json_object *object);

void delete_json_array(sacra_json_array *arr);

#endif /* SACRA_JSON */