// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _TRAFFIC_DETECTION_H_
#define _TRAFFIC_DETECTION_H_

#include <stdlib.h>

#include "utils.h"

#define HEADER_LEN 280
#define TRAFFIC_LEN 160
#define ZERO_SECONDS "0 days 00:00:00"

//main call for traffic detection
void traffic_detect(void);

#endif
