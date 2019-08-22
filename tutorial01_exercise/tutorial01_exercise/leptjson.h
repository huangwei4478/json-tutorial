//
//  leptjson.h
//  tutorial01_exercise
//
//  Created by GoSwak on 2019/8/20.
//  Copyright © 2019 huangwei. All rights reserved.
//

#ifndef leptjson_h
#define leptjson_h
#include <stddef.h>


typedef enum {
  LEPT_NULL,
  LEPT_FALSE,
  LEPT_TRUE,
  LEPT_NUMBER,
  LEPT_STRING,
  LEPT_ARRAY,
  LEPT_OBJECT,
} lept_type;

enum {
  LEPT_PARSE_OK = 0,
  LEPT_PARSE_EXPECT_VALUE,
  LEPT_PARSE_INVALID_VALUE,
  LEPT_PARSE_ROOT_NOT_SINGULAR,
  LEPT_PARSE_NUMBER_TOO_BIG,
};

typedef struct {
  union {
    struct { char* s; size_t len; } s;                // string
    double n;                                         // number
  } u;
  lept_type type;
} lept_value;

typedef struct {
  const char* json;
  char *stack;
  size_t size, top;
} lept_context;

#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)
#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value *v);
void lept_set_boolean(lept_value *v, int b);

double lept_get_number(const lept_value *v);
void lept_set_number(lept_value *v, double n);

const char* lept_get_string(const lept_value *v);
size_t lept_get_string_length(const lept_value *v);
void lept_set_string(lept_value *v, const char* s, size_t len);
void lept_free(lept_value *v);

/**
 JSON-text = ws value ws
 ws = *(%x20 / %x09 / %x0A / %x0D)
 value = null / false / true 
 null  = "null"
 false = "false"
 true  = "true"
 */

#endif /* leptjson_h */
