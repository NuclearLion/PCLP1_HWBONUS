// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _URL_DETECTION_H_
#define _URL_DETECTION_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DOMDB_CNT 41
#define EXT_CNT 9
#define DOM_LEN 30
#define URL_LEN 500
#define BEN 0
#define MAL 1
#define FALSE 0
#define TRUE 1

//read the domain db and save it in a matrix
void read_domain_db(char domains[][DOM_LEN]);

//main call for task1 - Malware Links Detection
void url_detect(void);

#endif
