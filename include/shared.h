#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <pthread.h>
#include <string.h>
#include "./request.h"
#include "./response.h"
#include <stdint.h>

#define WSA_ERROR(error) \
  do { \
    printf("error: %s\n | %d\n", error, WSAGetLastError()); \
  } while (0)

typedef struct {
  char  username[50];
  char  password[50]; 
} Credentials;
