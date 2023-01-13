// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _URL_DETECTION_H_
#define _URL_DETECTION_H_

#include "utils.h"
#include <ctype.h>

#define DOMDB_CNT 41
#define EXT_CNT 10
#define DOM_LEN 30
#define URL_LEN 1000

//read the domain db and save it in a matrix
int read_domain_db(char domains[][DOM_LEN]);

//main call for task1 - Malware Links Detection
void url_detect(void);

//count how many digits are in the domain
int digit_counter(char *ptr);

//check if the domain is in the database
int check_db(char *ptr, char domains[][DOM_LEN]);

#endif
