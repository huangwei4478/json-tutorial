//
//  leptjson.c
//  tutorial01_exercise
//
//  Created by GoSwak on 2019/8/20.
//  Copyright © 2019 huangwei. All rights reserved.
//

#include "leptjson.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch) do { assert(*(c->json) == (ch)); (c->json)++; } while (0)

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void lept_parse_whitespace(lept_context *c) {
  const char *p = c -> json;
  while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
    p++;
  }
  c->json = p;
}

static int lept_parse_literal(lept_context *c, lept_value *v, const char *literal, lept_type type) {
  size_t i;
  EXPECT(c, literal[0]);
  for (i = 0; literal[i + 1] != '\0'; ++i) {
    if (c->json[i] != literal[i + 1]) {
      return LEPT_PARSE_INVALID_VALUE;
    }
  }
  c->json += i;
  v->type = type;
  return LEPT_PARSE_OK;
}

static int lept_parse_number(lept_context *c, lept_value *v) {
  char *endptr;
  // TODO: validate number in JSON format
  v->n = strtod(c->json, &endptr);
  if (c->json == endptr) {
    return LEPT_PARSE_INVALID_VALUE;
  }
  c->json = endptr;
  v->type = LEPT_NUMBER;
  return LEPT_PARSE_OK;
}

/* false = "false */

/* value = null / false / true / number */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int lept_parse_value(lept_context *c, lept_value *v) {
  switch (*(c->json)) {
    case 'n':   return lept_parse_literal(c, v, "null", LEPT_NULL);
    case 't':   return lept_parse_literal(c, v, "true", LEPT_TRUE);
    case 'f':   return lept_parse_literal(c, v, "false", LEPT_FALSE);
    case '\0':  return LEPT_PARSE_EXPECT_VALUE;
    default:    return lept_parse_number(c, v);
  }
}

/**
    JSON-text = ws value ws
 */
int lept_parse(lept_value* v, const char* json) {
  lept_context c;
  assert(v != NULL);
  c.json = json;
  v -> type = LEPT_NULL;
  lept_parse_whitespace(&c);
  int ret = lept_parse_value(&c, v);
  lept_parse_whitespace(&c);
  if (*c.json != '\0') {
    ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
  }
  return ret;
}

lept_type lept_get_type(const lept_value* v) {
  return v->type;
}

double lept_get_number(const lept_value* v) {
  assert(v != NULL && v->type == LEPT_NUMBER);
  return v->n;
}


