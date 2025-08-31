#pragma once

typedef struct {
  char[10]    customer_id;
  int         balance;
} Account;

void create_account(char[10] customer_id, int balance);
void delete_account(char[10] customer_id);