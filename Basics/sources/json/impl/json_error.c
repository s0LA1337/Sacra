#define SACRA_JSON
#ifdef SACRA_JSON

#include "json/impl/json_error.h"

sacra_json_err *make_error(const SACRA_ERROR_CODES code)
{
  sacra_json_err *result = (sacra_json_err*)malloc(sizeof(sacra_json_err));
  result->error_code = code;
  switch(code)
  {
    case INVALID_FILE:
      sacra_string_from_chars_null(result->error_text, "The file is invalid.");
      return result;
    case NO_SIZE:
      sacra_string_from_chars_null(result->error_text, "The file is empty.");
      return result;
    case INVALID_JSON:
      sacra_string_from_chars_null(result->error_text, "The given file contains invalid json.");
      return result;
    case PANIC:
      sacra_string_from_chars_null(result->error_text, "AHHHHHH PANIC !1!!");
      return result;
    default:
      // if this ever occurs, the crash is justified.
      delete_error(result);
      return NULL;
  }

  // not needed, as it is assured it will return already something
  // just for safety and linter :)
  delete_error(result);
  return NULL;
}

void delete_error(sacra_json_err *err)
{
  sacra_string_free(err->error_text);
  free(err);
  err = NULL;
}

#endif /* SACRA_JSON */