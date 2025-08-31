#pragma once

typedef enum {
  OK = 200, 
  NOT_FOUND = 404
} StatusCode;

typedef struct {
  StatusCode    status_code; 
  char          data[50];
} Response;