//
//  leptjson.h
//  tutorial01_exercise
//
//  Created by GoSwak on 2019/8/20.
//  Copyright © 2019 huangwei. All rights reserved.
//

#ifndef leptjson_h
#define leptjson_h


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
};

typedef struct {
  lept_type type;
} lept_value;

typedef struct {
  const char* json;
} lept_context;



int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);

/**
 JSON-text = ws value ws
 ws = *(%x20 / %x09 / %x0A / %x0D)
 value = null / false / true 
 null  = "null"
 false = "false"
 true  = "true"
 */

#endif /* leptjson_h */
