#include "json/json.h"

sacra_json_base * create_from_file(const char *path, sacra_string *error_msg)
{
  return NULL;
}

void delete_json_base(sacra_json_base *json_base)
{
  for(size_t i = 0u; i < json_base->child_count; ++i)
  {
    if(sacra_json_object *candidate = ((sacra_json_object*)json_base->children[i]))
      delete_json_object(candidate);
    else if(sacra_json_array *candidate = ((sacra_json_array*)json_base->children[i]))
      delete_json_array(candidate);
    else
    {
      free(json_base->children[i]);
      json_base->children[i] = NULL;
    }
  }

  free(json_base);
  json_base = NULL;
}

sacra_json_object *try_get_object(const sacra_json_base *json_base, const sacra_string *key)
{
  sacra_json_object *temp = NULL;
  for(size_t i = 0u; i < json_base->child_count; ++i)
  {
    if(temp = (sacra_json_object*)json_base->children[i])
    {
      if(!strcmp(key->data, temp->key))
        return temp;
    }
  }

  return NULL;
}

sacra_json_array *try_get_array(const sacra_json_base *json_base, const sacra_string *key)
{
  sacra_json_array *temp = NULL;
  for(size_t i = 0u; i < json_base->child_count; ++i)
  {
    if(temp = (sacra_json_array*)json_base->children[i])
    {
      if(!strcmp(key->data, temp->key))
        return temp;
    }
  }

  return NULL;
}

void delete_json_object(sacra_json_object *object)
{
  sacra_string_free(object->key);
  if((sacra_string*)object->value)
    sacra_string_free(object->value);
  else if((sacra_json_object*)object->value)
    delete_json_object(object->value);
  else if((sacra_json_array*)object->value)
    delete_json_array(object->value);
  else
    free(object->value);

  object->value = NULL;
}

void delete_json_array(sacra_json_array *arr)
{
  for(size_t i = 0u; i < arr->json_arr_count; ++i)
  {
    if((sacra_json_array*)arr->json_arrays[i])
    {
      delete_json_array(arr->json_arrays[i]);
      arr->json_arrays[i] = NULL;
    }
    else
    {
      printf("Something went wrong with the deletion of a json array!\n(In Array Count)\n");
      free(arr);
      arr = NULL;
    }
  }
  for(size_t i = 0u; i < arr->json_object_count; ++i)
  {
    if((sacra_json_object*)arr->json_objects[i])
    {
      delete_json_object(arr->json_objects[i]);
      arr->json_objects[i] = NULL;
    }
    else
    {
      printf("Something went wrong with the deletion of a json array!\n(In Object Count)\n");
      free(arr);
      arr = NULL;
    }
  }

  free(arr);
  arr = NULL;
}
