/**
 * Only accept code coming from json, as this is not supposed to be used outside of the json parser
 */

#ifdef SACRA_JSON
#ifndef SACRA_JSON_ERR
#define SACRA_JSON_ERR

#include "string/string.h"

#include <stdint.h>

enum SACRA_ERROR_CODES
{
  INVALID_FILE = -1,
  NO_SIZE = 0,
  INVALID_JSON,
  PANIC
};

typedef struct sacra_json_err
{
  sacra_string *error_text;
  SACRA_ERROR_CODES error_code;
} json_err;

sacra_json_err *make_error(const SACRA_ERROR_CODES code);
void delete_error(sacra_json_err *err);

#endif /* SACRA_JSON_ERR */
#endif /* SACRA_JSON */